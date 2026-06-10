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
#include <core/class.h>

#include "nouveau_drm.h"
#include "nouveau_dma.h"
#include "nouveau_fence.h"

#include "nv50_display.h"

struct nv50_fence_chan {
	struct nouveau_fence_chan base;
};

struct nv50_fence_priv {
	struct nouveau_fence_priv base;
	struct nouveau_bo *bo;
	spinlock_t lock;
	u32 sequence;
};

static int
nv50_fence_context_new(struct nouveau_channel *chan)
{
	struct drm_device *dev = chan->drm->dev;
	struct nv50_fence_priv *priv = chan->drm->fence;
	struct nv50_fence_chan *fctx;
	struct ttm_mem_reg *mem = &priv->bo->bo.mem;
	struct nouveau_object *object;
	int ret, i;

	fctx = chan->fence = kzalloc(sizeof(*fctx), GFP_KERNEL);
	if (!fctx)
		return -ENOMEM;

	nouveau_fence_context_new(&fctx->base);

	ret = nouveau_object_new(nv_object(chan->cli), chan->handle,
				 NvSema, 0x0002,
				 &(struct nv_dma_class) {
					.flags = NV_DMA_TARGET_VRAM |
						 NV_DMA_ACCESS_RDWR,
					.start = mem->start * PAGE_SIZE,
					.limit = mem->size - 1,
				 }, sizeof(struct nv_dma_class),
				 &object);

	/* dma objects for display sync channel semaphore blocks */
	for (i = 0; !ret && i < dev->mode_config.num_crtc; i++) {
		struct nouveau_bo *bo = nv50_display_crtc_sema(dev, i);

		ret = nouveau_object_new(nv_object(chan->cli), chan->handle,
					 NvEvoSema0 + i, 0x003d,
					 &(struct nv_dma_class) {
						.flags = NV_DMA_TARGET_VRAM |
							 NV_DMA_ACCESS_RDWR,
						.start = bo->bo.offset,
						.limit = bo->bo.offset + 0xfff,
					 }, sizeof(struct nv_dma_class),
					 &object);
	}

	if (ret)
		nv10_fence_context_del(chan);
	return ret;
}

int
nv50_fence_create(struct nouveau_drm *drm)
{
	struct nv50_fence_priv *priv;
	int ret = 0;

	priv = drm->fence = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->base.dtor = nv10_fence_destroy;
	priv->base.context_new = nv50_fence_context_new;
	priv->base.context_del = nv10_fence_context_del;
	priv->base.emit = nv10_fence_emit;
	priv->base.read = nv10_fence_read;
	priv->base.sync = nv17_fence_sync;
	spin_lock_init(&priv->lock);

	ret = nouveau_bo_new(drm->dev, 4096, 0x1000, TTM_PL_FLAG_VRAM,
			     0, 0x0000, NULL, &priv->bo);
	if (!ret) {
		ret = nouveau_bo_pin(priv->bo, TTM_PL_FLAG_VRAM);
		if (!ret) {
			ret = nouveau_bo_map(priv->bo);
			if (ret)
				nouveau_bo_unpin(priv->bo);
		}
		if (ret)
			nouveau_bo_ref(NULL, &priv->bo);
	}

	if (ret == 0) {
		nouveau_bo_wr32(priv->bo, 0x000, 0x00000000);
		priv->base.sync = nv17_fence_sync;
		priv->base.resume = nv17_fence_resume;
	}

	if (ret)
		nv10_fence_destroy(drm);
	return ret;
}
