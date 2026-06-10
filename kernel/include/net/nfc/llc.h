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
#ifndef __NFC_LLC_H_
#define __NFC_LLC_H_

#include <net/nfc/hci.h>
#include <beep/skbuff.h>

#define LLC_NOP_NAME "nop"
#define LLC_SHDLC_NAME "shdlc"

typedef void (*rcv_to_hci_t) (struct nfc_hci_dev *hdev, struct sk_buff *skb);
typedef int (*xmit_to_drv_t) (struct nfc_hci_dev *hdev, struct sk_buff *skb);
typedef void (*llc_failure_t) (struct nfc_hci_dev *hdev, int err);

struct nfc_llc;

struct nfc_llc *nfc_llc_allocate(const char *name, struct nfc_hci_dev *hdev,
				 xmit_to_drv_t xmit_to_drv,
				 rcv_to_hci_t rcv_to_hci, int tx_headroom,
				 int tx_tailroom, llc_failure_t llc_failure);
void nfc_llc_free(struct nfc_llc *llc);

void nfc_llc_get_rx_head_tail_room(struct nfc_llc *llc, int *rx_headroom,
				   int *rx_tailroom);


int nfc_llc_start(struct nfc_llc *llc);
int nfc_llc_stop(struct nfc_llc *llc);
void nfc_llc_rcv_from_drv(struct nfc_llc *llc, struct sk_buff *skb);
int nfc_llc_xmit_from_hci(struct nfc_llc *llc, struct sk_buff *skb);

int nfc_llc_init(void);
void nfc_llc_exit(void);

#endif /* __NFC_LLC_H_ */
