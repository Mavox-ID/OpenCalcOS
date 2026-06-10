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
#ifndef __SOUND_PCXHR_HWDEP_H
#define __SOUND_PCXHR_HWDEP_H


/* firmware status codes  */
#define PCXHR_FIRMWARE_XLX_INT_INDEX   0
#define PCXHR_FIRMWARE_XLX_COM_INDEX   1
#define PCXHR_FIRMWARE_DSP_EPRM_INDEX  2
#define PCXHR_FIRMWARE_DSP_BOOT_INDEX  3
#define PCXHR_FIRMWARE_DSP_MAIN_INDEX  4
#define PCXHR_FIRMWARE_FILES_MAX_INDEX 5


/* exported */
int  pcxhr_setup_firmware(struct pcxhr_mgr *mgr);
void pcxhr_reset_board(struct pcxhr_mgr *mgr);

#endif /* __SOUND_PCXHR_HWDEP_H */
