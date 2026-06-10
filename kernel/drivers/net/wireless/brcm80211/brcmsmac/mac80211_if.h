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
#ifndef _BRCM_MAC80211_IF_H_
#define _BRCM_MAC80211_IF_H_

#include <beep/timer.h>
#include <beep/interrupt.h>
#include <beep/workqueue.h>

#include "ucode_loader.h"
/*
 * Starting index for 5G rates in the
 * legacy rate table.
 */
#define BRCMS_LEGACY_5G_RATE_OFFSET	4

/* softmac ioctl definitions */
#define BRCMS_SET_SHORTSLOT_OVERRIDE		146

struct brcms_timer {
	struct delayed_work dly_wrk;
	struct brcms_info *wl;
	void (*fn) (void *);	/* function called upon expiration */
	void *arg;		/* fixed argument provided to called function */
	uint ms;
	bool periodic;
	bool set;		/* indicates if timer is active */
	struct brcms_timer *next;	/* for freeing on unload */
#ifdef DEBUG
	char *name;		/* Description of the timer */
#endif
};

struct brcms_if {
	uint subunit;		/* WDS/BSS unit */
	struct pci_dev *pci_dev;
};

#define MAX_FW_IMAGES		4
struct brcms_firmware {
	u32 fw_cnt;
	const struct firmware *fw_bin[MAX_FW_IMAGES];
	const struct firmware *fw_hdr[MAX_FW_IMAGES];
	u32 hdr_num_entries[MAX_FW_IMAGES];
};

struct brcms_info {
	struct brcms_pub *pub;		/* pointer to public wlc state */
	struct brcms_c_info *wlc;	/* pointer to private common data */
	u32 magic;

	int irq;

	spinlock_t lock;	/* per-device perimeter lock */
	spinlock_t isr_lock;	/* per-device ISR synchronization lock */


	/* timer related fields */
	atomic_t callbacks;	/* # outstanding callback functions */
	struct brcms_timer *timers;	/* timer cleanup queue */

	struct tasklet_struct tasklet;	/* dpc tasklet */
	bool resched;		/* dpc needs to be and is rescheduled */
	struct brcms_firmware fw;
	struct wiphy *wiphy;
	struct brcms_ucode ucode;
	bool mute_tx;
};

/* misc callbacks */
extern void brcms_init(struct brcms_info *wl);
extern uint brcms_reset(struct brcms_info *wl);
extern void brcms_intrson(struct brcms_info *wl);
extern u32 brcms_intrsoff(struct brcms_info *wl);
extern void brcms_intrsrestore(struct brcms_info *wl, u32 macintmask);
extern int brcms_up(struct brcms_info *wl);
extern void brcms_down(struct brcms_info *wl);
extern void brcms_txflowcontrol(struct brcms_info *wl, struct brcms_if *wlif,
				bool state, int prio);
extern bool brcms_rfkill_set_hw_state(struct brcms_info *wl);

/* timer functions */
extern struct brcms_timer *brcms_init_timer(struct brcms_info *wl,
				      void (*fn) (void *arg), void *arg,
				      const char *name);
extern void brcms_free_timer(struct brcms_timer *timer);
extern void brcms_add_timer(struct brcms_timer *timer, uint ms, int periodic);
extern bool brcms_del_timer(struct brcms_timer *timer);
extern void brcms_msleep(struct brcms_info *wl, uint ms);
extern void brcms_dpc(unsigned long data);
extern void brcms_timer(struct brcms_timer *t);
extern void brcms_fatal_error(struct brcms_info *wl);

#endif				/* _BRCM_MAC80211_IF_H_ */
