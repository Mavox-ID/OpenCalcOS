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
#ifndef __DIR_DOT_H__
#define __DIR_DOT_H__

int dlm_dir_nodeid(struct dlm_rsb *rsb);
int dlm_hash2nodeid(struct dlm_ls *ls, uint32_t hash);
void dlm_recover_dir_nodeid(struct dlm_ls *ls);
int dlm_recover_directory(struct dlm_ls *ls);
void dlm_copy_master_names(struct dlm_ls *ls, char *inbuf, int inlen,
	char *outbuf, int outlen, int nodeid);

#endif				/* __DIR_DOT_H__ */

