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
#ifndef _ASM_IA64_XEN_EVENTS_H
#define _ASM_IA64_XEN_EVENTS_H

enum ipi_vector {
	XEN_RESCHEDULE_VECTOR,
	XEN_IPI_VECTOR,
	XEN_CMCP_VECTOR,
	XEN_CPEP_VECTOR,

	XEN_NR_IPIS,
};

static inline int xen_irqs_disabled(struct pt_regs *regs)
{
	return !(ia64_psr(regs)->i);
}

#define irq_ctx_init(cpu)	do { } while (0)

#endif /* _ASM_IA64_XEN_EVENTS_H */
