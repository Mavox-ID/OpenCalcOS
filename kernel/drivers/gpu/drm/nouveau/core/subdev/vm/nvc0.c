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
#include <core/device.h>
#include <core/gpuobj.h>

#include <subdev/timer.h>
#include <subdev/fb.h>
#include <subdev/vm.h>

struct nvc0_vmmgr_priv {
	struct nouveau_vmmgr base;
	spinlock_t lock;
};

static void
nvc0_vm_map_pgt(struct nouveau_gpuobj *pgd, u32 index,
		struct nouveau_gpuobj *pgt[2])
{
	u32 pde[2] = { 0, 0 };

	if (pgt[0])
		pde[1] = 0x00000001 | (pgt[0]->addr >> 8);
	if (pgt[1])
		pde[0] = 0x00000001 | (pgt[1]->addr >> 8);

	nv_wo32(pgd, (index * 8) + 0, pde[0]);
	nv_wo32(pgd, (index * 8) + 4, pde[1]);
}

static inline u64
nvc0_vm_addr(struct nouveau_vma *vma, u64 phys, u32 memtype, u32 target)
{
	phys >>= 8;

	phys |= 0x00000001; /* present */
	if (vma->access & NV_MEM_ACCESS_SYS)
		phys |= 0x00000002;

	phys |= ((u64)target  << 32);
	phys |= ((u64)memtype << 36);

	return phys;
}

static void
nvc0_vm_map(struct nouveau_vma *vma, struct nouveau_gpuobj *pgt,
	    struct nouveau_mem *mem, u32 pte, u32 cnt, u64 phys, u64 delta)
{
	u32 next = 1 << (vma->node->type - 8);

	phys  = nvc0_vm_addr(vma, phys, mem->memtype, 0);
	pte <<= 3;
	while (cnt--) {
		nv_wo32(pgt, pte + 0, lower_32_bits(phys));
		nv_wo32(pgt, pte + 4, upper_32_bits(phys));
		phys += next;
		pte  += 8;
	}
}

static void
nvc0_vm_map_sg(struct nouveau_vma *vma, struct nouveau_gpuobj *pgt,
	       struct nouveau_mem *mem, u32 pte, u32 cnt, dma_addr_t *list)
{
	u32 target = (vma->access & NV_MEM_ACCESS_NOSNOOP) ? 7 : 5;

	pte <<= 3;
	while (cnt--) {
		u64 phys = nvc0_vm_addr(vma, *list++, mem->memtype, target);
		nv_wo32(pgt, pte + 0, lower_32_bits(phys));
		nv_wo32(pgt, pte + 4, upper_32_bits(phys));
		pte += 8;
	}
}

static void
nvc0_vm_unmap(struct nouveau_gpuobj *pgt, u32 pte, u32 cnt)
{
	pte <<= 3;
	while (cnt--) {
		nv_wo32(pgt, pte + 0, 0x00000000);
		nv_wo32(pgt, pte + 4, 0x00000000);
		pte += 8;
	}
}

void
nvc0_vm_flush_engine(struct nouveau_subdev *subdev, u64 addr, int type)
{
	struct nvc0_vmmgr_priv *priv = (void *)nouveau_vmmgr(subdev);
	unsigned long flags;

	/* looks like maybe a "free flush slots" counter, the
	 * faster you write to 0x100cbc to more it decreases
	 */
	spin_lock_irqsave(&priv->lock, flags);
	if (!nv_wait_ne(subdev, 0x100c80, 0x00ff0000, 0x00000000)) {
		nv_error(subdev, "vm timeout 0: 0x%08x %d\n",
			 nv_rd32(subdev, 0x100c80), type);
	}

	nv_wr32(subdev, 0x100cb8, addr >> 8);
	nv_wr32(subdev, 0x100cbc, 0x80000000 | type);

	/* wait for flush to be queued? */
	if (!nv_wait(subdev, 0x100c80, 0x00008000, 0x00008000)) {
		nv_error(subdev, "vm timeout 1: 0x%08x %d\n",
			 nv_rd32(subdev, 0x100c80), type);
	}
	spin_unlock_irqrestore(&priv->lock, flags);
}

static void
nvc0_vm_flush(struct nouveau_vm *vm)
{
	struct nouveau_vm_pgd *vpgd;

	list_for_each_entry(vpgd, &vm->pgd_list, head) {
		nvc0_vm_flush_engine(nv_subdev(vm->vmm), vpgd->obj->addr, 1);
	}
}

static int
nvc0_vm_create(struct nouveau_vmmgr *vmm, u64 offset, u64 length,
	       u64 mm_offset, struct nouveau_vm **pvm)
{
	return nouveau_vm_create(vmm, offset, length, mm_offset, 4096, pvm);
}

static int
nvc0_vmmgr_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		struct nouveau_oclass *oclass, void *data, u32 size,
		struct nouveau_object **pobject)
{
	struct nvc0_vmmgr_priv *priv;
	int ret;

	ret = nouveau_vmmgr_create(parent, engine, oclass, "VM", "vm", &priv);
	*pobject = nv_object(priv);
	if (ret)
		return ret;

	priv->base.limit = 1ULL << 40;
	priv->base.dma_bits = 40;
	priv->base.pgt_bits  = 27 - 12;
	priv->base.spg_shift = 12;
	priv->base.lpg_shift = 17;
	priv->base.create = nvc0_vm_create;
	priv->base.map_pgt = nvc0_vm_map_pgt;
	priv->base.map = nvc0_vm_map;
	priv->base.map_sg = nvc0_vm_map_sg;
	priv->base.unmap = nvc0_vm_unmap;
	priv->base.flush = nvc0_vm_flush;
	spin_lock_init(&priv->lock);
	return 0;
}

struct nouveau_oclass
nvc0_vmmgr_oclass = {
	.handle = NV_SUBDEV(VM, 0xc0),
	.ofuncs = &(struct nouveau_ofuncs) {
		.ctor = nvc0_vmmgr_ctor,
		.dtor = _nouveau_vmmgr_dtor,
		.init = _nouveau_vmmgr_init,
		.fini = _nouveau_vmmgr_fini,
	},
};
