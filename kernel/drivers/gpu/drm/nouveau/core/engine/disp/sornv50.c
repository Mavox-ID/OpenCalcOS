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
#include <core/os.h>
#include <core/class.h>

#include <subdev/bios.h>
#include <subdev/bios/dcb.h>
#include <subdev/timer.h>

#include "nv50.h"

int
nv50_sor_power(struct nv50_disp_priv *priv, int or, u32 data)
{
	const u32 stat = data & NV50_DISP_SOR_PWR_STATE;
	const u32 soff = (or * 0x800);
	nv_wait(priv, 0x61c004 + soff, 0x80000000, 0x00000000);
	nv_mask(priv, 0x61c004 + soff, 0x80000001, 0x80000000 | stat);
	nv_wait(priv, 0x61c004 + soff, 0x80000000, 0x00000000);
	nv_wait(priv, 0x61c030 + soff, 0x10000000, 0x00000000);
	return 0;
}

int
nv50_sor_mthd(struct nouveau_object *object, u32 mthd, void *args, u32 size)
{
	struct nv50_disp_priv *priv = (void *)object->engine;
	struct nouveau_bios *bios = nouveau_bios(priv);
	const u16 type = (mthd & NV50_DISP_SOR_MTHD_TYPE) >> 12;
	const u8  head = (mthd & NV50_DISP_SOR_MTHD_HEAD) >> 3;
	const u8  link = (mthd & NV50_DISP_SOR_MTHD_LINK) >> 2;
	const u8    or = (mthd & NV50_DISP_SOR_MTHD_OR);
	const u16 mask = (0x0100 << head) | (0x0040 << link) | (0x0001 << or);
	struct dcb_output outp;
	u8  ver, hdr;
	u32 data;
	int ret = -EINVAL;

	if (size < sizeof(u32))
		return -EINVAL;
	data = *(u32 *)args;

	if (type && !dcb_outp_match(bios, type, mask, &ver, &hdr, &outp))
		return -ENODEV;

	switch (mthd & ~0x3f) {
	case NV50_DISP_SOR_PWR:
		ret = priv->sor.power(priv, or, data);
		break;
	case NVA3_DISP_SOR_HDA_ELD:
		ret = priv->sor.hda_eld(priv, or, args, size);
		break;
	case NV84_DISP_SOR_HDMI_PWR:
		ret = priv->sor.hdmi(priv, head, or, data);
		break;
	case NV50_DISP_SOR_LVDS_SCRIPT:
		priv->sor.lvdsconf = data & NV50_DISP_SOR_LVDS_SCRIPT_ID;
		ret = 0;
		break;
	case NV94_DISP_SOR_DP_TRAIN:
		switch (data & NV94_DISP_SOR_DP_TRAIN_OP) {
		case NV94_DISP_SOR_DP_TRAIN_OP_PATTERN:
			ret = priv->sor.dp_train(priv, or, link, type, mask, data, &outp);
			break;
		case NV94_DISP_SOR_DP_TRAIN_OP_INIT:
			ret = priv->sor.dp_train_init(priv, or, link, head, type, mask, data, &outp);
			break;
		case NV94_DISP_SOR_DP_TRAIN_OP_FINI:
			ret = priv->sor.dp_train_fini(priv, or, link, head, type, mask, data, &outp);
			break;
		default:
			break;
		}
		break;
	case NV94_DISP_SOR_DP_LNKCTL:
		ret = priv->sor.dp_lnkctl(priv, or, link, head, type, mask, data, &outp);
		break;
	case NV94_DISP_SOR_DP_DRVCTL(0):
	case NV94_DISP_SOR_DP_DRVCTL(1):
	case NV94_DISP_SOR_DP_DRVCTL(2):
	case NV94_DISP_SOR_DP_DRVCTL(3):
		ret = priv->sor.dp_drvctl(priv, or, link, (mthd & 0xc0) >> 6,
				          type, mask, data, &outp);
		break;
	default:
		BUG_ON(1);
	}

	return ret;
}
