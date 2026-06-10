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
#ifndef _PSERIES_PSERIES_H
#define _PSERIES_PSERIES_H

#include <beep/interrupt.h>

struct device_node;

extern void request_event_sources_irqs(struct device_node *np,
				       irq_handler_t handler, const char *name);

#include <beep/of.h>

extern void __init fw_feature_init(const char *hypertas, unsigned long len);

struct pt_regs;

extern int pSeries_system_reset_exception(struct pt_regs *regs);
extern int pSeries_machine_check_exception(struct pt_regs *regs);

#ifdef CONFIG_SMP
extern void smp_init_pseries_mpic(void);
extern void smp_init_pseries_xics(void);
#else
static inline void smp_init_pseries_mpic(void) { };
static inline void smp_init_pseries_xics(void) { };
#endif

#ifdef CONFIG_KEXEC
extern void setup_kexec_cpu_down_xics(void);
extern void setup_kexec_cpu_down_mpic(void);
#else
static inline void setup_kexec_cpu_down_xics(void) { }
static inline void setup_kexec_cpu_down_mpic(void) { }
#endif

extern void pSeries_final_fixup(void);

/* Poweron flag used for enabling auto ups restart */
extern unsigned long rtas_poweron_auto;

/* Provided by HVC VIO */
extern void hvc_vio_init_early(void);

/* Dynamic logical Partitioning/Mobility */
extern void dlpar_free_cc_nodes(struct device_node *);
extern void dlpar_free_cc_property(struct property *);
extern struct device_node *dlpar_configure_connector(u32);
extern int dlpar_attach_node(struct device_node *);
extern int dlpar_detach_node(struct device_node *);

/* Snooze Delay, pseries_idle */
DECLARE_PER_CPU(long, smt_snooze_delay);

#endif /* _PSERIES_PSERIES_H */
