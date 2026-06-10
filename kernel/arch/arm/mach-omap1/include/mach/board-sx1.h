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
#ifndef __ASM_ARCH_SX1_I2C_CHIPS_H
#define __ASM_ARCH_SX1_I2C_CHIPS_H

#define SOFIA_MAX_LIGHT_VAL	0x2B

#define SOFIA_I2C_ADDR		0x32
/* Sofia reg 3 bits masks */
#define SOFIA_POWER1_REG	0x03

#define	SOFIA_USB_POWER		0x01
#define	SOFIA_MMC_POWER		0x04
#define	SOFIA_BLUETOOTH_POWER	0x08
#define	SOFIA_MMILIGHT_POWER	0x20

#define SOFIA_POWER2_REG	0x04
#define SOFIA_BACKLIGHT_REG	0x06
#define SOFIA_KEYLIGHT_REG	0x07
#define SOFIA_DIMMING_REG	0x09


/* Function Prototypes for SX1 devices control on I2C bus */

int sx1_setbacklight(u8 backlight);
int sx1_getbacklight(u8 *backlight);
int sx1_setkeylight(u8 keylight);
int sx1_getkeylight(u8 *keylight);

int sx1_setmmipower(u8 onoff);
int sx1_setusbpower(u8 onoff);
int sx1_i2c_read_byte(u8 devaddr, u8 regoffset, u8 *value);
int sx1_i2c_write_byte(u8 devaddr, u8 regoffset, u8 value);

/* MMC prototypes */

extern void sx1_mmc_init(void);
extern void sx1_mmc_slot_cover_handler(void *arg, int state);

#endif /* __ASM_ARCH_SX1_I2C_CHIPS_H */
