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
#include "host.h"
#include "unsolicited_frame_control.h"
#include "registers.h"

void sci_unsolicited_frame_control_construct(struct isci_host *ihost)
{
	struct sci_unsolicited_frame_control *uf_control = &ihost->uf_control;
	struct sci_unsolicited_frame *uf;
	dma_addr_t dma = ihost->ufi_dma;
	void *virt = ihost->ufi_buf;
	int i;

	/*
	 * The Unsolicited Frame buffers are set at the start of the UF
	 * memory descriptor entry. The headers and address table will be
	 * placed after the buffers.
	 */

	/*
	 * Program the location of the UF header table into the SCU.
	 * Notes:
	 * - The address must align on a 64-byte boundary. Guaranteed to be
	 *   on 64-byte boundary already 1KB boundary for unsolicited frames.
	 * - Program unused header entries to overlap with the last
	 *   unsolicited frame.  The silicon will never DMA to these unused
	 *   headers, since we program the UF address table pointers to
	 *   NULL.
	 */
	uf_control->headers.physical_address = dma + SCI_UFI_BUF_SIZE;
	uf_control->headers.array = virt + SCI_UFI_BUF_SIZE;

	/*
	 * Program the location of the UF address table into the SCU.
	 * Notes:
	 * - The address must align on a 64-bit boundary. Guaranteed to be on 64
	 *   byte boundary already due to above programming headers being on a
	 *   64-bit boundary and headers are on a 64-bytes in size.
	 */
	uf_control->address_table.physical_address = dma + SCI_UFI_BUF_SIZE + SCI_UFI_HDR_SIZE;
	uf_control->address_table.array = virt + SCI_UFI_BUF_SIZE + SCI_UFI_HDR_SIZE;
	uf_control->get = 0;

	/*
	 * UF buffer requirements are:
	 * - The last entry in the UF queue is not NULL.
	 * - There is a power of 2 number of entries (NULL or not-NULL)
	 *   programmed into the queue.
	 * - Aligned on a 1KB boundary. */

	/*
	 * Program the actual used UF buffers into the UF address table and
	 * the controller's array of UFs.
	 */
	for (i = 0; i < SCU_MAX_UNSOLICITED_FRAMES; i++) {
		uf = &uf_control->buffers.array[i];

		uf_control->address_table.array[i] = dma;

		uf->buffer = virt;
		uf->header = &uf_control->headers.array[i];
		uf->state  = UNSOLICITED_FRAME_EMPTY;

		/*
		 * Increment the address of the physical and virtual memory
		 * pointers. Everything is aligned on 1k boundary with an
		 * increment of 1k.
		 */
		virt += SCU_UNSOLICITED_FRAME_BUFFER_SIZE;
		dma += SCU_UNSOLICITED_FRAME_BUFFER_SIZE;
	}
}

enum sci_status sci_unsolicited_frame_control_get_header(struct sci_unsolicited_frame_control *uf_control,
							 u32 frame_index,
							 void **frame_header)
{
	if (frame_index < SCU_MAX_UNSOLICITED_FRAMES) {
		/* Skip the first word in the frame since this is a controll word used
		 * by the hardware.
		 */
		*frame_header = &uf_control->buffers.array[frame_index].header->data;

		return SCI_SUCCESS;
	}

	return SCI_FAILURE_INVALID_PARAMETER_VALUE;
}

enum sci_status sci_unsolicited_frame_control_get_buffer(struct sci_unsolicited_frame_control *uf_control,
							 u32 frame_index,
							 void **frame_buffer)
{
	if (frame_index < SCU_MAX_UNSOLICITED_FRAMES) {
		*frame_buffer = uf_control->buffers.array[frame_index].buffer;

		return SCI_SUCCESS;
	}

	return SCI_FAILURE_INVALID_PARAMETER_VALUE;
}

bool sci_unsolicited_frame_control_release_frame(struct sci_unsolicited_frame_control *uf_control,
						 u32 frame_index)
{
	u32 frame_get;
	u32 frame_cycle;

	frame_get   = uf_control->get & (SCU_MAX_UNSOLICITED_FRAMES - 1);
	frame_cycle = uf_control->get & SCU_MAX_UNSOLICITED_FRAMES;

	/*
	 * In the event there are NULL entries in the UF table, we need to
	 * advance the get pointer in order to find out if this frame should
	 * be released (i.e. update the get pointer)
	 */
	while (lower_32_bits(uf_control->address_table.array[frame_get]) == 0 &&
	       upper_32_bits(uf_control->address_table.array[frame_get]) == 0 &&
	       frame_get < SCU_MAX_UNSOLICITED_FRAMES)
		frame_get++;

	/*
	 * The table has a NULL entry as it's last element.  This is
	 * illegal.
	 */
	BUG_ON(frame_get >= SCU_MAX_UNSOLICITED_FRAMES);
	if (frame_index >= SCU_MAX_UNSOLICITED_FRAMES)
		return false;

	uf_control->buffers.array[frame_index].state = UNSOLICITED_FRAME_RELEASED;

	if (frame_get != frame_index) {
		/*
		 * Frames remain in use until we advance the get pointer
		 * so there is nothing we can do here
		 */
		return false;
	}

	/*
	 * The frame index is equal to the current get pointer so we
	 * can now free up all of the frame entries that
	 */
	while (uf_control->buffers.array[frame_get].state == UNSOLICITED_FRAME_RELEASED) {
		uf_control->buffers.array[frame_get].state = UNSOLICITED_FRAME_EMPTY;

		if (frame_get+1 == SCU_MAX_UNSOLICITED_FRAMES-1) {
			frame_cycle ^= SCU_MAX_UNSOLICITED_FRAMES;
			frame_get = 0;
		} else
			frame_get++;
	}

	uf_control->get = SCU_UFQGP_GEN_BIT(ENABLE_BIT) | frame_cycle | frame_get;

	return true;
}
