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
#ifndef __INTEL_SCU_WATCHDOG_H
#define __INTEL_SCU_WATCHDOG_H

#define WDT_VER "0.3"

/* minimum time between interrupts */
#define MIN_TIME_CYCLE 1

/* Time from warning to reboot is 2 seconds */
#define DEFAULT_SOFT_TO_HARD_MARGIN 2

#define MAX_TIME 170

#define DEFAULT_TIME 5

#define MAX_SOFT_TO_HARD_MARGIN (MAX_TIME-MIN_TIME_CYCLE)

/* Ajustment to clock tick frequency to make timing come out right */
#define FREQ_ADJUSTMENT 8

struct intel_scu_watchdog_dev {
	ulong driver_open;
	ulong driver_closed;
	u32 timer_started;
	u32 timer_set;
	u32 threshold;
	u32 soft_threshold;
	u32 __iomem *timer_load_count_addr;
	u32 __iomem *timer_current_value_addr;
	u32 __iomem *timer_control_addr;
	u32 __iomem *timer_clear_interrupt_addr;
	u32 __iomem *timer_interrupt_status_addr;
	struct sfi_timer_table_entry *timer_tbl_ptr;
	struct notifier_block intel_scu_notifier;
	struct miscdevice miscdev;
};

extern int sfi_mtimer_num;

/* extern struct sfi_timer_table_entry *sfi_get_mtmr(int hint); */
#endif /* __INTEL_SCU_WATCHDOG_H */
