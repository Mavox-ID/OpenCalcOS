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
#include <defs.h>
#include "types.h"
#include <ucode_loader.h>

enum {
	D11UCODE_NAMETAG_START = 0,
	D11LCN0BSINITVALS24,
	D11LCN0INITVALS24,
	D11LCN1BSINITVALS24,
	D11LCN1INITVALS24,
	D11LCN2BSINITVALS24,
	D11LCN2INITVALS24,
	D11N0ABSINITVALS16,
	D11N0BSINITVALS16,
	D11N0INITVALS16,
	D11UCODE_OVERSIGHT16_MIMO,
	D11UCODE_OVERSIGHT16_MIMOSZ,
	D11UCODE_OVERSIGHT24_LCN,
	D11UCODE_OVERSIGHT24_LCNSZ,
	D11UCODE_OVERSIGHT_BOMMAJOR,
	D11UCODE_OVERSIGHT_BOMMINOR
};

int brcms_ucode_data_init(struct brcms_info *wl, struct brcms_ucode *ucode)
{
	int rc;

	rc = brcms_check_firmwares(wl);

	rc = rc < 0 ? rc :
		brcms_ucode_init_buf(wl, (void **)&ucode->d11lcn0bsinitvals24,
				     D11LCN0BSINITVALS24);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->d11lcn0initvals24,
				       D11LCN0INITVALS24);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->d11lcn1bsinitvals24,
				       D11LCN1BSINITVALS24);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->d11lcn1initvals24,
				       D11LCN1INITVALS24);
	rc = rc < 0 ? rc :
		brcms_ucode_init_buf(wl, (void **)&ucode->d11lcn2bsinitvals24,
				     D11LCN2BSINITVALS24);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->d11lcn2initvals24,
				       D11LCN2INITVALS24);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->d11n0absinitvals16,
				       D11N0ABSINITVALS16);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->d11n0bsinitvals16,
				       D11N0BSINITVALS16);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->d11n0initvals16,
				       D11N0INITVALS16);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->bcm43xx_16_mimo,
				       D11UCODE_OVERSIGHT16_MIMO);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_uint(wl, &ucode->bcm43xx_16_mimosz,
					D11UCODE_OVERSIGHT16_MIMOSZ);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->bcm43xx_24_lcn,
				       D11UCODE_OVERSIGHT24_LCN);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_uint(wl, &ucode->bcm43xx_24_lcnsz,
					D11UCODE_OVERSIGHT24_LCNSZ);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->bcm43xx_bommajor,
				       D11UCODE_OVERSIGHT_BOMMAJOR);
	rc = rc < 0 ?
	     rc : brcms_ucode_init_buf(wl, (void **)&ucode->bcm43xx_bomminor,
				       D11UCODE_OVERSIGHT_BOMMINOR);
	return rc;
}

void brcms_ucode_data_free(struct brcms_ucode *ucode)
{
	brcms_ucode_free_buf((void *)ucode->d11lcn0bsinitvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn0initvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn1bsinitvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn1initvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn2bsinitvals24);
	brcms_ucode_free_buf((void *)ucode->d11lcn2initvals24);
	brcms_ucode_free_buf((void *)ucode->d11n0absinitvals16);
	brcms_ucode_free_buf((void *)ucode->d11n0bsinitvals16);
	brcms_ucode_free_buf((void *)ucode->d11n0initvals16);
	brcms_ucode_free_buf((void *)ucode->bcm43xx_16_mimo);
	brcms_ucode_free_buf((void *)ucode->bcm43xx_24_lcn);
	brcms_ucode_free_buf((void *)ucode->bcm43xx_bommajor);
	brcms_ucode_free_buf((void *)ucode->bcm43xx_bomminor);
}
