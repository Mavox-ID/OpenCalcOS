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
#ifndef _AIC94XX_DUMP_H_
#define _AIC94XX_DUMP_H_

#ifdef ASD_DEBUG

void asd_dump_seq_state(struct asd_ha_struct *asd_ha, u8 lseq_mask);
void asd_dump_frame_rcvd(struct asd_phy *phy,
			 struct done_list_struct *dl);
#else /* ASD_DEBUG */

static inline void asd_dump_seq_state(struct asd_ha_struct *asd_ha,
				      u8 lseq_mask) { }
static inline void asd_dump_frame_rcvd(struct asd_phy *phy,
				       struct done_list_struct *dl) { }
#endif /* ASD_DEBUG */

#endif /* _AIC94XX_DUMP_H_ */
