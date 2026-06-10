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
#ifndef _XS_WIRE_H
#define _XS_WIRE_H

enum xsd_sockmsg_type
{
    XS_DEBUG,
    XS_DIRECTORY,
    XS_READ,
    XS_GET_PERMS,
    XS_WATCH,
    XS_UNWATCH,
    XS_TRANSACTION_START,
    XS_TRANSACTION_END,
    XS_INTRODUCE,
    XS_RELEASE,
    XS_GET_DOMAIN_PATH,
    XS_WRITE,
    XS_MKDIR,
    XS_RM,
    XS_SET_PERMS,
    XS_WATCH_EVENT,
    XS_ERROR,
    XS_IS_DOMAIN_INTRODUCED,
    XS_RESUME,
    XS_SET_TARGET,
    XS_RESTRICT,
    XS_RESET_WATCHES,
};

#define XS_WRITE_NONE "NONE"
#define XS_WRITE_CREATE "CREATE"
#define XS_WRITE_CREATE_EXCL "CREATE|EXCL"

/* We hand errors as strings, for portability. */
struct xsd_errors
{
    int errnum;
    const char *errstring;
};
#define XSD_ERROR(x) { x, #x }
static struct xsd_errors xsd_errors[] __attribute__((unused)) = {
    XSD_ERROR(EINVAL),
    XSD_ERROR(EACCES),
    XSD_ERROR(EEXIST),
    XSD_ERROR(EISDIR),
    XSD_ERROR(ENOENT),
    XSD_ERROR(ENOMEM),
    XSD_ERROR(ENOSPC),
    XSD_ERROR(EIO),
    XSD_ERROR(ENOTEMPTY),
    XSD_ERROR(ENOSYS),
    XSD_ERROR(EROFS),
    XSD_ERROR(EBUSY),
    XSD_ERROR(EAGAIN),
    XSD_ERROR(EISCONN)
};

struct xsd_sockmsg
{
    uint32_t type;  /* XS_??? */
    uint32_t req_id;/* Request identifier, echoed in daemon's response.  */
    uint32_t tx_id; /* Transaction id (0 if not related to a transaction). */
    uint32_t len;   /* Length of data following this. */

    /* Generally followed by nul-terminated string(s). */
};

enum xs_watch_type
{
    XS_WATCH_PATH = 0,
    XS_WATCH_TOKEN
};

/* Inter-domain shared memory communications. */
#define XENSTORE_RING_SIZE 1024
typedef uint32_t XENSTORE_RING_IDX;
#define MASK_XENSTORE_IDX(idx) ((idx) & (XENSTORE_RING_SIZE-1))
struct xenstore_domain_interface {
    char req[XENSTORE_RING_SIZE]; /* Requests to xenstore daemon. */
    char rsp[XENSTORE_RING_SIZE]; /* Replies and async watch events. */
    XENSTORE_RING_IDX req_cons, req_prod;
    XENSTORE_RING_IDX rsp_cons, rsp_prod;
};

/* Violating this is very bad.  See docs/misc/xenstore.txt. */
#define XENSTORE_PAYLOAD_MAX 4096

#endif /* _XS_WIRE_H */
