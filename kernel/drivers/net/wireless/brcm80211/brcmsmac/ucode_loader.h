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
#ifndef	_BRCM_UCODE_H_
#define	_BRCM_UCODE_H_

#include "types.h"		/* forward structure declarations */

#define MIN_FW_SIZE 40000	/* minimum firmware file size in bytes */
#define MAX_FW_SIZE 150000

#define UCODE_LOADER_API_VER 0

struct d11init;

struct brcms_ucode {
	struct d11init *d11lcn0bsinitvals24;
	struct d11init *d11lcn0initvals24;
	struct d11init *d11lcn1bsinitvals24;
	struct d11init *d11lcn1initvals24;
	struct d11init *d11lcn2bsinitvals24;
	struct d11init *d11lcn2initvals24;
	struct d11init *d11n0absinitvals16;
	struct d11init *d11n0bsinitvals16;
	struct d11init *d11n0initvals16;
	__le32 *bcm43xx_16_mimo;
	size_t bcm43xx_16_mimosz;
	__le32 *bcm43xx_24_lcn;
	size_t bcm43xx_24_lcnsz;
	u32 *bcm43xx_bommajor;
	u32 *bcm43xx_bomminor;
};

extern int
brcms_ucode_data_init(struct brcms_info *wl, struct brcms_ucode *ucode);

extern void brcms_ucode_data_free(struct brcms_ucode *ucode);

extern int brcms_ucode_init_buf(struct brcms_info *wl, void **pbuf,
				unsigned int idx);
extern int brcms_ucode_init_uint(struct brcms_info *wl, size_t *n_bytes,
				 unsigned int idx);
extern void brcms_ucode_free_buf(void *);
extern int  brcms_check_firmwares(struct brcms_info *wl);

#endif	/* _BRCM_UCODE_H_ */
