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
#include <subdev/gpio.h>

struct nv10_gpio_priv {
	struct nouveau_gpio base;
};

static int
nv10_gpio_sense(struct nouveau_gpio *gpio, int line)
{
	if (line < 2) {
		line = line * 16;
		line = nv_rd32(gpio, 0x600818) >> line;
		return !!(line & 0x0100);
	} else
	if (line < 10) {
		line = (line - 2) * 4;
		line = nv_rd32(gpio, 0x60081c) >> line;
		return !!(line & 0x04);
	} else
	if (line < 14) {
		line = (line - 10) * 4;
		line = nv_rd32(gpio, 0x600850) >> line;
		return !!(line & 0x04);
	}

	return -EINVAL;
}

static int
nv10_gpio_drive(struct nouveau_gpio *gpio, int line, int dir, int out)
{
	u32 reg, mask, data;

	if (line < 2) {
		line = line * 16;
		reg  = 0x600818;
		mask = 0x00000011;
		data = (dir << 4) | out;
	} else
	if (line < 10) {
		line = (line - 2) * 4;
		reg  = 0x60081c;
		mask = 0x00000003;
		data = (dir << 1) | out;
	} else
	if (line < 14) {
		line = (line - 10) * 4;
		reg  = 0x600850;
		mask = 0x00000003;
		data = (dir << 1) | out;
	} else {
		return -EINVAL;
	}

	nv_mask(gpio, reg, mask << line, data << line);
	return 0;
}

static void
nv10_gpio_irq_enable(struct nouveau_gpio *gpio, int line, bool on)
{
	u32 mask = 0x00010001 << line;

	nv_wr32(gpio, 0x001104, mask);
	nv_mask(gpio, 0x001144, mask, on ? mask : 0);
}

static void
nv10_gpio_intr(struct nouveau_subdev *subdev)
{
	struct nv10_gpio_priv *priv = (void *)subdev;
	u32 intr = nv_rd32(priv, 0x001104);
	u32 hi = (intr & 0x0000ffff) >> 0;
	u32 lo = (intr & 0xffff0000) >> 16;

	priv->base.isr_run(&priv->base, 0, hi | lo);

	nv_wr32(priv, 0x001104, intr);
}

static int
nv10_gpio_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
	       struct nouveau_oclass *oclass, void *data, u32 size,
	       struct nouveau_object **pobject)
{
	struct nv10_gpio_priv *priv;
	int ret;

	ret = nouveau_gpio_create(parent, engine, oclass, &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.drive = nv10_gpio_drive;
	priv->base.sense = nv10_gpio_sense;
	priv->base.irq_enable = nv10_gpio_irq_enable;
	nv_subdev(priv)->intr = nv10_gpio_intr;
	return 0;
}

static void
nv10_gpio_dtor(struct nouveau_object *object)
{
	struct nv10_gpio_priv *priv = (void *)object;
	nouveau_gpio_destroy(&priv->base);
}

static int
nv10_gpio_init(struct nouveau_object *object)
{
	struct nv10_gpio_priv *priv = (void *)object;
	int ret;

	ret = nouveau_gpio_init(&priv->base);
	if (ret)
		return ret;

	nv_wr32(priv, 0x001140, 0x00000000);
	nv_wr32(priv, 0x001100, 0xffffffff);
	nv_wr32(priv, 0x001144, 0x00000000);
	nv_wr32(priv, 0x001104, 0xffffffff);
	return 0;
}

static int
nv10_gpio_fini(struct nouveau_object *object, bool suspend)
{
	struct nv10_gpio_priv *priv = (void *)object;
	nv_wr32(priv, 0x001140, 0x00000000);
	nv_wr32(priv, 0x001144, 0x00000000);
	return nouveau_gpio_fini(&priv->base, suspend);
}

struct nouveau_oclass
nv10_gpio_oclass = {
	.handle = NV_SUBDEV(GPIO, 0x10),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nv10_gpio_ctor,
		.dtor = nv10_gpio_dtor,
		.init = nv10_gpio_init,
		.fini = nv10_gpio_fini,
	},
};
