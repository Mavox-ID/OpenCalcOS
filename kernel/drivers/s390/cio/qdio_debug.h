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
#ifndef QDIO_DEBUG_H
#define QDIO_DEBUG_H

#include <asm/debug.h>
#include <asm/qdio.h>
#include "qdio.h"

/* that gives us 15 characters in the text event views */
#define QDIO_DBF_LEN	16

extern debug_info_t *qdio_dbf_setup;
extern debug_info_t *qdio_dbf_error;

/* sort out low debug levels early to avoid wasted sprints */
static inline int qdio_dbf_passes(debug_info_t *dbf_grp, int level)
{
	return (level <= dbf_grp->level);
}

#define DBF_ERR		3	/* error conditions	*/
#define DBF_WARN	4	/* warning conditions	*/
#define DBF_INFO	6	/* informational	*/

#undef DBF_EVENT
#undef DBF_ERROR
#undef DBF_DEV_EVENT

#define DBF_EVENT(text...) \
	do { \
		char debug_buffer[QDIO_DBF_LEN]; \
		snprintf(debug_buffer, QDIO_DBF_LEN, text); \
		debug_text_event(qdio_dbf_setup, DBF_ERR, debug_buffer); \
	} while (0)

static inline void DBF_HEX(void *addr, int len)
{
	while (len > 0) {
		debug_event(qdio_dbf_setup, DBF_ERR, addr, len);
		len -= qdio_dbf_setup->buf_size;
		addr += qdio_dbf_setup->buf_size;
	}
}

#define DBF_ERROR(text...) \
	do { \
		char debug_buffer[QDIO_DBF_LEN]; \
		snprintf(debug_buffer, QDIO_DBF_LEN, text); \
		debug_text_event(qdio_dbf_error, DBF_ERR, debug_buffer); \
	} while (0)

static inline void DBF_ERROR_HEX(void *addr, int len)
{
	while (len > 0) {
		debug_event(qdio_dbf_error, DBF_ERR, addr, len);
		len -= qdio_dbf_error->buf_size;
		addr += qdio_dbf_error->buf_size;
	}
}

#define DBF_DEV_EVENT(level, device, text...) \
	do { \
		char debug_buffer[QDIO_DBF_LEN]; \
		if (qdio_dbf_passes(device->debug_area, level)) { \
			snprintf(debug_buffer, QDIO_DBF_LEN, text); \
			debug_text_event(device->debug_area, level, debug_buffer); \
		} \
	} while (0)

static inline void DBF_DEV_HEX(struct qdio_irq *dev, void *addr,
			       int len, int level)
{
	while (len > 0) {
		debug_event(dev->debug_area, level, addr, len);
		len -= dev->debug_area->buf_size;
		addr += dev->debug_area->buf_size;
	}
}

void qdio_allocate_dbf(struct qdio_initialize *init_data,
		       struct qdio_irq *irq_ptr);
void qdio_setup_debug_entries(struct qdio_irq *irq_ptr,
			      struct ccw_device *cdev);
void qdio_shutdown_debug_entries(struct qdio_irq *irq_ptr,
				 struct ccw_device *cdev);
int qdio_debug_init(void);
void qdio_debug_exit(void);

#endif
