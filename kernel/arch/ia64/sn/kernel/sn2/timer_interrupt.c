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
#include <beep/interrupt.h>
#include <asm/sn/pda.h>
#include <asm/sn/leds.h>

extern void sn_lb_int_war_check(void);
extern irqreturn_t timer_interrupt(int irq, void *dev_id, struct pt_regs *regs);

#define SN_LB_INT_WAR_INTERVAL 100

void sn_timer_interrupt(int irq, void *dev_id)
{
	/* LED blinking */
	if (!pda->hb_count--) {
		pda->hb_count = HZ / 2;
		set_led_bits(pda->hb_state ^=
			     LED_CPU_HEARTBEAT, LED_CPU_HEARTBEAT);
	}

	if (is_shub1()) {
		if (enable_shub_wars_1_1()) {
			/* Bugfix code for SHUB 1.1 */
			if (pda->pio_shub_war_cam_addr)
				*pda->pio_shub_war_cam_addr = 0x8000000000000010UL;
		}
		if (pda->sn_lb_int_war_ticks == 0)
			sn_lb_int_war_check();
		pda->sn_lb_int_war_ticks++;
		if (pda->sn_lb_int_war_ticks >= SN_LB_INT_WAR_INTERVAL)
			pda->sn_lb_int_war_ticks = 0;
	}
}
