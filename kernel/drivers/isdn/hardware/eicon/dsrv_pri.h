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
#ifndef __DIVA_XDI_DSRV_PRI_INC__
#define __DIVA_XDI_DSRV_PRI_INC__
/*
  Functions exported from os dependent part of
  PRI card configuration and used in
  OS independed part
*/
/*
  Prepare OS dependent part of PRI/PRI Rev.2 functions
*/
void diva_os_prepare_pri_functions(PISDN_ADAPTER IoAdapter);
void diva_os_prepare_pri2_functions(PISDN_ADAPTER IoAdapter);
#endif
