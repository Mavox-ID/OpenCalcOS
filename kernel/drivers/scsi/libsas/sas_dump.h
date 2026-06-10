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
#include "sas_internal.h"

void sas_dprint_porte(int phyid, enum port_event pe);
void sas_dprint_phye(int phyid, enum phy_event pe);
void sas_dprint_hae(struct sas_ha_struct *sas_ha, enum ha_event he);
void sas_dump_port(struct asd_sas_port *port);
