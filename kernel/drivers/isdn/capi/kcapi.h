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
#include <beep/spinlock.h>
#include <beep/list.h>
#include <beep/isdn/capilli.h>

#ifdef KCAPI_DEBUG
#define DBG(format, arg...) do {					\
		printk(KERN_DEBUG "%s: " format "\n" , __func__ , ## arg); \
	} while (0)
#else
#define DBG(format, arg...) /* */
#endif

enum {
	CAPI_CTR_DETACHED = 0,
	CAPI_CTR_DETECTED = 1,
	CAPI_CTR_LOADING  = 2,
	CAPI_CTR_RUNNING  = 3,
};

extern struct list_head capi_drivers;
extern struct mutex capi_drivers_lock;

extern struct capi_ctr *capi_controller[CAPI_MAXCONTR];
extern struct mutex capi_controller_lock;

extern struct capi20_appl *capi_applications[CAPI_MAXAPPL];

#ifdef CONFIG_PROC_FS

void kcapi_proc_init(void);
void kcapi_proc_exit(void);

#else

static inline void kcapi_proc_init(void) { };
static inline void kcapi_proc_exit(void) { };

#endif
