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
#ifndef ZCRYPT_DEBUG_H
#define ZCRYPT_DEBUG_H

#include <asm/debug.h>
#include "zcrypt_api.h"

/* that gives us 15 characters in the text event views */
#define ZCRYPT_DBF_LEN	16

/* sort out low debug levels early to avoid wasted sprints */
static inline int zcrypt_dbf_passes(debug_info_t *dbf_grp, int level)
{
	return (level <= dbf_grp->level);
}

#define DBF_ERR		3	/* error conditions	*/
#define DBF_WARN	4	/* warning conditions	*/
#define DBF_INFO	6	/* informational	*/

#define RC2WARN(rc) ((rc) ? DBF_WARN : DBF_INFO)

#define ZCRYPT_DBF_COMMON(level, text...) \
	do { \
		if (zcrypt_dbf_passes(zcrypt_dbf_common, level)) { \
			char debug_buffer[ZCRYPT_DBF_LEN]; \
			snprintf(debug_buffer, ZCRYPT_DBF_LEN, text); \
			debug_text_event(zcrypt_dbf_common, level, \
					 debug_buffer); \
		} \
	} while (0)

#define ZCRYPT_DBF_DEVICES(level, text...) \
	do { \
		if (zcrypt_dbf_passes(zcrypt_dbf_devices, level)) { \
			char debug_buffer[ZCRYPT_DBF_LEN]; \
			snprintf(debug_buffer, ZCRYPT_DBF_LEN, text); \
			debug_text_event(zcrypt_dbf_devices, level, \
					 debug_buffer); \
		} \
	} while (0)

#define ZCRYPT_DBF_DEV(level, device, text...) \
	do { \
		if (zcrypt_dbf_passes(device->dbf_area, level)) { \
			char debug_buffer[ZCRYPT_DBF_LEN]; \
			snprintf(debug_buffer, ZCRYPT_DBF_LEN, text); \
			debug_text_event(device->dbf_area, level, \
					 debug_buffer); \
		} \
	} while (0)

int zcrypt_debug_init(void);
void zcrypt_debug_exit(void);

#endif /* ZCRYPT_DEBUG_H */
