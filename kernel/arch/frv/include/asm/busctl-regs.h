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
#ifndef _ASM_BUSCTL_REGS_H
#define _ASM_BUSCTL_REGS_H

/* bus controller registers */
#define __get_LGCR()	({ *(volatile unsigned long *)(0xfe000010); })
#define __get_LMAICR()	({ *(volatile unsigned long *)(0xfe000030); })
#define __get_LEMBR()	({ *(volatile unsigned long *)(0xfe000040); })
#define __get_LEMAM()	({ *(volatile unsigned long *)(0xfe000048); })
#define __get_LCR(R)	({ *(volatile unsigned long *)(0xfe000100 + 8*(R)); })
#define __get_LSBR(R)	({ *(volatile unsigned long *)(0xfe000c00 + 8*(R)); })
#define __get_LSAM(R)	({ *(volatile unsigned long *)(0xfe000d00 + 8*(R)); })

#define __set_LGCR(V)	do { *(volatile unsigned long *)(0xfe000010) = (V); } while(0)
#define __set_LMAICR(V)	do { *(volatile unsigned long *)(0xfe000030) = (V); } while(0)
#define __set_LEMBR(V)	do { *(volatile unsigned long *)(0xfe000040) = (V); } while(0)
#define __set_LEMAM(V)	do { *(volatile unsigned long *)(0xfe000048) = (V); } while(0)
#define __set_LCR(R,V)	do { *(volatile unsigned long *)(0xfe000100 + 8*(R)) = (V); } while(0)
#define __set_LSBR(R,V)	do { *(volatile unsigned long *)(0xfe000c00 + 8*(R)) = (V); } while(0)
#define __set_LSAM(R,V)	do { *(volatile unsigned long *)(0xfe000d00 + 8*(R)) = (V); } while(0)

/* FR401 SDRAM controller registers */
#define __get_DBR(R)	({ *(volatile unsigned long *)(0xfe000e00 + 8*(R)); })
#define __get_DAM(R)	({ *(volatile unsigned long *)(0xfe000f00 + 8*(R)); })

/* FR551 SDRAM controller registers */
#define __get_DARS(R)	({ *(volatile unsigned long *)(0xfeff0100 + 8*(R)); })
#define __get_DAMK(R)	({ *(volatile unsigned long *)(0xfeff0110 + 8*(R)); })


#endif /* _ASM_BUSCTL_REGS_H */
