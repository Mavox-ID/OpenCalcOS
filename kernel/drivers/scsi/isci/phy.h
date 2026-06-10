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
#ifndef _ISCI_PHY_H_
#define _ISCI_PHY_H_

#include <scsi/sas.h>
#include <scsi/libsas.h>
#include "isci.h"
#include "sas.h"

/* This is the timeout value for the SATA phy to wait for a SIGNATURE FIS
 * before restarting the starting state machine.  Technically, the old parallel
 * ATA specification required up to 30 seconds for a device to issue its
 * signature FIS as a result of a soft reset.  Now we see that devices respond
 * generally within 15 seconds, but we'll use 25 for now.
 */
#define SCIC_SDS_SIGNATURE_FIS_TIMEOUT    25000

/* This is the timeout for the SATA OOB/SN because the hardware does not
 * recognize a hot plug after OOB signal but before the SN signals.  We need to
 * make sure after a hotplug timeout if we have not received the speed event
 * notification from the hardware that we restart the hardware OOB state
 * machine.
 */
#define SCIC_SDS_SATA_LINK_TRAINING_TIMEOUT  250

/**
 * isci_phy - hba local phy infrastructure
 * @sm:
 * @protocol: attached device protocol
 * @phy_index: physical index relative to the controller (0-3)
 * @bcn_received_while_port_unassigned: bcn to report after port association
 * @sata_timer: timeout SATA signature FIS arrival
 */
struct isci_phy {
	struct sci_base_state_machine sm;
	struct isci_port *owning_port;
	enum sas_linkrate max_negotiated_speed;
	enum sas_protocol protocol;
	u8 phy_index;
	bool bcn_received_while_port_unassigned;
	bool is_in_link_training;
	struct sci_timer sata_timer;
	struct scu_transport_layer_registers __iomem *transport_layer_registers;
	struct scu_link_layer_registers __iomem *link_layer_registers;
	struct asd_sas_phy sas_phy;
	u8 sas_addr[SAS_ADDR_SIZE];
	union {
		struct sas_identify_frame iaf;
		struct dev_to_host_fis fis;
	} frame_rcvd;
};

static inline struct isci_phy *to_iphy(struct asd_sas_phy *sas_phy)
{
	struct isci_phy *iphy = container_of(sas_phy, typeof(*iphy), sas_phy);

	return iphy;
}

struct sci_phy_cap {
	union {
		struct {
			/*
			 * The SAS specification indicates the start bit shall
			 * always be set to
			 * 1.  This implementation will have the start bit set
			 * to 0 if the PHY CAPABILITIES were either not
			 * received or speed negotiation failed.
			 */
			u8 start:1;
			u8 tx_ssc_type:1;
			u8 res1:2;
			u8 req_logical_linkrate:4;

			u32 gen1_no_ssc:1;
			u32 gen1_ssc:1;
			u32 gen2_no_ssc:1;
			u32 gen2_ssc:1;
			u32 gen3_no_ssc:1;
			u32 gen3_ssc:1;
			u32 res2:17;
			u32 parity:1;
		};
		u32 all;
	};
}  __packed;

/* this data structure reflects the link layer transmit identification reg */
struct sci_phy_proto {
	union {
		struct {
			u16 _r_a:1;
			u16 smp_iport:1;
			u16 stp_iport:1;
			u16 ssp_iport:1;
			u16 _r_b:4;
			u16 _r_c:1;
			u16 smp_tport:1;
			u16 stp_tport:1;
			u16 ssp_tport:1;
			u16 _r_d:4;
		};
		u16 all;
	};
} __packed;


/**
 * struct sci_phy_properties - This structure defines the properties common to
 *    all phys that can be retrieved.
 *
 *
 */
struct sci_phy_properties {
	/**
	 * This field specifies the port that currently contains the
	 * supplied phy.  This field may be set to NULL
	 * if the phy is not currently contained in a port.
	 */
	struct isci_port *iport;

	/**
	 * This field specifies the link rate at which the phy is
	 * currently operating.
	 */
	enum sas_linkrate negotiated_link_rate;

	/**
	 * This field specifies the index of the phy in relation to other
	 * phys within the controller.  This index is zero relative.
	 */
	u8 index;
};

/**
 * struct sci_sas_phy_properties - This structure defines the properties,
 *    specific to a SAS phy, that can be retrieved.
 *
 *
 */
struct sci_sas_phy_properties {
	/**
	 * This field delineates the Identify Address Frame received
	 * from the remote end point.
	 */
	struct sas_identify_frame rcvd_iaf;

