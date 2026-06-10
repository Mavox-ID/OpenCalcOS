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
#ifndef __UTIL_DOT_H__
#define __UTIL_DOT_H__

void dlm_message_out(struct dlm_message *ms);
void dlm_message_in(struct dlm_message *ms);
void dlm_rcom_out(struct dlm_rcom *rc);
void dlm_rcom_in(struct dlm_rcom *rc);

#endif

