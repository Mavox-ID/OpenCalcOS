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
#ifndef __ASM_ARM_ARCH_UDC_H
#define __ASM_ARM_ARCH_UDC_H

enum s3c2410_udc_cmd_e {
	S3C2410_UDC_P_ENABLE	= 1,	/* Pull-up enable        */
	S3C2410_UDC_P_DISABLE	= 2,	/* Pull-up disable       */
	S3C2410_UDC_P_RESET	= 3,	/* UDC reset, in case of */
};

struct s3c2410_udc_mach_info {
	void	(*udc_command)(enum s3c2410_udc_cmd_e);
	void	(*vbus_draw)(unsigned int ma);

	unsigned int pullup_pin;
	unsigned int pullup_pin_inverted;

	unsigned int vbus_pin;
	unsigned char vbus_pin_inverted;
};

extern void __init s3c24xx_udc_set_platdata(struct s3c2410_udc_mach_info *);

struct s3c24xx_hsudc_platdata;

extern void __init s3c24xx_hsudc_set_platdata(struct s3c24xx_hsudc_platdata *pd);

#endif /* __ASM_ARM_ARCH_UDC_H */
