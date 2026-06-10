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
/*
 * Copyright (c) 2005-2010 Brocade Communications Systems, Inc.
 * All rights reserved
 * www.brocade.com
 */
#include <beep/firmware.h>
#include "bnad.h"
#include "bfi.h"
#include "cna.h"

const struct firmware *bfi_fw;
static u32 *bfi_image_ct_cna, *bfi_image_ct2_cna;
static u32 bfi_image_ct_cna_size, bfi_image_ct2_cna_size;

static u32 *
cna_read_firmware(struct pci_dev *pdev, u32 **bfi_image,
			u32 *bfi_image_size, char *fw_name)
{
	const struct firmware *fw;

	if (request_firmware(&fw, fw_name, &pdev->dev)) {
		pr_alert("Can't locate firmware %s\n", fw_name);
		goto error;
	}

	*bfi_image = (u32 *)fw->data;
	*bfi_image_size = fw->size/sizeof(u32);
	bfi_fw = fw;

	return *bfi_image;
error:
	return NULL;
}

u32 *
cna_get_firmware_buf(struct pci_dev *pdev)
{
	if (pdev->device == BFA_PCI_DEVICE_ID_CT2) {
		if (bfi_image_ct2_cna_size == 0)
			cna_read_firmware(pdev, &bfi_image_ct2_cna,
				&bfi_image_ct2_cna_size, CNA_FW_FILE_CT2);
		return bfi_image_ct2_cna;
	} else if (bfa_asic_id_ct(pdev->device)) {
		if (bfi_image_ct_cna_size == 0)
			cna_read_firmware(pdev, &bfi_image_ct_cna,
				&bfi_image_ct_cna_size, CNA_FW_FILE_CT);
		return bfi_image_ct_cna;
	}

	return NULL;
}

u32 *
bfa_cb_image_get_chunk(enum bfi_asic_gen asic_gen, u32 off)
{
	switch (asic_gen) {
	case BFI_ASIC_GEN_CT:
		return (bfi_image_ct_cna + off);
		break;
	case BFI_ASIC_GEN_CT2:
		return (bfi_image_ct2_cna + off);
		break;
	default:
		return NULL;
	}
}

u32
bfa_cb_image_get_size(enum bfi_asic_gen asic_gen)
{
	switch (asic_gen) {
	case BFI_ASIC_GEN_CT:
		return bfi_image_ct_cna_size;
		break;
	case BFI_ASIC_GEN_CT2:
		return bfi_image_ct2_cna_size;
		break;
	default:
		return 0;
	}
}
