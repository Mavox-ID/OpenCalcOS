/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <subdev/timer.h>

#define NV04_PTIMER_INTR_0      0x009100
#define NV04_PTIMER_INTR_EN_0   0x009140
#define NV04_PTIMER_NUMERATOR   0x009200
#define NV04_PTIMER_DENOMINATOR 0x009210
#define NV04_PTIMER_TIME_0      0x009400
#define NV04_PTIMER_TIME_1      0x009410
#define NV04_PTIMER_ALARM_0     0x009420

struct nv04_timer_priv {
	struct nouveau_timer base;
	struct list_head alarms;
	spinlock_t lock;
};

static u64
nv04_timer_read(struct nouveau_timer *ptimer)
{
	struct nv04_timer_priv *priv = (void *)ptimer;
	u32 hi, lo;

	do {
		hi = nv_rd32(priv, NV04_PTIMER_TIME_1);
		lo = nv_rd32(priv, NV04_PTIMER_TIME_0);
	} while (hi != nv_rd32(priv, NV04_PTIMER_TIME_1));

	return ((u64)hi << 32 | lo);
}

static void
nv04_timer_alarm_trigger(struct nouveau_timer *ptimer)
{
	struct nv04_timer_priv *priv = (void *)ptimer;
	struct nouveau_alarm *alarm, *atemp;
	unsigned long flags;
	LIST_HEAD(exec);

	/* move any due alarms off the pending list */
	spin_lock_irqsave(&priv->lock, flags);
	list_for_each_entry_safe(alarm, atemp, &priv->alarms, head) {
		if (alarm->timestamp <= ptimer->read(ptimer))
			list_move_tail(&alarm->head, &exec);
	}

	/* reschedule interrupt for next alarm time */
	if (!list_empty(&priv->alarms)) {
		alarm = list_first_entry(&priv->alarms, typeof(*alarm), head);
		nv_wr32(priv, NV04_PTIMER_ALARM_0, alarm->timestamp);
		nv_wr32(priv, NV04_PTIMER_INTR_EN_0, 0x00000001);
	} else {
		nv_wr32(priv, NV04_PTIMER_INTR_EN_0, 0x00000000);
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	/* execute any pending alarm handlers */
	list_for_each_entry_safe(alarm, atemp, &exec, head) {
		list_del(&alarm->head);
		alarm->func(alarm);
	}
}

static void
nv04_timer_alarm(struct nouveau_timer *ptimer, u64 time,
		 struct nouveau_alarm *alarm)
{
	struct nv04_timer_priv *priv = (void *)ptimer;
	struct nouveau_alarm *list;
	unsigned long flags;

	alarm->timestamp = ptimer->read(ptimer) + time;

	/* append new alarm to list, in soonest-alarm-first order */
	spin_lock_irqsave(&priv->lock, flags);
	list_for_each_entry(list, &priv->alarms, head) {
		if (list->timestamp > alarm->timestamp)
			break;
	}
	list_add_tail(&alarm->head, &list->head);
	spin_unlock_irqrestore(&priv->lock, flags);

	/* process pending alarms */
	nv04_timer_alarm_trigger(ptimer);
}

static void
nv04_timer_intr(struct nouveau_subdev *subdev)
{
	struct nv04_timer_priv *priv = (void *)subdev;
	u32 stat = nv_rd32(priv, NV04_PTIMER_INTR_0);

	if (stat & 0x00000001) {
		nv04_timer_alarm_trigger(&priv->base);
		nv_wr32(priv, NV04_PTIMER_INTR_0, 0x00000001);
		stat &= ~0x00000001;
	}

	if (stat) {
		nv_error(priv, "unknown stat 0x%08x\n", stat);
		nv_wr32(priv, NV04_PTIMER_INTR_0, stat);
	}
}

static int
nv04_timer_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nv04_timer_priv *priv;
	int ret;

	ret = nouveau_timer_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.base.intr = nv04_timer_intr;
	priv->base.read = nv04_timer_read;
	priv->base.alarm = nv04_timer_alarm;

	INIT_LIST_HEAD(&priv->alarms);
	spin_lock_init(&priv->lock);
	return 0;
}

static void
nv04_timer_dtor(struct nouveau_object *object)
{
	struct nv04_timer_priv *priv = (void *)object;
	return nouveau_timer_destroy(&priv->base);
}

static int
nv04_timer_init(struct nouveau_object *object)
{
	struct nouveau_device *device = nv_device(object);
	struct nv04_timer_priv *priv = (void *)object;
	u32 m = 1, f, n, d;
	int ret;

	ret = nouveau_timer_init(&priv->base);
	if (ret)
		return ret;

	/* aim for 31.25MHz, which gives us nanosecond timestamps */
	d = 1000000 / 32;

	/* determine base clock for timer source */
#if 0 /*XXX*/
	if (device->chipset < 0x40) {
		n = nouveau_hw_get_clock(device, PLL_CORE);
	} else
#endif
	if (device->chipset <= 0x40) {
		/*XXX: figure this out */
		f = -1;
		n = 0;
	} else {
		f = device->crystal;
		n = f;
		while (n < (d * 2)) {
			n += (n / m);
			m++;
		}

		nv_wr32(priv, 0x009220, m - 1);
	}

	if (!n) {
		nv_warn(priv, "unknown input clock freq\n");
		if (!nv_rd32(priv, NV04_PTIMER_NUMERATOR) ||
		    !nv_rd32(priv, NV04_PTIMER_DENOMINATOR)) {
			nv_wr32(priv, NV04_PTIMER_NUMERATOR, 1);
			nv_wr32(priv, NV04_PTIMER_DENOMINATOR, 1);
		}
		return 0;
	}

	/* reduce ratio to acceptable values */
	while (((n % 5) == 0) && ((d % 5) == 0)) {
		n /= 5;
		d /= 5;
	}

	while (((n % 2) == 0) && ((d % 2) == 0)) {
		n /= 2;
		d /= 2;
	}

	while (n > 0xffff || d > 0xffff) {
		n >>= 1;
		d >>= 1;
	}

	nv_debug(priv, "input frequency : %dHz\n", f);
	nv_debug(priv, "input multiplier: %d\n", m);
	nv_debug(priv, "numerator       : 0x%08x\n", n);
	nv_debug(priv, "denominator     : 0x%08x\n", d);
	nv_debug(priv, "timer frequency : %dHz\n", (f * m) * d / n);

	nv_wr32(priv, NV04_PTIMER_NUMERATOR, n);
	nv_wr32(priv, NV04_PTIMER_DENOMINATOR, d);
	nv_wr32(priv, NV04_PTIMER_INTR_0, 0xffffffff);
	nv_wr32(priv, NV04_PTIMER_INTR_EN_0, 0x00000000);
	return 0;
}

static int
nv04_timer_fini(struct nouveau_object *object, bool suspend)
{
	struct nv04_timer_priv *priv = (void *)object;
	nv_wr32(priv, NV04_PTIMER_INTR_EN_0, 0x00000000);
	return nouveau_timer_fini(&priv->base, suspend);
}

struct nouveau_oclass
nv04_timer_oclass = {
	.handle = NV_SUBDEV(TIMER, 0x04),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv04_timer_ctor,
		.dtor = nv04_timer_dtor,
		.init = nv04_timer_init,
		.fini = nv04_timer_fini,
	}
};
