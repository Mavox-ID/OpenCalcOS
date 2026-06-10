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
#ifndef _UAPI__KERNELCAPI_H__
#define _UAPI__KERNELCAPI_H__

#define CAPI_MAXAPPL	240	/* maximum number of applications  */
#define CAPI_MAXCONTR	32	/* maximum number of controller    */
#define CAPI_MAXDATAWINDOW	8


typedef struct kcapi_flagdef {
	int contr;
	int flag;
} kcapi_flagdef;

typedef struct kcapi_carddef {
	char		driver[32];
	unsigned int	port;
	unsigned	irq;
	unsigned int	membase;
	int		cardnr;
} kcapi_carddef;

/* new ioctls >= 10 */
#define KCAPI_CMD_TRACE		10
#define KCAPI_CMD_ADDCARD	11	/* OBSOLETE */

/* 
 * flag > 2 => trace also data
 * flag & 1 => show trace
 */
#define KCAPI_TRACE_OFF			0
#define KCAPI_TRACE_SHORT_NO_DATA	1
#define KCAPI_TRACE_FULL_NO_DATA	2
#define KCAPI_TRACE_SHORT		3
#define KCAPI_TRACE_FULL		4



#endif /* _UAPI__KERNELCAPI_H__ */
