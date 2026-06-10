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
#include <beep/io.h>
#include <asm/system_misc.h>
#include <asm/hardware/sp810.h>
#include <mach/spear.h>
#include <mach/generic.h>

#define SPEAR13XX_SYS_SW_RES			(VA_MISC_BASE + 0x204)
void spear_restart(char mode, const char *cmd)
{
	if (mode == 's') {
		/* software reset, Jump into ROM at address 0 */
		soft_restart(0);
	} else {
		/* hardware reset, Use on-chip reset capability */
#ifdef CONFIG_ARCH_SPEAR13XX
		writel_relaxed(0x01, SPEAR13XX_SYS_SW_RES);
#else
		sysctl_soft_reset((void __iomem *)VA_SPEAR_SYS_CTRL_BASE);
#endif
	}
}
