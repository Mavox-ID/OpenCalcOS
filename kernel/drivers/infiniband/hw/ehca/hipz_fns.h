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
#ifndef __HIPZ_FNS_H__
#define __HIPZ_FNS_H__

#include "ehca_classes.h"
#include "hipz_hw.h"

#include "hipz_fns_core.h"

#define hipz_galpa_store_eq(gal, offset, value) \
	hipz_galpa_store(gal, EQTEMM_OFFSET(offset), value)

#define hipz_galpa_load_eq(gal, offset) \
	hipz_galpa_load(gal, EQTEMM_OFFSET(offset))

#define hipz_galpa_store_qped(gal, offset, value) \
	hipz_galpa_store(gal, QPEDMM_OFFSET(offset), value)

#define hipz_galpa_load_qped(gal, offset) \
	hipz_galpa_load(gal, QPEDMM_OFFSET(offset))

#define hipz_galpa_store_mrmw(gal, offset, value) \
	hipz_galpa_store(gal, MRMWMM_OFFSET(offset), value)

#define hipz_galpa_load_mrmw(gal, offset) \
	hipz_galpa_load(gal, MRMWMM_OFFSET(offset))

#endif
