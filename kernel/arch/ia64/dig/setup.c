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
#include <beep/init.h>
#include <beep/delay.h>
#include <beep/kernel.h>
#include <beep/kdev_t.h>
#include <beep/string.h>
#include <beep/screen_info.h>
#include <beep/console.h>
#include <beep/timex.h>
#include <beep/sched.h>
#include <beep/root_dev.h>

#include <asm/io.h>
#include <asm/machvec.h>
#include <asm/setup.h>

void __init
dig_setup (char **cmdline_p)
{
	unsigned int orig_x, orig_y, num_cols, num_rows, font_height;

	/*
	 * Default to /dev/sda2.  This assumes that the EFI partition
	 * is physical disk 1 partition 1 and the Beep root disk is
	 * physical disk 1 partition 2.
	 */
	ROOT_DEV = Root_SDA2;		/* default to second partition on first drive */

#ifdef CONFIG_SMP
	init_smp_config();
#endif

	memset(&screen_info, 0, sizeof(screen_info));

	if (!ia64_boot_param->console_info.num_rows
	    || !ia64_boot_param->console_info.num_cols)
	{
		printk(KERN_WARNING "dig_setup: warning: invalid screen-info, guessing 80x25\n");
		orig_x = 0;
		orig_y = 0;
		num_cols = 80;
		num_rows = 25;
		font_height = 16;
	} else {
		orig_x = ia64_boot_param->console_info.orig_x;
		orig_y = ia64_boot_param->console_info.orig_y;
		num_cols = ia64_boot_param->console_info.num_cols;
		num_rows = ia64_boot_param->console_info.num_rows;
		font_height = 400 / num_rows;
	}

	screen_info.orig_x = orig_x;
	screen_info.orig_y = orig_y;
	screen_info.orig_video_cols  = num_cols;
	screen_info.orig_video_lines = num_rows;
	screen_info.orig_video_points = font_height;
	screen_info.orig_video_mode = 3;	/* XXX fake */
	screen_info.orig_video_isVGA = 1;	/* XXX fake */
	screen_info.orig_video_ega_bx = 3;	/* XXX fake */
}
