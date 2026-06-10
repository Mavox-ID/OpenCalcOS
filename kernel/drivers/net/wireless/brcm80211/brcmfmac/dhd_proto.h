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
#ifndef _BRCMF_PROTO_H_
#define _BRCMF_PROTO_H_

/*
 * Exported from the brcmf protocol module (brcmf_cdc)
 */

/* Linkage, sets prot link and updates hdrlen in pub */
extern int brcmf_proto_attach(struct brcmf_pub *drvr);

/* Unlink, frees allocated protocol memory (including brcmf_proto) */
extern void brcmf_proto_detach(struct brcmf_pub *drvr);

/* Stop protocol: sync w/dongle state. */
extern void brcmf_proto_stop(struct brcmf_pub *drvr);

/* Add any protocol-specific data header.
 * Caller must reserve prot_hdrlen prepend space.
 */
extern void brcmf_proto_hdrpush(struct brcmf_pub *, int ifidx,
				struct sk_buff *txp);

/* Sets dongle media info (drv_version, mac address). */
extern int brcmf_c_preinit_dcmds(struct brcmf_if *ifp);

#endif				/* _BRCMF_PROTO_H_ */
