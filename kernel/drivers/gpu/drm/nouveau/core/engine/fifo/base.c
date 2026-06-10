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
#include <core/object.h>
#include <core/handle.h>
#include <core/class.h>

#include <engine/dmaobj.h>
#include <engine/fifo.h>

int
nouveau_fifo_channel_create_(struct nouveau_object *parent,
			     struct nouveau_object *engine,
			     struct nouveau_oclass *oclass,
			     int bar, u32 addr, u32 size, u32 pushbuf,
			     u64 engmask, int len, void **ptr)
{
	struct nouveau_device *device = nv_device(engine);
	struct nouveau_fifo *priv = (void *)engine;
	struct nouveau_fifo_chan *chan;
	struct nouveau_dmaeng *dmaeng;
	unsigned long flags;
	int ret;

	/* create base object class */
	ret = nouveau_namedb_create_(parent, engine, oclass, 0, NULL,
				     engmask, len, ptr);
	chan = *ptr;
	if (ret)
		return ret;

	/* validate dma object representing push buffer */
	chan->pushdma = (void *)nouveau_handle_ref(parent, pushbuf);
	if (!chan->pushdma)
		return -ENOENT;

	dmaeng = (void *)chan->pushdma->base.engine;
	switch (chan->pushdma->base.oclass->handle) {
	case NV_DMA_FROM_MEMORY_CLASS:
	case NV_DMA_IN_MEMORY_CLASS:
		break;
	default:
		return -EINVAL;
	}

	ret = dmaeng->bind(dmaeng, parent, chan->pushdma, &chan->pushgpu);
	if (ret)
		return ret;

	/* find a free fifo channel */
	spin_lock_irqsave(&priv->lock, flags);
	for (chan->chid = priv->min; chan->chid < priv->max; chan->chid++) {
		if (!priv->channel[chan->chid]) {
			priv->channel[chan->chid] = nv_object(chan);
			break;
		}
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	if (chan->chid == priv->max) {
		nv_error(priv, "no free channels\n");
		return -ENOSPC;
	}

	/* map fifo control registers */
	chan->user = ioremap(pci_resource_start(device->pdev, bar) + addr +
			     (chan->chid * size), size);
	if (!chan->user)
		return -EFAULT;

	chan->size = size;
	return 0;
}

void
nouveau_fifo_channel_destroy(struct nouveau_fifo_chan *chan)
{
	struct nouveau_fifo *priv = (void *)nv_object(chan)->engine;
	unsigned long flags;

	iounmap(chan->user);

	spin_lock_irqsave(&priv->lock, flags);
	priv->channel[chan->chid] = NULL;
	spin_unlock_irqrestore(&priv->lock, flags);

	nouveau_gpuobj_ref(NULL, &chan->pushgpu);
	nouveau_object_ref(NULL, (struct nouveau_object **)&chan->pushdma);
	nouveau_namedb_destroy(&chan->base);
}

void
_nouveau_fifo_channel_dtor(struct nouveau_object *object)
{
	struct nouveau_fifo_chan *chan = (void *)object;
	nouveau_fifo_channel_destroy(chan);
}

u32
_nouveau_fifo_channel_rd32(struct nouveau_object *object, u64 addr)
{
	struct nouveau_fifo_chan *chan = (void *)object;
	return ioread32_native(chan->user + addr);
}

void
_nouveau_fifo_channel_wr32(struct nouveau_object *object, u64 addr, u32 data)
{
	struct nouveau_fifo_chan *chan = (void *)object;
	iowrite32_native(data, chan->user + addr);
}

static int
nouveau_fifo_chid(struct nouveau_fifo *priv, struct nouveau_object *object)
{
	int engidx = nv_hclass(priv) & 0xff;

	while (object && object->parent) {
		if ( nv_iclass(object->parent, NV_ENGCTX_CLASS) &&
		    (nv_hclass(object->parent) & 0xff) == engidx)
			return nouveau_fifo_chan(object)->chid;
		object = object->parent;
	}

	return -1;
}

void
nouveau_fifo_destroy(struct nouveau_fifo *priv)
{
	kfree(priv->channel);
	nouveau_engine_destroy(&priv->base);
}

int
nouveau_fifo_create_(struct nouveau_object *parent,
		     struct nouveau_object *engine,
		     struct nouveau_oclass *oclass,
		     int min, int max, int length, void **pobject)
{
	struct nouveau_fifo *priv;
	int ret;

	ret = nouveau_engine_create_(parent, engine, oclass, true, "PFIFO",
				     "fifo", length, pobject);
	priv = *pobject;
	if (ret)
		return ret;

	priv->min = min;
	priv->max = max;
	priv->channel = kzalloc(sizeof(*priv->channel) * (max + 1), GFP_KERNEL);
	if (!priv->channel)
		return -ENOMEM;

	priv->chid = nouveau_fifo_chid;
	spin_lock_init(&priv->lock);
	return 0;
}
