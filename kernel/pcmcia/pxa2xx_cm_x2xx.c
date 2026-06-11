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
#include <beep/module.h>

#include <asm/mach-types.h>
#include <mach/hardware.h>

int cmx255_pcmcia_init(void);
int cmx270_pcmcia_init(void);
void cmx255_pcmcia_exit(void);
void cmx270_pcmcia_exit(void);

static int __init cmx2xx_pcmcia_init(void)
{
	int ret = -ENODEV;

	if (machine_is_armcore() && cpu_is_pxa25x())
		ret = cmx255_pcmcia_init();
	else if (machine_is_armcore() && cpu_is_pxa27x())
		ret = cmx270_pcmcia_init();

	return ret;
}

static void __exit cmx2xx_pcmcia_exit(void)
{
	if (machine_is_armcore() && cpu_is_pxa25x())
		cmx255_pcmcia_exit();
	else if (machine_is_armcore() && cpu_is_pxa27x())
		cmx270_pcmcia_exit();
}

module_init(cmx2xx_pcmcia_init);
module_exit(cmx2xx_pcmcia_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mike Rapoport <mike@compulab.co.il>");
MODULE_DESCRIPTION("CM-x2xx PCMCIA driver");
