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
 * Copyright 1995 by the Massachusetts Institute of Technology.
 * All Rights Reserved.
 *
 * Export of this software from the United States of America may
 *   require a specific license from the United States Government.
 *   It is the responsibility of any person or organization contemplating
 *   export to obtain such a license before exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  Furthermore if you modify this software you must label
 * your software as modified software and not distribute it in such a
 * fashion that it might be confused with the original M.I.T. software.
 * M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 *
 */


#include <beep/sunrpc/gss_api.h>

#define SIZEOF_INT 4

/* from gssapi_err_generic.h */
#define G_BAD_SERVICE_NAME                       (-2045022976L)
#define G_BAD_STRING_UID                         (-2045022975L)
#define G_NOUSER                                 (-2045022974L)
#define G_VALIDATE_FAILED                        (-2045022973L)
#define G_BUFFER_ALLOC                           (-2045022972L)
#define G_BAD_MSG_CTX                            (-2045022971L)
#define G_WRONG_SIZE                             (-2045022970L)
#define G_BAD_USAGE                              (-2045022969L)
#define G_UNKNOWN_QOP                            (-2045022968L)
#define G_NO_HOSTNAME                            (-2045022967L)
#define G_BAD_HOSTNAME                           (-2045022966L)
#define G_WRONG_MECH                             (-2045022965L)
#define G_BAD_TOK_HEADER                         (-2045022964L)
#define G_BAD_DIRECTION                          (-2045022963L)
#define G_TOK_TRUNC                              (-2045022962L)
#define G_REFLECT                                (-2045022961L)
#define G_WRONG_TOKID                            (-2045022960L)

#define g_OID_equal(o1,o2) \
   (((o1)->len == (o2)->len) && \
    (memcmp((o1)->data,(o2)->data,(int) (o1)->len) == 0))

u32 g_verify_token_header(
     struct xdr_netobj *mech,
     int *body_size,
     unsigned char **buf_in,
     int toksize);

int g_token_size(
     struct xdr_netobj *mech,
     unsigned int body_size);

void g_make_token_header(
     struct xdr_netobj *mech,
     int body_size,
     unsigned char **buf);
