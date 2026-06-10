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
#ifndef _fwil_h_
#define _fwil_h_

s32 brcmf_fil_cmd_data_set(struct brcmf_if *ifp, u32 cmd, void *data, u32 len);
s32 brcmf_fil_cmd_data_get(struct brcmf_if *ifp, u32 cmd, void *data, u32 len);
s32 brcmf_fil_cmd_int_set(struct brcmf_if *ifp, u32 cmd, u32 data);
s32 brcmf_fil_cmd_int_get(struct brcmf_if *ifp, u32 cmd, u32 *data);

s32 brcmf_fil_iovar_data_set(struct brcmf_if *ifp, char *name, void *data,
			     u32 len);
s32 brcmf_fil_iovar_data_get(struct brcmf_if *ifp, char *name, void *data,
			     u32 len);
s32 brcmf_fil_iovar_int_set(struct brcmf_if *ifp, char *name, u32 data);
s32 brcmf_fil_iovar_int_get(struct brcmf_if *ifp, char *name, u32 *data);

s32 brcmf_fil_bsscfg_data_set(struct brcmf_if *ifp, char *name, void *data,
			      u32 len);
s32 brcmf_fil_bsscfg_data_get(struct brcmf_if *ifp, char *name, void *data,
			      u32 len);
s32 brcmf_fil_bsscfg_int_set(struct brcmf_if *ifp, char *name, u32 data);
s32 brcmf_fil_bsscfg_int_get(struct brcmf_if *ifp, char *name, u32 *data);

#endif /* _fwil_h_ */
