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
#ifndef __ASM_TXX9_NDFMC_H
#define __ASM_TXX9_NDFMC_H

#define NDFMC_PLAT_FLAG_USE_BSPRT	0x01
#define NDFMC_PLAT_FLAG_NO_RSTR		0x02
#define NDFMC_PLAT_FLAG_HOLDADD		0x04
#define NDFMC_PLAT_FLAG_DUMMYWRITE	0x08

struct txx9ndfmc_platform_data {
	unsigned int shift;
	unsigned int gbus_clock;
	unsigned int hold;		/* hold time in nanosecond */
	unsigned int spw;		/* strobe pulse width in nanosecond */
	unsigned int flags;
	unsigned char ch_mask;		/* available channel bitmask */
	unsigned char wp_mask;		/* write-protect bitmask */
	unsigned char wide_mask;	/* 16bit-nand bitmask */
};

void txx9_ndfmc_init(unsigned long baseaddr,
		     const struct txx9ndfmc_platform_data *plat_data);

#endif /* __ASM_TXX9_NDFMC_H */
