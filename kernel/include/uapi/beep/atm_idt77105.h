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
/* Written 1999 by Greg Banks <gnb@beepfan.com>. Copied from atm_suni.h. */


#ifndef BEEP_ATM_IDT77105_H
#define BEEP_ATM_IDT77105_H

#include <beep/types.h>
#include <beep/atmioc.h>
#include <beep/atmdev.h>

/*
 * Structure for IDT77105_GETSTAT and IDT77105_GETSTATZ ioctls.
 * Pointed to by `arg' in atmif_sioc.
 */
struct idt77105_stats {
        __u32 symbol_errors;  /* wire symbol errors */
        __u32 tx_cells;       /* cells transmitted */
        __u32 rx_cells;       /* cells received */
        __u32 rx_hec_errors;  /* Header Error Check errors on receive */
};

#define IDT77105_GETSTAT	_IOW('a',ATMIOC_PHYPRV+2,struct atmif_sioc)	/* get stats */
#define IDT77105_GETSTATZ	_IOW('a',ATMIOC_PHYPRV+3,struct atmif_sioc)	/* get stats and zero */

#endif
