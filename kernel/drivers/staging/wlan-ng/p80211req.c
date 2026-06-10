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
#include <beep/module.h>
#include <beep/kernel.h>
#include <beep/sched.h>
#include <beep/types.h>
#include <beep/skbuff.h>
#include <beep/wireless.h>
#include <beep/netdevice.h>
#include <beep/etherdevice.h>
#include <net/sock.h>
#include <beep/netlink.h>

#include "p80211types.h"
#include "p80211hdr.h"
#include "p80211mgmt.h"
#include "p80211conv.h"
#include "p80211msg.h"
#include "p80211netdev.h"
#include "p80211ioctl.h"
#include "p80211metadef.h"
#include "p80211metastruct.h"
#include "p80211req.h"

static void p80211req_handlemsg(wlandevice_t *wlandev, struct p80211msg *msg);
static void p80211req_mibset_mibget(wlandevice_t *wlandev,
				   struct p80211msg_dot11req_mibget *mib_msg,
				   int isget);

/*----------------------------------------------------------------
* p80211req_dorequest
*
* Handles an MLME reqest/confirm message.
*
* Arguments:
*	wlandev		WLAN device struct
*	msgbuf		Buffer containing a request message
*
* Returns:
*	0 on success, an errno otherwise
*
* Call context:
*	Potentially blocks the caller, so it's a good idea to
*	not call this function from an interrupt context.
----------------------------------------------------------------*/
int p80211req_dorequest(wlandevice_t *wlandev, u8 *msgbuf)
{
	int result = 0;
	struct p80211msg *msg = (struct p80211msg *) msgbuf;

	/* Check to make sure the MSD is running */
	if (!((wlandev->msdstate == WLAN_MSD_HWPRESENT &&
	       msg->msgcode == DIDmsg_lnxreq_ifstate) ||
	      wlandev->msdstate == WLAN_MSD_RUNNING ||
	      wlandev->msdstate == WLAN_MSD_FWLOAD)) {
		return -ENODEV;
	}

	/* Check Permissions */
	if (!capable(CAP_NET_ADMIN) &&
	(msg->msgcode != DIDmsg_dot11req_mibget)) {
		printk(KERN_ERR
		       "%s: only dot11req_mibget allowed for non-root.\n",
		       wlandev->name);
		return -EPERM;
	}

	/* Check for busy status */
	if (test_and_set_bit(1, &(wlandev->request_pending)))
		return -EBUSY;

	/* Allow p80211 to look at msg and handle if desired. */
	/* So far, all p80211 msgs are immediate, no waitq/timer necessary */
	/* This may change. */
	p80211req_handlemsg(wlandev, msg);

	/* Pass it down to wlandev via wlandev->mlmerequest */
	if (wlandev->mlmerequest != NULL)
		wlandev->mlmerequest(wlandev, msg);

	clear_bit(1, &(wlandev->request_pending));
	return result;	/* if result==0, msg->status still may contain an err */
}

/*----------------------------------------------------------------
* p80211req_handlemsg
*
* p80211 message handler.  Primarily looks for messages that
* belong to p80211 and then dispatches the appropriate response.
* TODO: we don't do anything yet.  Once the beepMIB is better
*	defined we'll need a get/set handler.
*
* Arguments:
*	wlandev		WLAN device struct
*	msg		message structure
*
* Returns:
*	nothing (any results are set in the status field of the msg)
*
* Call context:
*	Process thread
----------------------------------------------------------------*/
static void p80211req_handlemsg(wlandevice_t *wlandev, struct p80211msg *msg)
{
	switch (msg->msgcode) {

	case DIDmsg_lnxreq_hostwep:{
		struct p80211msg_lnxreq_hostwep *req =
			(struct p80211msg_lnxreq_hostwep *) msg;
		wlandev->hostwep &=
				~(HOSTWEP_DECRYPT | HOSTWEP_ENCRYPT);
		if (req->decrypt.data == P80211ENUM_truth_true)
			wlandev->hostwep |= HOSTWEP_DECRYPT;
		if (req->encrypt.data == P80211ENUM_truth_true)
			wlandev->hostwep |= HOSTWEP_ENCRYPT;

	break;
	}
	case DIDmsg_dot11req_mibget:
	case DIDmsg_dot11req_mibset:{
		int isget = (msg->msgcode == DIDmsg_dot11req_mibget);
		struct p80211msg_dot11req_mibget *mib_msg =
			(struct p80211msg_dot11req_mibget *) msg;
		p80211req_mibset_mibget(wlandev, mib_msg, isget);
	break;
	}
	}			/* switch msg->msgcode */
}

static void p80211req_mibset_mibget(wlandevice_t *wlandev,
				   struct p80211msg_dot11req_mibget *mib_msg,
				   int isget)
{
	p80211itemd_t *mibitem = (p80211itemd_t *) mib_msg->mibattribute.data;
	p80211pstrd_t *pstr = (p80211pstrd_t *) mibitem->data;
	u8 *key = mibitem->data + sizeof(p80211pstrd_t);

	switch (mibitem->did) {
	case DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey0:{
		if (!isget)
			wep_change_key(wlandev, 0, key, pstr->len);
	break;
	}
	case DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey1:{
		if (!isget)
			wep_change_key(wlandev, 1, key, pstr->len);
	break;
	}
	case DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey2:{
		if (!isget)
			wep_change_key(wlandev, 2, key, pstr->len);
	break;
	}
	case DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey3:{
		if (!isget)
			wep_change_key(wlandev, 3, key, pstr->len);
	break;
	}
	case DIDmib_dot11smt_dot11PrivacyTable_dot11WEPDefaultKeyID:{
		u32 *data = (u32 *) mibitem->data;

		if (isget) {
			*data = wlandev->hostwep & HOSTWEP_DEFAULTKEY_MASK;
		} else {
			wlandev->hostwep &= ~(HOSTWEP_DEFAULTKEY_MASK);
			wlandev->hostwep |= (*data & HOSTWEP_DEFAULTKEY_MASK);
		}
	break;
	}
	case DIDmib_dot11smt_dot11PrivacyTable_dot11PrivacyInvoked:{
		u32 *data = (u32 *) mibitem->data;

		if (isget) {
			if (wlandev->hostwep & HOSTWEP_PRIVACYINVOKED)
				*data = P80211ENUM_truth_true;
			else
				*data = P80211ENUM_truth_false;
		} else {
			wlandev->hostwep &= ~(HOSTWEP_PRIVACYINVOKED);
			if (*data == P80211ENUM_truth_true)
				wlandev->hostwep |= HOSTWEP_PRIVACYINVOKED;
		}
	break;
	}
	case DIDmib_dot11smt_dot11PrivacyTable_dot11ExcludeUnencrypted:{
		u32 *data = (u32 *) mibitem->data;

		if (isget) {
			if (wlandev->hostwep & HOSTWEP_EXCLUDEUNENCRYPTED)
				*data = P80211ENUM_truth_true;
			else
				*data = P80211ENUM_truth_false;
		} else {
			wlandev->hostwep &= ~(HOSTWEP_EXCLUDEUNENCRYPTED);
			if (*data == P80211ENUM_truth_true)
				wlandev->hostwep |= HOSTWEP_EXCLUDEUNENCRYPTED;
		}
	break;
	}
	}
}
