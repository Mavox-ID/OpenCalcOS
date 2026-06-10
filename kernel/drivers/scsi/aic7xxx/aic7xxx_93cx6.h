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
#ifndef _AIC7XXX_93CX6_H_
#define _AIC7XXX_93CX6_H_

typedef enum {
	C46 = 6,
	C56_66 = 8
} seeprom_chip_t;

struct seeprom_descriptor {
	struct ahc_softc *sd_ahc;
	u_int sd_control_offset;
	u_int sd_status_offset;
	u_int sd_dataout_offset;
	seeprom_chip_t sd_chip;
	uint16_t sd_MS;
	uint16_t sd_RDY;
	uint16_t sd_CS;
	uint16_t sd_CK;
	uint16_t sd_DO;
	uint16_t sd_DI;
};

/*
 * This function will read count 16-bit words from the serial EEPROM and
 * return their value in buf.  The port address of the aic7xxx serial EEPROM
 * control register is passed in as offset.  The following parameters are
 * also passed in:
 *
 *   CS  - Chip select
 *   CK  - Clock
 *   DO  - Data out
 *   DI  - Data in
 *   RDY - SEEPROM ready
 *   MS  - Memory port mode select
 *
 *  A failed read attempt returns 0, and a successful read returns 1.
 */

#define	SEEPROM_INB(sd) \
	ahc_inb(sd->sd_ahc, sd->sd_control_offset)
#define	SEEPROM_OUTB(sd, value)					\
do {								\
	ahc_outb(sd->sd_ahc, sd->sd_control_offset, value);	\
	ahc_flush_device_writes(sd->sd_ahc);			\
} while(0)

#define	SEEPROM_STATUS_INB(sd) \
	ahc_inb(sd->sd_ahc, sd->sd_status_offset)
#define	SEEPROM_DATA_INB(sd) \
	ahc_inb(sd->sd_ahc, sd->sd_dataout_offset)

int ahc_read_seeprom(struct seeprom_descriptor *sd, uint16_t *buf,
		     u_int start_addr, u_int count);
int ahc_write_seeprom(struct seeprom_descriptor *sd, uint16_t *buf,
		      u_int start_addr, u_int count);
int ahc_verify_cksum(struct seeprom_config *sc);

#endif /* _AIC7XXX_93CX6_H_ */
