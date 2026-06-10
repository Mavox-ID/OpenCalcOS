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
#ifndef __ASM_PLAT_ATA_H
#define __ASM_PLAT_ATA_H __FILE__

/**
 * struct s3c_ide_platdata - S3C IDE driver platform data.
 * @setup_gpio: Setup the external GPIO pins to the right state for data
 * transfer in true-ide mode.
 */
struct s3c_ide_platdata {
	void (*setup_gpio)(void);
};

/*
 * s3c_ide_set_platdata() - Setup the platform specifc data for IDE driver.
 * @pdata: Platform data for IDE driver.
 */
extern void s3c_ide_set_platdata(struct s3c_ide_platdata *pdata);

/* architecture-specific IDE configuration */
extern void s3c64xx_ide_setup_gpio(void);
extern void s5pc100_ide_setup_gpio(void);
extern void s5pv210_ide_setup_gpio(void);

#endif /*__ASM_PLAT_ATA_H */
