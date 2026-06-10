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
#ifndef _SCIC_SDS_REMOTE_NODE_CONTEXT_H_
#define _SCIC_SDS_REMOTE_NODE_CONTEXT_H_

/**
 * This file contains the structures, constants, and prototypes associated with
 *    the remote node context in the silicon.  It exists to model and manage
 *    the remote node context in the silicon.
 *
 *
 */

#include "isci.h"

/**
 *
 *
 * This constant represents an invalid remote device id, it is used to program
 * the STPDARNI register so the driver knows when it has received a SIGNATURE
 * FIS from the SCU.
 */
#define SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX    0x0FFF

enum sci_remote_node_suspension_reasons {
	SCI_HW_SUSPEND,
	SCI_SW_SUSPEND_NORMAL,
	SCI_SW_SUSPEND_LINKHANG_DETECT
};
#define SCI_SOFTWARE_SUSPEND_CMD SCU_CONTEXT_COMMAND_POST_RNC_SUSPEND_TX_RX
#define SCI_SOFTWARE_SUSPEND_EXPECTED_EVENT SCU_EVENT_TL_RNC_SUSPEND_TX_RX

struct isci_request;
struct isci_remote_device;
struct sci_remote_node_context;

typedef void (*scics_sds_remote_node_context_callback)(void *);

/**
 * enum sci_remote_node_context_states
 * @SCI_RNC_INITIAL initial state for a remote node context.  On a resume
 * request the remote node context will transition to the posting state.
 *
 * @SCI_RNC_POSTING: transition state that posts the RNi to the hardware. Once
 * the RNC is posted the remote node context will be made ready.
 *
 * @SCI_RNC_INVALIDATING: transition state that will post an RNC invalidate to
 * the hardware.  Once the invalidate is complete the remote node context will
 * transition to the posting state.
 *
 * @SCI_RNC_RESUMING: transition state that will post an RNC resume to the
 * hardare.  Once the event notification of resume complete is received the
 * remote node context will transition to the ready state.
 *
 * @SCI_RNC_READY: state that the remote node context must be in to accept io
 * request operations.
 *
 * @SCI_RNC_TX_SUSPENDED: state that the remote node context transitions to when
 * it gets a TX suspend notification from the hardware.
 *
 * @SCI_RNC_TX_RX_SUSPENDED: state that the remote node context transitions to
 * when it gets a TX RX suspend notification from the hardware.
 *
 * @SCI_RNC_AWAIT_SUSPENSION: wait state for the remote node context that waits
 * for a suspend notification from the hardware.  This state is entered when
 * either there is a request to supend the remote node context or when there is
 * a TC completion where the remote node will be suspended by the hardware.
 */
#define RNC_STATES {\
	C(RNC_INITIAL),\
	C(RNC_POSTING),\
	C(RNC_INVALIDATING),\
	C(RNC_RESUMING),\
	C(RNC_READY),\
	C(RNC_TX_SUSPENDED),\
	C(RNC_TX_RX_SUSPENDED),\
	C(RNC_AWAIT_SUSPENSION),\
	}
#undef C
#define C(a) SCI_##a
enum scis_sds_remote_node_context_states RNC_STATES;
#undef C
const char *rnc_state_name(enum scis_sds_remote_node_context_states state);

/**
 *
 *
 * This enumeration is used to define the end destination state for the remote
 * node context.
 */
enum sci_remote_node_context_destination_state {
	RNC_DEST_UNSPECIFIED,
	RNC_DEST_READY,
	RNC_DEST_FINAL,
	RNC_DEST_SUSPENDED,       /* Set when suspend during post/invalidate */
	RNC_DEST_SUSPENDED_RESUME /* Set when a resume was done during posting
				   * or invalidating and already suspending.
				   */
};

/**
 * struct sci_remote_node_context - This structure contains the data
 *    associated with the remote node context object.  The remote node context
 *    (RNC) object models the the remote device information necessary to manage
 *    the silicon RNC.
 */
struct sci_remote_node_context {
	/**
	 * This field indicates the remote node index (RNI) associated with
	 * this RNC.
	 */
	u16 remote_node_index;

	/**
	 * This field is the recored suspension type of the remote node
	 * context suspension.
	 */
	u32 suspend_type;
	enum sci_remote_node_suspension_reasons suspend_reason;
	u32 suspend_count;

	/**
	 * This field is true if the remote node context is resuming from its current
	 * state.  This can cause an automatic resume on receiving a suspension
	 * notification.
	 */
	enum sci_remote_node_context_destination_state destination_state;

	/**
	 * This field contains the callback function that the user requested to be
	 * called when the requested state transition is complete.
	 */
	scics_sds_remote_node_context_callback user_callback;

	/**
	 * This field contains the parameter that is called when the user requested
	 * state transition is completed.
	 */
	void *user_cookie;

	/**
	 * This field contains the data for the object's state machine.
	 */
	struct sci_base_state_machine sm;
};

void sci_remote_node_context_construct(struct sci_remote_node_context *rnc,
					    u16 remote_node_index);


bool sci_remote_node_context_is_ready(
	struct sci_remote_node_context *sci_rnc);

bool sci_remote_node_context_is_suspended(struct sci_remote_node_context *sci_rnc);

enum sci_status sci_remote_node_context_event_handler(struct sci_remote_node_context *sci_rnc,
							   u32 event_code);
enum sci_status sci_remote_node_context_destruct(struct sci_remote_node_context *sci_rnc,
						      scics_sds_remote_node_context_callback callback,
						      void *callback_parameter);
enum sci_status sci_remote_node_context_suspend(struct sci_remote_node_context *sci_rnc,
						     enum sci_remote_node_suspension_reasons reason,
						     u32 suspension_code);
enum sci_status sci_remote_node_context_resume(struct sci_remote_node_context *sci_rnc,
						    scics_sds_remote_node_context_callback cb_fn,
						    void *cb_p);
enum sci_status sci_remote_node_context_start_task(struct sci_remote_node_context *sci_rnc,
						   struct isci_request *ireq,
						   scics_sds_remote_node_context_callback cb_fn,
						   void *cb_p);
enum sci_status sci_remote_node_context_start_io(struct sci_remote_node_context *sci_rnc,
						      struct isci_request *ireq);
int sci_remote_node_context_is_safe_to_abort(
	struct sci_remote_node_context *sci_rnc);

static inline bool sci_remote_node_context_is_being_destroyed(
	struct sci_remote_node_context *sci_rnc)
{
	return (sci_rnc->destination_state == RNC_DEST_FINAL)
		|| ((sci_rnc->sm.current_state_id == SCI_RNC_INITIAL)
		    && (sci_rnc->destination_state == RNC_DEST_UNSPECIFIED));
}
#endif  /* _SCIC_SDS_REMOTE_NODE_CONTEXT_H_ */
