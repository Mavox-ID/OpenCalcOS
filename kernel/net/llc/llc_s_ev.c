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
#include <beep/socket.h>
#include <net/sock.h>
#include <net/llc_if.h>
#include <net/llc_s_ev.h>
#include <net/llc_pdu.h>

int llc_sap_ev_activation_req(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);

	return ev->type == LLC_SAP_EV_TYPE_SIMPLE &&
	       ev->prim_type == LLC_SAP_EV_ACTIVATION_REQ ? 0 : 1;
}

int llc_sap_ev_rx_ui(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);
	struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	return ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_CMD(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_CMD(pdu) == LLC_1_PDU_CMD_UI ? 0 : 1;
}

int llc_sap_ev_unitdata_req(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);

	return ev->type == LLC_SAP_EV_TYPE_PRIM &&
	       ev->prim == LLC_DATAUNIT_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;

}

int llc_sap_ev_xid_req(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);

	return ev->type == LLC_SAP_EV_TYPE_PRIM &&
	       ev->prim == LLC_XID_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
}

int llc_sap_ev_rx_xid_c(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);
	struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	return ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_CMD(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_CMD(pdu) == LLC_1_PDU_CMD_XID ? 0 : 1;
}

int llc_sap_ev_rx_xid_r(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);
	struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	return ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_RSP(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_RSP(pdu) == LLC_1_PDU_CMD_XID ? 0 : 1;
}

int llc_sap_ev_test_req(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);

	return ev->type == LLC_SAP_EV_TYPE_PRIM &&
	       ev->prim == LLC_TEST_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
}

int llc_sap_ev_rx_test_c(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);
	struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	return ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_CMD(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_CMD(pdu) == LLC_1_PDU_CMD_TEST ? 0 : 1;
}

int llc_sap_ev_rx_test_r(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);
	struct llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	return ev->type == LLC_SAP_EV_TYPE_PDU && LLC_PDU_IS_RSP(pdu) &&
	       LLC_PDU_TYPE_IS_U(pdu) &&
	       LLC_U_PDU_RSP(pdu) == LLC_1_PDU_CMD_TEST ? 0 : 1;
}

int llc_sap_ev_deactivation_req(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_sap_state_ev *ev = llc_sap_ev(skb);

	return ev->type == LLC_SAP_EV_TYPE_SIMPLE &&
	       ev->prim_type == LLC_SAP_EV_DEACTIVATION_REQ ? 0 : 1;
}
