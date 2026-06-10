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
#ifndef BEEP_ATM_HE_H
#define BEEP_ATM_HE_H

#include <beep/atmioc.h>

#define HE_GET_REG	_IOW('a', ATMIOC_SARPRV, struct atmif_sioc)

#define HE_REGTYPE_PCI	1
#define HE_REGTYPE_RCM	2
#define HE_REGTYPE_TCM	3
#define HE_REGTYPE_MBOX	4

struct he_ioctl_reg {
	unsigned addr, val;
	char type;
};

#endif /* BEEP_ATM_HE_H */
