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
#define CDC_NCM_COMM_ALTSETTING_NCM		0
#define CDC_NCM_COMM_ALTSETTING_MBIM		1

#define CDC_NCM_DATA_ALTSETTING_NCM		1
#define CDC_NCM_DATA_ALTSETTING_MBIM		2

/* CDC NCM subclass 3.2.1 */
#define USB_CDC_NCM_NDP16_LENGTH_MIN		0x10

/* Maximum NTB length */
#define	CDC_NCM_NTB_MAX_SIZE_TX			32768	/* bytes */
#define	CDC_NCM_NTB_MAX_SIZE_RX			32768	/* bytes */

/* Minimum value for MaxDatagramSize, ch. 6.2.9 */
#define	CDC_NCM_MIN_DATAGRAM_SIZE		1514	/* bytes */

/* Minimum value for MaxDatagramSize, ch. 8.1.3 */
#define CDC_MBIM_MIN_DATAGRAM_SIZE		2048	/* bytes */

#define	CDC_NCM_MIN_TX_PKT			512	/* bytes */

/* Default value for MaxDatagramSize */
#define	CDC_NCM_MAX_DATAGRAM_SIZE		8192	/* bytes */

/*
 * Maximum amount of datagrams in NCM Datagram Pointer Table, not counting
 * the last NULL entry.
 */
#define	CDC_NCM_DPT_DATAGRAMS_MAX		40

/* Restart the timer, if amount of datagrams is less than given value */
#define	CDC_NCM_RESTART_TIMER_DATAGRAM_CNT	3
#define	CDC_NCM_TIMER_PENDING_CNT		2
#define CDC_NCM_TIMER_INTERVAL			(400UL * NSEC_PER_USEC)

/* The following macro defines the minimum header space */
#define	CDC_NCM_MIN_HDR_SIZE \
	(sizeof(struct usb_cdc_ncm_nth16) + sizeof(struct usb_cdc_ncm_ndp16) + \
	(CDC_NCM_DPT_DATAGRAMS_MAX + 1) * sizeof(struct usb_cdc_ncm_dpe16))

#define CDC_NCM_NDP_SIZE \
	(sizeof(struct usb_cdc_ncm_ndp16) +				\
	      (CDC_NCM_DPT_DATAGRAMS_MAX + 1) * sizeof(struct usb_cdc_ncm_dpe16))

#define cdc_ncm_comm_intf_is_mbim(x)  ((x)->desc.bInterfaceSubClass == USB_CDC_SUBCLASS_MBIM && \
				       (x)->desc.bInterfaceProtocol == USB_CDC_PROTO_NONE)
#define cdc_ncm_data_intf_is_mbim(x)  ((x)->desc.bInterfaceProtocol == USB_CDC_MBIM_PROTO_NTB)

struct cdc_ncm_ctx {
	struct usb_cdc_ncm_ntb_parameters ncm_parm;
	struct hrtimer tx_timer;
	struct tasklet_struct bh;

	const struct usb_cdc_ncm_desc *func_desc;
	const struct usb_cdc_mbim_desc   *mbim_desc;
	const struct usb_cdc_header_desc *header_desc;
	const struct usb_cdc_union_desc *union_desc;
	const struct usb_cdc_ether_desc *ether_desc;

	struct net_device *netdev;
	struct usb_device *udev;
	struct usb_host_endpoint *in_ep;
	struct usb_host_endpoint *out_ep;
	struct usb_host_endpoint *status_ep;
	struct usb_interface *intf;
	struct usb_interface *control;
	struct usb_interface *data;

	struct sk_buff *tx_curr_skb;
	struct sk_buff *tx_rem_skb;
	__le32 tx_rem_sign;

	spinlock_t mtx;
	atomic_t stop;

	u32 tx_timer_pending;
	u32 tx_curr_frame_num;
	u32 rx_speed;
	u32 tx_speed;
	u32 rx_max;
	u32 tx_max;
	u32 max_datagram_size;
	u16 tx_max_datagrams;
	u16 tx_remainder;
	u16 tx_modulus;
	u16 tx_ndp_modulus;
	u16 tx_seq;
	u16 rx_seq;
	u16 connected;
};

extern int cdc_ncm_bind_common(struct usbnet *dev, struct usb_interface *intf, u8 data_altsetting);
extern void cdc_ncm_unbind(struct usbnet *dev, struct usb_interface *intf);
extern struct sk_buff *cdc_ncm_fill_tx_frame(struct cdc_ncm_ctx *ctx, struct sk_buff *skb, __le32 sign);
extern int cdc_ncm_rx_verify_nth16(struct cdc_ncm_ctx *ctx, struct sk_buff *skb_in);
extern int cdc_ncm_rx_verify_ndp16(struct sk_buff *skb_in, int ndpoffset);
