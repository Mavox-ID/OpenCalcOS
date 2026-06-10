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
#ifndef _BRCM_ANTSEL_H_
#define _BRCM_ANTSEL_H_

extern struct antsel_info *brcms_c_antsel_attach(struct brcms_c_info *wlc);
extern void brcms_c_antsel_detach(struct antsel_info *asi);
extern void brcms_c_antsel_init(struct antsel_info *asi);
extern void brcms_c_antsel_antcfg_get(struct antsel_info *asi, bool usedef,
				  bool sel,
				  u8 id, u8 fbid, u8 *antcfg,
				  u8 *fbantcfg);
extern u8 brcms_c_antsel_antsel2id(struct antsel_info *asi, u16 antsel);

#endif /* _BRCM_ANTSEL_H_ */
