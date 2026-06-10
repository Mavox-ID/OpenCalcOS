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
#ifndef _BRCM_CHANNEL_H_
#define _BRCM_CHANNEL_H_

/* conversion for phy txpwr calculations that use .25 dB units */
#define BRCMS_TXPWR_DB_FACTOR 4

/* bits for locale_info flags */
#define BRCMS_PEAK_CONDUCTED	0x00	/* Peak for locals */
#define BRCMS_EIRP		0x01	/* Flag for EIRP */
#define BRCMS_DFS_TPC		0x02	/* Flag for DFS TPC */
#define BRCMS_NO_OFDM		0x04	/* Flag for No OFDM */
#define BRCMS_NO_40MHZ		0x08	/* Flag for No MIMO 40MHz */
#define BRCMS_NO_MIMO		0x10	/* Flag for No MIMO, 20 or 40 MHz */
#define BRCMS_RADAR_TYPE_EU       0x20	/* Flag for EU */
#define BRCMS_DFS_FCC             BRCMS_DFS_TPC	/* Flag for DFS FCC */

#define BRCMS_DFS_EU (BRCMS_DFS_TPC | BRCMS_RADAR_TYPE_EU) /* Flag for DFS EU */

extern struct brcms_cm_info *
brcms_c_channel_mgr_attach(struct brcms_c_info *wlc);

extern void brcms_c_channel_mgr_detach(struct brcms_cm_info *wlc_cm);

extern bool brcms_c_valid_chanspec_db(struct brcms_cm_info *wlc_cm,
				      u16 chspec);

extern void brcms_c_channel_reg_limits(struct brcms_cm_info *wlc_cm,
				   u16 chanspec,
				   struct txpwr_limits *txpwr);
extern void brcms_c_channel_set_chanspec(struct brcms_cm_info *wlc_cm,
				     u16 chanspec,
				     u8 local_constraint_qdbm);
extern void brcms_c_regd_init(struct brcms_c_info *wlc);

#endif				/* _WLC_CHANNEL_H */
