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
#ifndef _FMDRV_RX_H
#define _FMDRV_RX_H

int fm_rx_set_freq(struct fmdev *, u32);
int fm_rx_set_mute_mode(struct fmdev *, u8);
int fm_rx_set_stereo_mono(struct fmdev *, u16);
int fm_rx_set_rds_mode(struct fmdev *, u8);
int fm_rx_set_rds_system(struct fmdev *, u8);
int fm_rx_set_volume(struct fmdev *, u16);
int fm_rx_set_rssi_threshold(struct fmdev *, short);
int fm_rx_set_region(struct fmdev *, u8);
int fm_rx_set_rfdepend_softmute(struct fmdev *, u8);
int fm_rx_set_deemphasis_mode(struct fmdev *, u16);
int fm_rx_set_af_switch(struct fmdev *, u8);

void fm_rx_reset_rds_cache(struct fmdev *);
void fm_rx_reset_station_info(struct fmdev *);

int fm_rx_seek(struct fmdev *, u32, u32, u32);

int fm_rx_get_rds_mode(struct fmdev *, u8 *);
int fm_rx_get_rds_system(struct fmdev *, u8 *);
int fm_rx_get_mute_mode(struct fmdev *, u8 *);
int fm_rx_get_volume(struct fmdev *, u16 *);
int fm_rx_get_band_freq_range(struct fmdev *,
					u32 *, u32 *);
int fm_rx_get_stereo_mono(struct fmdev *, u16 *);
int fm_rx_get_rssi_level(struct fmdev *, u16 *);
int fm_rx_get_rssi_threshold(struct fmdev *, short *);
int fm_rx_get_rfdepend_softmute(struct fmdev *, u8 *);
int fm_rx_get_deemph_mode(struct fmdev *, u16 *);
int fm_rx_get_af_switch(struct fmdev *, u8 *);
void fm_rx_get_region(struct fmdev *, u8 *);

int fm_rx_set_chanl_spacing(struct fmdev *, u8);
int fm_rx_get_chanl_spacing(struct fmdev *, u8 *);
#endif

