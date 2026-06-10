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
/* bttv address list */
#define I2C_ADDR_TSA5522	0xc2
#define I2C_ADDR_TDA7432	0x8a
#define I2C_ADDR_TDA8425	0x82
#define I2C_ADDR_TDA9840	0x84
#define I2C_ADDR_TDA9850	0xb6 /* also used by 9855,9873 */
#define I2C_ADDR_TDA9874	0xb0 /* also used by 9875 */
#define I2C_ADDR_TDA9875	0xb0
#define I2C_ADDR_HAUPEE		0xa0
#define I2C_ADDR_STBEE		0xae
#define I2C_ADDR_VHX		0xc0
#define I2C_ADDR_MSP3400	0x80
#define I2C_ADDR_MSP3400_ALT	0x88
#define I2C_ADDR_TEA6300	0x80 /* also used by 6320 */
#define I2C_ADDR_DPL3518	0x84
#define I2C_ADDR_TDA9887	0x86

/*
 * i2c bus addresses for the chips supported by tvaudio.c
 */

#define I2C_ADDR_TDA8425	0x82
#define I2C_ADDR_TDA9840	0x84 /* also used by TA8874Z */
#define I2C_ADDR_TDA985x_L	0xb4 /* also used by 9873 */
#define I2C_ADDR_TDA985x_H	0xb6
#define I2C_ADDR_TDA9874	0xb0 /* also used by 9875 */

#define I2C_ADDR_TEA6300	0x80 /* also used by 6320 */
#define I2C_ADDR_TEA6420	0x98

#define I2C_ADDR_PIC16C54	0x96 /* PV951 */
