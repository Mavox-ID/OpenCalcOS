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
#ifndef DLMDOMAIN_H
#define DLMDOMAIN_H

extern spinlock_t dlm_domain_lock;
extern struct list_head dlm_domains;

int dlm_joined(struct dlm_ctxt *dlm);
int dlm_shutting_down(struct dlm_ctxt *dlm);
void dlm_fire_domain_eviction_callbacks(struct dlm_ctxt *dlm,
					int node_num);

#endif
