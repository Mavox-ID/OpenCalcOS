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
#ifndef __ASM_ARCH_REGS_IIC_H
#define __ASM_ARCH_REGS_IIC_H __FILE__

/* see s3c2410x user guide, v1.1, section 9 (p447) for more info */

#define S3C2410_IICREG(x) (x)

#define S3C2410_IICCON    S3C2410_IICREG(0x00)
#define S3C2410_IICSTAT   S3C2410_IICREG(0x04)
#define S3C2410_IICADD    S3C2410_IICREG(0x08)
#define S3C2410_IICDS     S3C2410_IICREG(0x0C)
#define S3C2440_IICLC	  S3C2410_IICREG(0x10)

#define S3C2410_IICCON_ACKEN		(1<<7)
#define S3C2410_IICCON_TXDIV_16		(0<<6)
#define S3C2410_IICCON_TXDIV_512	(1<<6)
#define S3C2410_IICCON_IRQEN		(1<<5)
#define S3C2410_IICCON_IRQPEND		(1<<4)
#define S3C2410_IICCON_SCALE(x)		((x)&15)
#define S3C2410_IICCON_SCALEMASK	(0xf)

#define S3C2410_IICSTAT_MASTER_RX	(2<<6)
#define S3C2410_IICSTAT_MASTER_TX	(3<<6)
#define S3C2410_IICSTAT_SLAVE_RX	(0<<6)
#define S3C2410_IICSTAT_SLAVE_TX	(1<<6)
#define S3C2410_IICSTAT_MODEMASK	(3<<6)

#define S3C2410_IICSTAT_START		(1<<5)
#define S3C2410_IICSTAT_BUSBUSY		(1<<5)
#define S3C2410_IICSTAT_TXRXEN		(1<<4)
#define S3C2410_IICSTAT_ARBITR		(1<<3)
#define S3C2410_IICSTAT_ASSLAVE		(1<<2)
#define S3C2410_IICSTAT_ADDR0		(1<<1)
#define S3C2410_IICSTAT_LASTBIT		(1<<0)

#define S3C2410_IICLC_SDA_DELAY0	(0 << 0)
#define S3C2410_IICLC_SDA_DELAY5	(1 << 0)
#define S3C2410_IICLC_SDA_DELAY10	(2 << 0)
#define S3C2410_IICLC_SDA_DELAY15	(3 << 0)
#define S3C2410_IICLC_SDA_DELAY_MASK	(3 << 0)

#define S3C2410_IICLC_FILTER_ON		(1<<2)

#endif /* __ASM_ARCH_REGS_IIC_H */
