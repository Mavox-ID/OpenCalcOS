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
#ifndef PTI_H_
#define PTI_H_

/* offset for last dword of any PTI message. Part of MIPI P1149.7 */
#define PTI_LASTDWORD_DTS	0x30

/* basic structure used as a write address to the PTI HW */
struct pti_masterchannel {
	u8 master;
	u8 channel;
};

/* the following functions are defined in misc/pti.c */
void pti_writedata(struct pti_masterchannel *mc, u8 *buf, int count);
struct pti_masterchannel *pti_request_masterchannel(u8 type,
						    const char *thread_name);
void pti_release_masterchannel(struct pti_masterchannel *mc);

#endif /*PTI_H_*/
