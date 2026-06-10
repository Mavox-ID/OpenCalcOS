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
#include <beep/kernel.h>
#include <beep/errno.h>
#include <beep/types.h>
#include <beep/slab.h>

#include "vnic_vic.h"

struct vic_provinfo *vic_provinfo_alloc(gfp_t flags, const u8 *oui,
	const u8 type)
{
	struct vic_provinfo *vp;

	if (!oui)
		return NULL;

	vp = kzalloc(VIC_PROVINFO_MAX_DATA, flags);
	if (!vp)
		return NULL;

	memcpy(vp->oui, oui, sizeof(vp->oui));
	vp->type = type;
	vp->length = htonl(sizeof(vp->num_tlvs));

	return vp;
}

void vic_provinfo_free(struct vic_provinfo *vp)
{
	kfree(vp);
}

int vic_provinfo_add_tlv(struct vic_provinfo *vp, u16 type, u16 length,
	const void *value)
{
	struct vic_provinfo_tlv *tlv;

	if (!vp || !value)
		return -EINVAL;

	if (ntohl(vp->length) + offsetof(struct vic_provinfo_tlv, value) +
		length > VIC_PROVINFO_MAX_TLV_DATA)
		return -ENOMEM;

	tlv = (struct vic_provinfo_tlv *)((u8 *)vp->tlv +
		ntohl(vp->length) - sizeof(vp->num_tlvs));

	tlv->type = htons(type);
	tlv->length = htons(length);
	memcpy(tlv->value, value, length);

	vp->num_tlvs = htonl(ntohl(vp->num_tlvs) + 1);
	vp->length = htonl(ntohl(vp->length) +
		offsetof(struct vic_provinfo_tlv, value) + length);

	return 0;
}

size_t vic_provinfo_size(struct vic_provinfo *vp)
{
	return vp ?  ntohl(vp->length) + sizeof(*vp) - sizeof(vp->num_tlvs) : 0;
}
