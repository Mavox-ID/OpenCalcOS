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
#ifndef XEN_HVM_H__
#define XEN_HVM_H__

#include <xen/interface/hvm/params.h>
#include <asm/xen/hypercall.h>

static const char *param_name(int op)
{
#define PARAM(x) [HVM_PARAM_##x] = #x
	static const char *const names[] = {
		PARAM(CALLBACK_IRQ),
		PARAM(STORE_PFN),
		PARAM(STORE_EVTCHN),
		PARAM(PAE_ENABLED),
		PARAM(IOREQ_PFN),
		PARAM(BUFIOREQ_PFN),
		PARAM(TIMER_MODE),
		PARAM(HPET_ENABLED),
		PARAM(IDENT_PT),
		PARAM(DM_DOMAIN),
		PARAM(ACPI_S_STATE),
		PARAM(VM86_TSS),
		PARAM(VPT_ALIGN),
		PARAM(CONSOLE_PFN),
		PARAM(CONSOLE_EVTCHN),
	};
#undef PARAM

	if (op >= ARRAY_SIZE(names))
		return "unknown";

	if (!names[op])
		return "reserved";

	return names[op];
}
static inline int hvm_get_parameter(int idx, uint64_t *value)
{
	struct xen_hvm_param xhv;
	int r;

	xhv.domid = DOMID_SELF;
	xhv.index = idx;
	r = HYPERVISOR_hvm_op(HVMOP_get_param, &xhv);
	if (r < 0) {
		printk(KERN_ERR "Cannot get hvm parameter %s (%d): %d!\n",
			param_name(idx), idx, r);
		return r;
	}
	*value = xhv.value;
	return r;
}

#define HVM_CALLBACK_VIA_TYPE_VECTOR 0x2
#define HVM_CALLBACK_VIA_TYPE_SHIFT 56
#define HVM_CALLBACK_VECTOR(x) (((uint64_t)HVM_CALLBACK_VIA_TYPE_VECTOR)<<\
		HVM_CALLBACK_VIA_TYPE_SHIFT | (x))

#endif /* XEN_HVM_H__ */
