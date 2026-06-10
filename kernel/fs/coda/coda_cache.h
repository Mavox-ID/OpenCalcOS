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
#ifndef _CFSNC_HEADER_
#define _CFSNC_HEADER_

/* credential cache */
void coda_cache_enter(struct inode *inode, int mask);
void coda_cache_clear_inode(struct inode *);
void coda_cache_clear_all(struct super_block *sb);
int coda_cache_check(struct inode *inode, int mask);

/* for downcalls and attributes and lookups */
void coda_flag_inode_children(struct inode *inode, int flag);

#endif /* _CFSNC_HEADER_ */
