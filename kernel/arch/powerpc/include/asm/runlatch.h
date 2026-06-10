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
#ifndef _ASM_POWERPC_RUNLATCH_H
#define _ASM_POWERPC_RUNLATCH_H

#ifdef CONFIG_PPC64

extern void __ppc64_runlatch_on(void);
extern void __ppc64_runlatch_off(void);

/*
 * We manually hard enable-disable, this is called
 * in the idle loop and we don't want to mess up
 * with soft-disable/enable & interrupt replay.
 */
#define ppc64_runlatch_off()					\
	do {							\
		if (cpu_has_feature(CPU_FTR_CTRL) &&		\
		    test_thread_local_flags(_TLF_RUNLATCH)) {	\
			unsigned long msr = mfmsr();		\
			__hard_irq_disable();			\
			__ppc64_runlatch_off();			\
			if (msr & MSR_EE)			\
				__hard_irq_enable();		\
		}      						\
	} while (0)

#define ppc64_runlatch_on()					\
	do {							\
		if (cpu_has_feature(CPU_FTR_CTRL) &&		\
		    !test_thread_local_flags(_TLF_RUNLATCH)) {	\
			unsigned long msr = mfmsr();		\
			__hard_irq_disable();			\
			__ppc64_runlatch_on();			\
			if (msr & MSR_EE)			\
				__hard_irq_enable();		\
		}      						\
	} while (0)
#else
#define ppc64_runlatch_on()
#define ppc64_runlatch_off()
#endif /* CONFIG_PPC64 */

#endif /* _ASM_POWERPC_RUNLATCH_H */
