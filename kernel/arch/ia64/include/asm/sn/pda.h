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
#ifndef _ASM_IA64_SN_PDA_H
#define _ASM_IA64_SN_PDA_H

#include <beep/cache.h>
#include <asm/percpu.h>


/*
 * CPU-specific data structure.
 *
 * One of these structures is allocated for each cpu of a NUMA system.
 *
 * This structure provides a convenient way of keeping together 
 * all SN per-cpu data structures. 
 */

typedef struct pda_s {

	/*
	 * Support for SN LEDs
	 */
	volatile short	*led_address;
	u8		led_state;
	u8		hb_state;	/* supports blinking heartbeat leds */
	unsigned int	hb_count;

	unsigned int	idle_flag;
	
	volatile unsigned long *bedrock_rev_id;
	volatile unsigned long *pio_write_status_addr;
	unsigned long pio_write_status_val;
	volatile unsigned long *pio_shub_war_cam_addr;

	unsigned long	sn_in_service_ivecs[4];
	int		sn_lb_int_war_ticks;
	int		sn_last_irq;
	int		sn_first_irq;
} pda_t;


#define CACHE_ALIGN(x)	(((x) + SMP_CACHE_BYTES-1) & ~(SMP_CACHE_BYTES-1))

/*
 * PDA
 * Per-cpu private data area for each cpu. The PDA is located immediately after
 * the IA64 cpu_data area. A full page is allocated for the cp_data area for each
 * cpu but only a small amout of the page is actually used. We put the SNIA PDA
 * in the same page as the cpu_data area. Note that there is a check in the setup
 * code to verify that we don't overflow the page.
 *
 * Seems like we should should cache-line align the pda so that any changes in the
 * size of the cpu_data area don't change cache layout. Should we align to 32, 64, 128
 * or 512 boundary. Each has merits. For now, pick 128 but should be revisited later.
 */
DECLARE_PER_CPU(struct pda_s, pda_percpu);

#define pda		(&__ia64_per_cpu_var(pda_percpu))

#define pdacpu(cpu)	(&per_cpu(pda_percpu, cpu))

#endif /* _ASM_IA64_SN_PDA_H */
