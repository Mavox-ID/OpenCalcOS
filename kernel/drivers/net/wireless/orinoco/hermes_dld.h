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
#ifndef _HERMES_DLD_H
#define _HERMES_DLD_H

#include "hermes.h"

int hermesi_program_init(struct hermes *hw, u32 offset);
int hermesi_program_end(struct hermes *hw);
int hermes_program(struct hermes *hw, const char *first_block, const void *end);

int hermes_read_pda(struct hermes *hw,
		    __le16 *pda,
		    u32 pda_addr,
		    u16 pda_len,
		    int use_eeprom);
int hermes_apply_pda(struct hermes *hw,
		     const char *first_pdr,
		     const void *pdr_end,
		     const __le16 *pda,
		     const void *pda_end);
int hermes_apply_pda_with_defaults(struct hermes *hw,
				   const char *first_pdr,
				   const void *pdr_end,
				   const __le16 *pda,
				   const void *pda_end);

size_t hermes_blocks_length(const char *first_block, const void *end);

#endif /* _HERMES_DLD_H */
