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
#ifndef _MACH_DAVINCI_AEMIF_H
#define _MACH_DAVINCI_AEMIF_H

#define NRCSR_OFFSET		0x00
#define AWCCR_OFFSET		0x04
#define A1CR_OFFSET		0x10

#define ACR_ASIZE_MASK		0x3
#define ACR_EW_MASK		BIT(30)
#define ACR_SS_MASK		BIT(31)

/* All timings in nanoseconds */
struct davinci_aemif_timing {
	u8	wsetup;
	u8	wstrobe;
	u8	whold;

	u8	rsetup;
	u8	rstrobe;
	u8	rhold;

	u8	ta;
};

int davinci_aemif_setup_timing(struct davinci_aemif_timing *t,
					void __iomem *base, unsigned cs);
#endif
