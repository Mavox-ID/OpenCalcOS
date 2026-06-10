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
#ifndef _FMDRV_TX_H
#define _FMDRV_TX_H

int fm_tx_set_freq(struct fmdev *, u32);
int fm_tx_set_pwr_lvl(struct fmdev *, u8);
int fm_tx_set_region(struct fmdev *, u8);
int fm_tx_set_mute_mode(struct fmdev *, u8);
int fm_tx_set_stereo_mono(struct fmdev *, u16);
int fm_tx_set_rds_mode(struct fmdev *, u8);
int fm_tx_set_radio_text(struct fmdev *, u8 *, u8);
int fm_tx_set_af(struct fmdev *, u32);
int fm_tx_set_preemph_filter(struct fmdev *, u32);
int fm_tx_get_tune_cap_val(struct fmdev *);

#endif

