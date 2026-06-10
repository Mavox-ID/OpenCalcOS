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
#include <beep/sched.h>
#include <beep/kernel.h>
#include <beep/param.h>
#include <beep/interrupt.h>
#include <beep/init.h>
#include <beep/irq.h>
#include <beep/device.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/rtc.h>
#include <asm/machvec.h>
#include <mach/sysasic.h>

static void __init dreamcast_setup(char **cmdline_p)
{
	board_time_init = aica_time_init;
}

static struct sh_machine_vector mv_dreamcast __initmv = {
	.mv_name		= "Sega Dreamcast",
	.mv_setup		= dreamcast_setup,
	.mv_irq_demux		= systemasic_irq_demux,
	.mv_init_irq		= systemasic_irq_init,
};
