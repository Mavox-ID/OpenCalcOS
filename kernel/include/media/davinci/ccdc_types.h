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
#ifndef _CCDC_TYPES_H
#define _CCDC_TYPES_H
enum ccdc_pixfmt {
	CCDC_PIXFMT_RAW,
	CCDC_PIXFMT_YCBCR_16BIT,
	CCDC_PIXFMT_YCBCR_8BIT
};

enum ccdc_frmfmt {
	CCDC_FRMFMT_PROGRESSIVE,
	CCDC_FRMFMT_INTERLACED
};

/* PIXEL ORDER IN MEMORY from LSB to MSB */
/* only applicable for 8-bit input mode  */
enum ccdc_pixorder {
	CCDC_PIXORDER_YCBYCR,
	CCDC_PIXORDER_CBYCRY,
};

enum ccdc_buftype {
	CCDC_BUFTYPE_FLD_INTERLEAVED,
	CCDC_BUFTYPE_FLD_SEPARATED
};
#endif
