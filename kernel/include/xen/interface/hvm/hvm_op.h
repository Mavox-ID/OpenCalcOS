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
#ifndef __XEN_PUBLIC_HVM_HVM_OP_H__
#define __XEN_PUBLIC_HVM_HVM_OP_H__

/* Get/set subcommands: the second argument of the hypercall is a
 * pointer to a xen_hvm_param struct. */
#define HVMOP_set_param           0
#define HVMOP_get_param           1
struct xen_hvm_param {
    domid_t  domid;    /* IN */
    uint32_t index;    /* IN */
    uint64_t value;    /* IN/OUT */
};
DEFINE_GUEST_HANDLE_STRUCT(xen_hvm_param);

/* Hint from PV drivers for pagetable destruction. */
#define HVMOP_pagetable_dying       9
struct xen_hvm_pagetable_dying {
    /* Domain with a pagetable about to be destroyed. */
    domid_t  domid;
    /* guest physical address of the toplevel pagetable dying */
    aligned_u64 gpa;
};
typedef struct xen_hvm_pagetable_dying xen_hvm_pagetable_dying_t;
DEFINE_GUEST_HANDLE_STRUCT(xen_hvm_pagetable_dying_t);
 
enum hvmmem_type_t {
    HVMMEM_ram_rw,             /* Normal read/write guest RAM */
    HVMMEM_ram_ro,             /* Read-only; writes are discarded */
    HVMMEM_mmio_dm,            /* Reads and write go to the device model */
};

#define HVMOP_get_mem_type    15
/* Return hvmmem_type_t for the specified pfn. */
struct xen_hvm_get_mem_type {
    /* Domain to be queried. */
    domid_t domid;
    /* OUT variable. */
    uint16_t mem_type;
    uint16_t pad[2]; /* align next field on 8-byte boundary */
    /* IN variable. */
    uint64_t pfn;
};
DEFINE_GUEST_HANDLE_STRUCT(xen_hvm_get_mem_type);

#endif /* __XEN_PUBLIC_HVM_HVM_OP_H__ */
