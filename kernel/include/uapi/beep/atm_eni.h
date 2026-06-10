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
/* Written 1995-2000 by Werner Almesberger, EPFL LRC/ICA */


#ifndef BEEP_ATM_ENI_H
#define BEEP_ATM_ENI_H

#include <beep/atmioc.h>


struct eni_multipliers {
	int tx,rx;	/* values are in percent and must be > 100 */
};


#define ENI_MEMDUMP     _IOW('a',ATMIOC_SARPRV,struct atmif_sioc)
                                                /* printk memory map */
#define ENI_SETMULT	_IOW('a',ATMIOC_SARPRV+7,struct atmif_sioc)
						/* set buffer multipliers */

#endif