	/**
	 * This field delineates the Phy capabilities structure received
	 * from the remote end point.
	 */
	struct sci_phy_cap rcvd_cap;

};

/**
 * struct sci_sata_phy_properties - This structure defines the properties,
 *    specific to a SATA phy, that can be retrieved.
 *
 *
 */
struct sci_sata_phy_properties {
	/**
	 * This field delineates the signature FIS received from the
	 * attached target.
	 */
	struct dev_to_host_fis signature_fis;

	/**
	 * This field specifies to the user if a port selector is connected
	 * on the specified phy.
	 */
	bool is_port_selector_present;

};

/**
 * enum sci_phy_counter_id - This enumeration depicts the various pieces of
 *    optional information that can be retrieved for a specific phy.
 *
 *
 */
enum sci_phy_counter_id {
	/**
	 * This PHY information field tracks the number of frames received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME,

	/**
	 * This PHY information field tracks the number of frames transmitted.
	 */
	SCIC_PHY_COUNTER_TRANSMITTED_FRAME,

	/**
	 * This PHY information field tracks the number of DWORDs received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME_WORD,

	/**
	 * This PHY information field tracks the number of DWORDs transmitted.
	 */
	SCIC_PHY_COUNTER_TRANSMITTED_FRAME_DWORD,

	/**
	 * This PHY information field tracks the number of times DWORD
	 * synchronization was lost.
	 */
	SCIC_PHY_COUNTER_LOSS_OF_SYNC_ERROR,

	/**
	 * This PHY information field tracks the number of received DWORDs with
	 * running disparity errors.
	 */
	SCIC_PHY_COUNTER_RECEIVED_DISPARITY_ERROR,

	/**
	 * This PHY information field tracks the number of received frames with a
	 * CRC error (not including short or truncated frames).
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME_CRC_ERROR,

	/**
	 * This PHY information field tracks the number of DONE (ACK/NAK TIMEOUT)
	 * primitives received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_DONE_ACK_NAK_TIMEOUT,

	/**
	 * This PHY information field tracks the number of DONE (ACK/NAK TIMEOUT)
	 * primitives transmitted.
	 */
	SCIC_PHY_COUNTER_TRANSMITTED_DONE_ACK_NAK_TIMEOUT,

	/**
	 * This PHY information field tracks the number of times the inactivity
	 * timer for connections on the phy has been utilized.
	 */
	SCIC_PHY_COUNTER_INACTIVITY_TIMER_EXPIRED,

	/**
	 * This PHY information field tracks the number of DONE (CREDIT TIMEOUT)
	 * primitives received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_DONE_CREDIT_TIMEOUT,

	/**
	 * This PHY information field tracks the number of DONE (CREDIT TIMEOUT)
	 * primitives transmitted.
	 */
	SCIC_PHY_COUNTER_TRANSMITTED_DONE_CREDIT_TIMEOUT,

	/**
	 * This PHY information field tracks the number of CREDIT BLOCKED
	 * primitives received.
	 * @note Depending on remote device implementation, credit blocks
	 *       may occur regularly.
	 */
	SCIC_PHY_COUNTER_RECEIVED_CREDIT_BLOCKED,

	/**
	 * This PHY information field contains the number of short frames
	 * received.  A short frame is simply a frame smaller then what is
	 * allowed by either the SAS or SATA specification.
	 */
	SCIC_PHY_COUNTER_RECEIVED_SHORT_FRAME,

	/**
	 * This PHY information field contains the number of frames received after
	 * credit has been exhausted.
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME_WITHOUT_CREDIT,

	/**
	 * This PHY information field contains the number of frames received after
	 * a DONE has been received.
	 */
	SCIC_PHY_COUNTER_RECEIVED_FRAME_AFTER_DONE,

	/**
	 * This PHY information field contains the number of times the phy
	 * failed to achieve DWORD synchronization during speed negotiation.
	 */
	SCIC_PHY_COUNTER_SN_DWORD_SYNC_ERROR
};

