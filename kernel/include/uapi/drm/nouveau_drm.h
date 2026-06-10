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
#ifndef __NOUVEAU_DRM_H__
#define __NOUVEAU_DRM_H__

#define NOUVEAU_GEM_DOMAIN_CPU       (1 << 0)
#define NOUVEAU_GEM_DOMAIN_VRAM      (1 << 1)
#define NOUVEAU_GEM_DOMAIN_GART      (1 << 2)
#define NOUVEAU_GEM_DOMAIN_MAPPABLE  (1 << 3)

#define NOUVEAU_GEM_TILE_COMP        0x00030000 /* nv50-only */
#define NOUVEAU_GEM_TILE_LAYOUT_MASK 0x0000ff00
#define NOUVEAU_GEM_TILE_16BPP       0x00000001
#define NOUVEAU_GEM_TILE_32BPP       0x00000002
#define NOUVEAU_GEM_TILE_ZETA        0x00000004
#define NOUVEAU_GEM_TILE_NONCONTIG   0x00000008

struct drm_nouveau_gem_info {
	uint32_t handle;
	uint32_t domain;
	uint64_t size;
	uint64_t offset;
	uint64_t map_handle;
	uint32_t tile_mode;
	uint32_t tile_flags;
};

struct drm_nouveau_gem_new {
	struct drm_nouveau_gem_info info;
	uint32_t channel_hint;
	uint32_t align;
};

#define NOUVEAU_GEM_MAX_BUFFERS 1024
struct drm_nouveau_gem_pushbuf_bo_presumed {
	uint32_t valid;
	uint32_t domain;
	uint64_t offset;
};

struct drm_nouveau_gem_pushbuf_bo {
	uint64_t user_priv;
	uint32_t handle;
	uint32_t read_domains;
	uint32_t write_domains;
	uint32_t valid_domains;
	struct drm_nouveau_gem_pushbuf_bo_presumed presumed;
};

#define NOUVEAU_GEM_RELOC_LOW  (1 << 0)
#define NOUVEAU_GEM_RELOC_HIGH (1 << 1)
#define NOUVEAU_GEM_RELOC_OR   (1 << 2)
#define NOUVEAU_GEM_MAX_RELOCS 1024
struct drm_nouveau_gem_pushbuf_reloc {
	uint32_t reloc_bo_index;
	uint32_t reloc_bo_offset;
	uint32_t bo_index;
	uint32_t flags;
	uint32_t data;
	uint32_t vor;
	uint32_t tor;
};

#define NOUVEAU_GEM_MAX_PUSH 512
struct drm_nouveau_gem_pushbuf_push {
	uint32_t bo_index;
	uint32_t pad;
	uint64_t offset;
	uint64_t length;
};

struct drm_nouveau_gem_pushbuf {
	uint32_t channel;
	uint32_t nr_buffers;
	uint64_t buffers;
	uint32_t nr_relocs;
	uint32_t nr_push;
	uint64_t relocs;
	uint64_t push;
	uint32_t suffix0;
	uint32_t suffix1;
	uint64_t vram_available;
	uint64_t gart_available;
};

#define NOUVEAU_GEM_CPU_PREP_NOWAIT                                  0x00000001
#define NOUVEAU_GEM_CPU_PREP_WRITE                                   0x00000004
struct drm_nouveau_gem_cpu_prep {
	uint32_t handle;
	uint32_t flags;
};

struct drm_nouveau_gem_cpu_fini {
	uint32_t handle;
};

#define DRM_NOUVEAU_GETPARAM           0x00 /* deprecated */
#define DRM_NOUVEAU_SETPARAM           0x01 /* deprecated */
#define DRM_NOUVEAU_CHANNEL_ALLOC      0x02 /* deprecated */
#define DRM_NOUVEAU_CHANNEL_FREE       0x03 /* deprecated */
#define DRM_NOUVEAU_GROBJ_ALLOC        0x04 /* deprecated */
#define DRM_NOUVEAU_NOTIFIEROBJ_ALLOC  0x05 /* deprecated */
#define DRM_NOUVEAU_GPUOBJ_FREE        0x06 /* deprecated */
#define DRM_NOUVEAU_GEM_NEW            0x40
#define DRM_NOUVEAU_GEM_PUSHBUF        0x41
#define DRM_NOUVEAU_GEM_CPU_PREP       0x42
#define DRM_NOUVEAU_GEM_CPU_FINI       0x43
#define DRM_NOUVEAU_GEM_INFO           0x44

#define DRM_IOCTL_NOUVEAU_GEM_NEW            DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_NEW, struct drm_nouveau_gem_new)
#define DRM_IOCTL_NOUVEAU_GEM_PUSHBUF        DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_PUSHBUF, struct drm_nouveau_gem_pushbuf)
#define DRM_IOCTL_NOUVEAU_GEM_CPU_PREP       DRM_IOW (DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_CPU_PREP, struct drm_nouveau_gem_cpu_prep)
#define DRM_IOCTL_NOUVEAU_GEM_CPU_FINI       DRM_IOW (DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_CPU_FINI, struct drm_nouveau_gem_cpu_fini)
#define DRM_IOCTL_NOUVEAU_GEM_INFO           DRM_IOWR(DRM_COMMAND_BASE + DRM_NOUVEAU_GEM_INFO, struct drm_nouveau_gem_info)

#endif /* __NOUVEAU_DRM_H__ */
