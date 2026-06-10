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
#ifndef _SCIC_SDS_UNSOLICITED_FRAME_CONTROL_H_
#define _SCIC_SDS_UNSOLICITED_FRAME_CONTROL_H_

#include "isci.h"

#define SCU_UNSOLICITED_FRAME_HEADER_DATA_DWORDS 15

/**
 * struct scu_unsolicited_frame_header -
 *
 * This structure delineates the format of an unsolicited frame header. The
 * first DWORD are UF attributes defined by the silicon architecture. The data
 * depicts actual header information received on the link.
 */
struct scu_unsolicited_frame_header {
	/**
	 * This field indicates if there is an Initiator Index Table entry with
	 * which this header is associated.
	 */
	u32 iit_exists:1;

	/**
	 * This field simply indicates the protocol type (i.e. SSP, STP, SMP).
	 */
	u32 protocol_type:3;

	/**
	 * This field indicates if the frame is an address frame (IAF or OAF)
	 * or if it is a information unit frame.
	 */
	u32 is_address_frame:1;

	/**
	 * This field simply indicates the connection rate at which the frame
	 * was received.
	 */
	u32 connection_rate:4;

	u32 reserved:23;

	/**
	 * This field represents the actual header data received on the link.
	 */
	u32 data[SCU_UNSOLICITED_FRAME_HEADER_DATA_DWORDS];

};



/**
 * enum unsolicited_frame_state -
 *
 * This enumeration represents the current unsolicited frame state.  The
 * controller object can not updtate the hardware unsolicited frame put pointer
 * unless it has already processed the priror unsolicited frames.
 */
enum unsolicited_frame_state {
	/**
	 * This state is when the frame is empty and not in use.  It is
	 * different from the released state in that the hardware could DMA
	 * data to this frame buffer.
	 */
	UNSOLICITED_FRAME_EMPTY,

	/**
	 * This state is set when the frame buffer is in use by by some
	 * object in the system.
	 */
	UNSOLICITED_FRAME_IN_USE,

	/**
	 * This state is set when the frame is returned to the free pool
	 * but one or more frames prior to this one are still in use.
	 * Once all of the frame before this one are freed it will go to
	 * the empty state.
	 */
	UNSOLICITED_FRAME_RELEASED,

	UNSOLICITED_FRAME_MAX_STATES
};

/**
 * struct sci_unsolicited_frame -
 *
 * This is the unsolicited frame data structure it acts as the container for
 * the current frame state, frame header and frame buffer.
 */
struct sci_unsolicited_frame {
	/**
	 * This field contains the current frame state
	 */
	enum unsolicited_frame_state state;

	/**
	 * This field points to the frame header data.
	 */
	struct scu_unsolicited_frame_header *header;

	/**
	 * This field points to the frame buffer data.
	 */
	void *buffer;

};

/**
 * struct sci_uf_header_array -
 *
 * This structure contains all of the unsolicited frame header information.
 */
struct sci_uf_header_array {
	/**
	 * This field is represents a virtual pointer to the start
	 * address of the UF address table.  The table contains
	 * 64-bit pointers as required by the hardware.
	 */
	struct scu_unsolicited_frame_header *array;

	/**
	 * This field specifies the physical address location for the UF
	 * buffer array.
	 */
	dma_addr_t physical_address;

};

/**
 * struct sci_uf_buffer_array -
 *
 * This structure contains all of the unsolicited frame buffer (actual payload)
 * information.
 */
struct sci_uf_buffer_array {
	/**
	 * This field is the unsolicited frame data its used to manage
	 * the data for the unsolicited frame requests.  It also represents
	 * the virtual address location that corresponds to the
	 * physical_address field.
	 */
	struct sci_unsolicited_frame array[SCU_MAX_UNSOLICITED_FRAMES];

	/**
	 * This field specifies the physical address location for the UF
	 * buffer array.
	 */
	dma_addr_t physical_address;
};

/**
 * struct sci_uf_address_table_array -
 *
 * This object maintains all of the unsolicited frame address table specific
 * data.  The address table is a collection of 64-bit pointers that point to
 * 1KB buffers into which the silicon will DMA unsolicited frames.
 */
struct sci_uf_address_table_array {
	/**
	 * This field represents a virtual pointer that refers to the
	 * starting address of the UF address table.
	 * 64-bit pointers are required by the hardware.
	 */
	u64 *array;

	/**
	 * This field specifies the physical address location for the UF
	 * address table.
	 */
	dma_addr_t physical_address;

};

/**
 * struct sci_unsolicited_frame_control -
 *
 * This object contains all of the data necessary to handle unsolicited frames.
 */
struct sci_unsolicited_frame_control {
	/**
	 * This field is the software copy of the unsolicited frame queue
	 * get pointer.  The controller object writes this value to the
	 * hardware to let the hardware put more unsolicited frame entries.
	 */
	u32 get;

	/**
	 * This field contains all of the unsolicited frame header
	 * specific fields.
	 */
	struct sci_uf_header_array headers;

	/**
	 * This field contains all of the unsolicited frame buffer
	 * specific fields.
	 */
	struct sci_uf_buffer_array buffers;

	/**
	 * This field contains all of the unsolicited frame address table
	 * specific fields.
	 */
	struct sci_uf_address_table_array address_table;

};

#define SCI_UFI_BUF_SIZE (SCU_MAX_UNSOLICITED_FRAMES * SCU_UNSOLICITED_FRAME_BUFFER_SIZE)
#define SCI_UFI_HDR_SIZE (SCU_MAX_UNSOLICITED_FRAMES * sizeof(struct scu_unsolicited_frame_header))
#define SCI_UFI_TOTAL_SIZE (SCI_UFI_BUF_SIZE + SCI_UFI_HDR_SIZE + SCU_MAX_UNSOLICITED_FRAMES * sizeof(u64))

struct isci_host;

void sci_unsolicited_frame_control_construct(struct isci_host *ihost);

enum sci_status sci_unsolicited_frame_control_get_header(
	struct sci_unsolicited_frame_control *uf_control,
	u32 frame_index,
	void **frame_header);

enum sci_status sci_unsolicited_frame_control_get_buffer(
	struct sci_unsolicited_frame_control *uf_control,
	u32 frame_index,
	void **frame_buffer);

bool sci_unsolicited_frame_control_release_frame(
	struct sci_unsolicited_frame_control *uf_control,
	u32 frame_index);

#endif /* _SCIC_SDS_UNSOLICITED_FRAME_CONTROL_H_ */
