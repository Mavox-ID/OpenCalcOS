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
#ifndef __OSD_SEC_H__
#define __OSD_SEC_H__

#include <scsi/osd_protocol.h>
#include <scsi/osd_types.h>

/*
 * Contains types and constants of osd capabilities and security
 * encoding/decoding.
 * API is trying to keep security abstract so initiator of an object
 * based pNFS client knows as little as possible about security and
 * capabilities. It is the Server's osd-initiator place to know more.
 * Also can be used by osd-target.
 */
void osd_sec_encode_caps(void *caps, ...);/* NI */
void osd_sec_init_nosec_doall_caps(void *caps,
	const struct osd_obj_id *obj, bool is_collection, const bool is_v1);

bool osd_is_sec_alldata(struct osd_security_parameters *sec_params);

/* Conditionally sign the CDB according to security setting in ocdb
 * with cap_key */
void osd_sec_sign_cdb(struct osd_cdb *ocdb, const u8 *cap_key);

/* Unconditionally sign the BIO data with cap_key.
 * Check for osd_is_sec_alldata() was done prior to calling this. */
void osd_sec_sign_data(void *data_integ, struct bio *bio, const u8 *cap_key);

/* Version independent copy of caps into the cdb */
void osd_set_caps(struct osd_cdb *cdb, const void *caps);

#endif /* ndef __OSD_SEC_H__ */
