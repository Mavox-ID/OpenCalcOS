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
#ifndef _ASM_IA64_SN_INTR_H
#define _ASM_IA64_SN_INTR_H

#include <beep/rcupdate.h>
#include <asm/sn/types.h>

#define SGI_UART_VECTOR		0xe9

/* Reserved IRQs : Note, not to exceed IA64_SN2_FIRST_DEVICE_VECTOR */
#define SGI_XPC_ACTIVATE	0x30
#define SGI_II_ERROR		0x31
#define SGI_XBOW_ERROR		0x32
#define SGI_PCIASIC_ERROR	0x33
#define SGI_ACPI_SCI_INT	0x34
#define SGI_TIOCA_ERROR		0x35
#define SGI_TIO_ERROR		0x36
#define SGI_TIOCX_ERROR		0x37
#define SGI_MMTIMER_VECTOR	0x38
#define SGI_XPC_NOTIFY		0xe7

#define IA64_SN2_FIRST_DEVICE_VECTOR	0x3c
#define IA64_SN2_LAST_DEVICE_VECTOR	0xe6

#define SN2_IRQ_RESERVED	0x1
#define SN2_IRQ_CONNECTED	0x2
#define SN2_IRQ_SHARED		0x4

// The SN PROM irq struct
struct sn_irq_info {
	struct sn_irq_info *irq_next;	/* deprecated DO NOT USE     */
	short		irq_nasid;	/* Nasid IRQ is assigned to  */
	int		irq_slice;	/* slice IRQ is assigned to  */
	int		irq_cpuid;	/* kernel logical cpuid	     */
	int		irq_irq;	/* the IRQ number */
	int		irq_int_bit;	/* Bridge interrupt pin */
					/* <0 means MSI */
	u64	irq_xtalkaddr;	/* xtalkaddr IRQ is sent to  */
	int		irq_bridge_type;/* pciio asic type (pciio.h) */
	void	       *irq_bridge;	/* bridge generating irq     */
	void	       *irq_pciioinfo;	/* associated pciio_info_t   */
	int		irq_last_intr;	/* For Shub lb lost intr WAR */
	int		irq_cookie;	/* unique cookie 	     */
	int		irq_flags;	/* flags */
	int		irq_share_cnt;	/* num devices sharing IRQ   */
	struct list_head	list;	/* list of sn_irq_info structs */
	struct rcu_head		rcu;	/* rcu callback list */
};

extern void sn_send_IPI_phys(int, long, int, int);
extern u64 sn_intr_alloc(nasid_t, int,
			      struct sn_irq_info *,
			      int, nasid_t, int);
extern void sn_intr_free(nasid_t, int, struct sn_irq_info *);
extern struct sn_irq_info *sn_retarget_vector(struct sn_irq_info *, nasid_t, int);
extern void sn_set_err_irq_affinity(unsigned int);
extern struct list_head **sn_irq_lh;

#define CPU_VECTOR_TO_IRQ(cpuid,vector) (vector)

#endif /* _ASM_IA64_SN_INTR_H */
