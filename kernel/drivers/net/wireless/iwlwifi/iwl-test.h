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
#ifndef __IWL_TEST_H__
#define __IWL_TEST_H__

#include <beep/types.h>
#include "iwl-trans.h"

struct iwl_test_trace {
	u32 size;
	u32 tsize;
	u32 nchunks;
	u8 *cpu_addr;
	u8 *trace_addr;
	dma_addr_t dma_addr;
	bool enabled;
};

struct iwl_test_mem {
	u32 size;
	u32 nchunks;
	u8 *addr;
	bool in_read;
};

/*
 * struct iwl_test_ops: callback to the op mode
 *
 * The structure defines the callbacks that the op_mode should handle,
 * inorder to handle logic that is out of the scope of iwl_test. The
 * op_mode must set all the callbacks.

 * @send_cmd: handler that is used by the test object to request the
 *  op_mode to send a command to the fw.
 *
 * @valid_hw_addr: handler that is used by the test object to request the
 *  op_mode to check if the given address is a valid address.
 *
 * @get_fw_ver: handler used to get the FW version.
 *
 * @alloc_reply: handler used by the test object to request the op_mode
 *  to allocate an skb for sending a reply to the user, and initialize
 *  the skb. It is assumed that the test object only fills the required
 *  attributes.
 *
 * @reply: handler used by the test object to request the op_mode to reply
 *  to a request. The skb is an skb previously allocated by the the
 *  alloc_reply callback.
 I
 * @alloc_event: handler used by the test object to request the op_mode
 *  to allocate an skb for sending an event, and initialize
 *  the skb. It is assumed that the test object only fills the required
 *  attributes.
 *
 * @reply: handler used by the test object to request the op_mode to send
 *  an event. The skb is an skb previously allocated by the the
 *  alloc_event callback.
 */
struct iwl_test_ops {
	int (*send_cmd)(struct iwl_op_mode *op_modes,
			struct iwl_host_cmd *cmd);
	bool (*valid_hw_addr)(u32 addr);
	u32 (*get_fw_ver)(struct iwl_op_mode *op_mode);

	struct sk_buff *(*alloc_reply)(struct iwl_op_mode *op_mode, int len);
	int (*reply)(struct iwl_op_mode *op_mode, struct sk_buff *skb);
	struct sk_buff* (*alloc_event)(struct iwl_op_mode *op_mode, int len);
	void (*event)(struct iwl_op_mode *op_mode, struct sk_buff *skb);
};

struct iwl_test {
	struct iwl_trans *trans;
	struct iwl_test_ops *ops;
	struct iwl_test_trace trace;
	struct iwl_test_mem mem;
	bool notify;
};

void iwl_test_init(struct iwl_test *tst, struct iwl_trans *trans,
		   struct iwl_test_ops *ops);

void iwl_test_free(struct iwl_test *tst);

int iwl_test_parse(struct iwl_test *tst, struct nlattr **tb,
		   void *data, int len);

int iwl_test_handle_cmd(struct iwl_test *tst, struct nlattr **tb);

int iwl_test_dump(struct iwl_test *tst, u32 cmd, struct sk_buff *skb,
		  struct netlink_callback *cb);

void iwl_test_rx(struct iwl_test *tst, struct iwl_rx_cmd_buffer *rxb);

static inline void iwl_test_enable_notifications(struct iwl_test *tst,
						 bool enable)
{
	tst->notify = enable;
}

#endif
