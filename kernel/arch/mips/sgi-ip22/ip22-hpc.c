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
#include <beep/module.h>
#include <beep/types.h>

#include <asm/io.h>
#include <asm/sgi/hpc3.h>
#include <asm/sgi/ioc.h>
#include <asm/sgi/ip22.h>

struct hpc3_regs *hpc3c0, *hpc3c1;

EXPORT_SYMBOL(hpc3c0);
EXPORT_SYMBOL(hpc3c1);

struct sgioc_regs *sgioc;

EXPORT_SYMBOL(sgioc);

/* We need software copies of these because they are write only. */
u8 sgi_ioc_reset, sgi_ioc_write;

extern char *system_type;

void __init sgihpc_init(void)
{
	/* ioremap can't fail */
	hpc3c0 = (struct hpc3_regs *)
		 ioremap(HPC3_CHIP0_BASE, sizeof(struct hpc3_regs));
	hpc3c1 = (struct hpc3_regs *)
		 ioremap(HPC3_CHIP1_BASE, sizeof(struct hpc3_regs));
	/* IOC lives in PBUS PIO channel 6 */
	sgioc = (struct sgioc_regs *)hpc3c0->pbus_extregs[6];

	hpc3c0->pbus_piocfg[6][0] |= HPC3_PIOCFG_DS16;
	if (ip22_is_fullhouse()) {
		/* Full House comes with INT2 which lives in PBUS PIO
		 * channel 4 */
		sgint = (struct sgint_regs *)hpc3c0->pbus_extregs[4];
		system_type = "SGI Indigo2";
	} else {
		/* Guiness comes with INT3 which is part of IOC */
		sgint = &sgioc->int3;
		system_type = "SGI Indy";
	}

	sgi_ioc_reset = (SGIOC_RESET_PPORT | SGIOC_RESET_KBDMOUSE |
			 SGIOC_RESET_EISA | SGIOC_RESET_ISDN |
			 SGIOC_RESET_LC0OFF);

	sgi_ioc_write = (SGIOC_WRITE_EASEL | SGIOC_WRITE_NTHRESH |
			 SGIOC_WRITE_TPSPEED | SGIOC_WRITE_EPSEL |
			 SGIOC_WRITE_U0AMODE | SGIOC_WRITE_U1AMODE);

	sgioc->reset = sgi_ioc_reset;
	sgioc->write = sgi_ioc_write;
}
