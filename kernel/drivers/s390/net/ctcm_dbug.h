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
#ifndef _CTCM_DBUG_H_
#define _CTCM_DBUG_H_

/*
 * Debug Facility stuff
 */

#include <asm/debug.h>

#ifdef DEBUG
 #define do_debug 1
#else
 #define do_debug 0
#endif
#ifdef DEBUGCCW
 #define do_debug_ccw 1
 #define DEBUGDATA 1
#else
 #define do_debug_ccw 0
#endif
#ifdef DEBUGDATA
 #define do_debug_data 1
#else
 #define do_debug_data 0
#endif

/* define dbf debug levels similar to kernel msg levels */
#define	CTC_DBF_ALWAYS	0	/* always print this 			*/
#define	CTC_DBF_EMERG	0	/* system is unusable			*/
#define	CTC_DBF_ALERT	1	/* action must be taken immediately	*/
#define	CTC_DBF_CRIT	2	/* critical conditions			*/
#define	CTC_DBF_ERROR	3	/* error conditions			*/
#define	CTC_DBF_WARN	4	/* warning conditions			*/
#define	CTC_DBF_NOTICE	5	/* normal but significant condition	*/
#define	CTC_DBF_INFO	5	/* informational			*/
#define	CTC_DBF_DEBUG	6	/* debug-level messages			*/

enum ctcm_dbf_names {
	CTCM_DBF_SETUP,
	CTCM_DBF_ERROR,
	CTCM_DBF_TRACE,
	CTCM_DBF_MPC_SETUP,
	CTCM_DBF_MPC_ERROR,
	CTCM_DBF_MPC_TRACE,
	CTCM_DBF_INFOS	/* must be last element */
};

struct ctcm_dbf_info {
	char name[DEBUG_MAX_NAME_LEN];
	int pages;
	int areas;
	int len;
	int level;
	debug_info_t *id;
};

extern struct ctcm_dbf_info ctcm_dbf[CTCM_DBF_INFOS];

int ctcm_register_dbf_views(void);
void ctcm_unregister_dbf_views(void);
void ctcm_dbf_longtext(enum ctcm_dbf_names dbf_nix, int level, char *text, ...);

static inline const char *strtail(const char *s, int n)
{
	int l = strlen(s);
	return (l > n) ? s + (l - n) : s;
}

#define CTCM_FUNTAIL strtail((char *)__func__, 16)

#define CTCM_DBF_TEXT(name, level, text) \
	do { \
		debug_text_event(ctcm_dbf[CTCM_DBF_##name].id, level, text); \
	} while (0)

#define CTCM_DBF_HEX(name, level, addr, len) \
	do { \
		debug_event(ctcm_dbf[CTCM_DBF_##name].id, \
					level, (void *)(addr), len); \
	} while (0)

#define CTCM_DBF_TEXT_(name, level, text...) \
	ctcm_dbf_longtext(CTCM_DBF_##name, level, text)

/*
 * cat : one of {setup, mpc_setup, trace, mpc_trace, error, mpc_error}.
 * dev : netdevice with valid name field.
 * text: any text string.
 */
#define CTCM_DBF_DEV_NAME(cat, dev, text) \
	do { \
		CTCM_DBF_TEXT_(cat, CTC_DBF_INFO, "%s(%s) :- %s", \
			CTCM_FUNTAIL, dev->name, text); \
	} while (0)

#define MPC_DBF_DEV_NAME(cat, dev, text) \
	do { \
		CTCM_DBF_TEXT_(MPC_##cat, CTC_DBF_INFO, "%s(%s) := %s", \
			CTCM_FUNTAIL, dev->name, text); \
	} while (0)

#define CTCMY_DBF_DEV_NAME(cat, dev, text) \
	do { \
		if (IS_MPCDEV(dev)) \
			MPC_DBF_DEV_NAME(cat, dev, text); \
		else \
			CTCM_DBF_DEV_NAME(cat, dev, text); \
	} while (0)

/*
 * cat : one of {setup, mpc_setup, trace, mpc_trace, error, mpc_error}.
 * dev : netdevice.
 * text: any text string.
 */
#define CTCM_DBF_DEV(cat, dev, text) \
	do { \
		CTCM_DBF_TEXT_(cat, CTC_DBF_INFO, "%s(%p) :-: %s", \
			CTCM_FUNTAIL, dev, text); \
	} while (0)

#define MPC_DBF_DEV(cat, dev, text) \
	do { \
		CTCM_DBF_TEXT_(MPC_##cat, CTC_DBF_INFO, "%s(%p) :=: %s", \
			CTCM_FUNTAIL, dev, text); \
	} while (0)

#define CTCMY_DBF_DEV(cat, dev, text) \
	do { \
		if (IS_MPCDEV(dev)) \
			MPC_DBF_DEV(cat, dev, text); \
		else \
			CTCM_DBF_DEV(cat, dev, text); \
	} while (0)

#endif
