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
#ifndef RMM_
#define RMM_

/*
 *  ======== rmm_addr ========
 *  DSP address + segid
 */
struct rmm_addr {
	u32 addr;
	s32 segid;
};

/*
 *  ======== rmm_segment ========
 *  Memory segment on the DSP available for remote allocations.
 */
struct rmm_segment {
	u32 base;		/* Base of the segment */
	u32 length;		/* Size of the segment (target MAUs) */
	s32 space;		/* Code or data */
	u32 number;		/* Number of Allocated Blocks */
};

/*
 *  ======== RMM_Target ========
 */
struct rmm_target_obj;

/*
 *  ======== rmm_alloc ========
 *
 *  rmm_alloc is used to remotely allocate or reserve memory on the DSP.
 *
 *  Parameters:
 *      target          - Target returned from rmm_create().
 *      segid           - Memory segment to allocate from.
 *      size            - Size (target MAUS) to allocate.
 *      align           - alignment.
 *      dsp_address     - If reserve is FALSE, the location to store allocated
 *                        address on output, otherwise, the DSP address to
 *                        reserve.
 *      reserve         - If TRUE, reserve the memory specified by dsp_address.
 *  Returns:
 *      0:                Success.
 *      -ENOMEM:            Memory allocation on GPP failed.
 *      -ENXIO:     Cannot "allocate" overlay memory because it's
 *                              already in use.
 *  Requires:
 *      RMM initialized.
 *      Valid target.
 *      dsp_address != NULL.
 *      size > 0
 *      reserve || target->num_segs > 0.
 *  Ensures:
 */
extern int rmm_alloc(struct rmm_target_obj *target, u32 segid, u32 size,
			u32 align, u32 *dsp_address, bool reserve);

/*
 *  ======== rmm_create ========
 *  Create a target object with memory segments for remote allocation. If
 *  seg_tab == NULL or num_segs == 0, memory can only be reserved through
 *  rmm_alloc().
 *
 *  Parameters:
 *      target_obj:        - Location to store target on output.
 *      seg_tab:         - Table of memory segments.
 *      num_segs:        - Number of memory segments.
 *  Returns:
 *      0:        Success.
 *      -ENOMEM:    Memory allocation failed.
 *  Requires:
 *      RMM initialized.
 *      target_obj != NULL.
 *      num_segs == 0 || seg_tab != NULL.
 *  Ensures:
 *      Success:        Valid *target_obj.
 *      Failure:        *target_obj == NULL.
 */
extern int rmm_create(struct rmm_target_obj **target_obj,
			     struct rmm_segment seg_tab[], u32 num_segs);

/*
 *  ======== rmm_delete ========
 *  Delete target allocated in rmm_create().
 *
 *  Parameters:
 *      target          - Target returned from rmm_create().
 *  Returns:
 *  Requires:
 *      RMM initialized.
 *      Valid target.
 *  Ensures:
 */
extern void rmm_delete(struct rmm_target_obj *target);

/*
 *  ======== rmm_free ========
 *  Free or unreserve memory allocated through rmm_alloc().
 *
 *  Parameters:
 *      target:         - Target returned from rmm_create().
 *      segid:          - Segment of memory to free.
 *      dsp_address:    - Address to free or unreserve.
 *      size:           - Size of memory to free or unreserve.
 *      reserved:       - TRUE if memory was reserved only, otherwise FALSE.
 *  Returns:
 *  Requires:
 *      RMM initialized.
 *      Valid target.
 *      reserved || segid < target->num_segs.
 *      reserve || [dsp_address, dsp_address + size] is a valid memory range.
 *  Ensures:
 */
extern bool rmm_free(struct rmm_target_obj *target, u32 segid, u32 dsp_addr,
		     u32 size, bool reserved);

/*
 *  ======== rmm_stat ========
 *  Obtain  memory segment status
 *
 *  Parameters:
 *      segid:       Segment ID of the dynamic loading segment.
 *      mem_stat_buf: Pointer to allocated buffer into which memory stats are
 *                   placed.
 *  Returns:
 *      TRUE:   Success.
 *      FALSE:  Failure.
 *  Requires:
 *      segid < target->num_segs
 *  Ensures:
 */
extern bool rmm_stat(struct rmm_target_obj *target, enum dsp_memtype segid,
		     struct dsp_memstat *mem_stat_buf);

#endif /* RMM_ */