/**
 * enum sci_phy_states - phy state machine states
 * @SCI_PHY_INITIAL: Simply the initial state for the base domain state
 *		     machine.
 * @SCI_PHY_STOPPED: phy has successfully been stopped.  In this state
 *		     no new IO operations are permitted on this phy.
 * @SCI_PHY_STARTING: the phy is in the process of becomming ready.  In
 *		      this state no new IO operations are permitted on
 *		      this phy.
 * @SCI_PHY_SUB_INITIAL: Initial state
 * @SCI_PHY_SUB_AWAIT_OSSP_EN: Wait state for the hardware OSSP event
 *			       type notification
 * @SCI_PHY_SUB_AWAIT_SAS_SPEED_EN: Wait state for the PHY speed
 *				    notification
 * @SCI_PHY_SUB_AWAIT_IAF_UF: Wait state for the IAF Unsolicited frame
 *			      notification
 * @SCI_PHY_SUB_AWAIT_SAS_POWER: Wait state for the request to consume
 *				 power
 * @SCI_PHY_SUB_AWAIT_SATA_POWER: Wait state for request to consume
 *				  power
 * @SCI_PHY_SUB_AWAIT_SATA_PHY_EN: Wait state for the SATA PHY
 *				   notification
 * @SCI_PHY_SUB_AWAIT_SATA_SPEED_EN: Wait for the SATA PHY speed
 *				     notification
 * @SCI_PHY_SUB_AWAIT_SIG_FIS_UF: Wait state for the SIGNATURE FIS
 *				  unsolicited frame notification
 * @SCI_PHY_SUB_FINAL: Exit state for this state machine
 * @SCI_PHY_READY: phy is now ready.  Thus, the user is able to perform
 *		   IO operations utilizing this phy as long as it is
 *		   currently part of a valid port.  This state is
 *		   entered from the STARTING state.
 * @SCI_PHY_RESETTING: phy is in the process of being reset.  In this
 *		       state no new IO operations are permitted on this
 *		       phy.  This state is entered from the READY state.
 * @SCI_PHY_FINAL: Simply the final state for the base phy state
 *		   machine.
 */
#define PHY_STATES {\
	C(PHY_INITIAL),\
	C(PHY_STOPPED),\
	C(PHY_STARTING),\
	C(PHY_SUB_INITIAL),\
	C(PHY_SUB_AWAIT_OSSP_EN),\
	C(PHY_SUB_AWAIT_SAS_SPEED_EN),\
	C(PHY_SUB_AWAIT_IAF_UF),\
	C(PHY_SUB_AWAIT_SAS_POWER),\
	C(PHY_SUB_AWAIT_SATA_POWER),\
	C(PHY_SUB_AWAIT_SATA_PHY_EN),\
	C(PHY_SUB_AWAIT_SATA_SPEED_EN),\
	C(PHY_SUB_AWAIT_SIG_FIS_UF),\
	C(PHY_SUB_FINAL),\
	C(PHY_READY),\
	C(PHY_RESETTING),\
	C(PHY_FINAL),\
	}
#undef C
#define C(a) SCI_##a
enum sci_phy_states PHY_STATES;
#undef C

void sci_phy_construct(
	struct isci_phy *iphy,
	struct isci_port *iport,
	u8 phy_index);

struct isci_port *phy_get_non_dummy_port(struct isci_phy *iphy);

void sci_phy_set_port(
	struct isci_phy *iphy,
	struct isci_port *iport);

enum sci_status sci_phy_initialize(
	struct isci_phy *iphy,
	struct scu_transport_layer_registers __iomem *transport_layer_registers,
	struct scu_link_layer_registers __iomem *link_layer_registers);

enum sci_status sci_phy_start(
	struct isci_phy *iphy);

enum sci_status sci_phy_stop(
	struct isci_phy *iphy);

enum sci_status sci_phy_reset(
	struct isci_phy *iphy);

void sci_phy_resume(
	struct isci_phy *iphy);

void sci_phy_setup_transport(
	struct isci_phy *iphy,
	u32 device_id);

enum sci_status sci_phy_event_handler(
	struct isci_phy *iphy,
	u32 event_code);

enum sci_status sci_phy_frame_handler(
	struct isci_phy *iphy,
	u32 frame_index);

enum sci_status sci_phy_consume_power_handler(
	struct isci_phy *iphy);

void sci_phy_get_sas_address(
	struct isci_phy *iphy,
	struct sci_sas_address *sas_address);

void sci_phy_get_attached_sas_address(
	struct isci_phy *iphy,
	struct sci_sas_address *sas_address);

struct sci_phy_proto;
void sci_phy_get_protocols(
	struct isci_phy *iphy,
	struct sci_phy_proto *protocols);
enum sas_linkrate sci_phy_linkrate(struct isci_phy *iphy);

struct isci_host;
void isci_phy_init(struct isci_phy *iphy, struct isci_host *ihost, int index);
int isci_phy_control(struct asd_sas_phy *phy, enum phy_func func, void *buf);

#endif /* !defined(_ISCI_PHY_H_) */
