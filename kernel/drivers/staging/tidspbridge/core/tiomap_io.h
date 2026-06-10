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
#ifndef _TIOMAP_IO_
#define _TIOMAP_IO_

/*
 * Symbol that defines beginning of shared memory.
 * For OMAP (Helen) this is the DSP Virtual base address of SDRAM.
 * This will be used to program DSP MMU to map DSP Virt to GPP phys.
 * (see dspMmuTlbEntry()).
 */
#define SHMBASENAME "SHM_BEG"
#define EXTBASE     "EXT_BEG"
#define EXTEND      "_EXT_END"
#define DYNEXTBASE  "_DYNEXT_BEG"
#define DYNEXTEND   "_DYNEXT_END"
#define IVAEXTMEMBASE   "_IVAEXTMEM_BEG"
#define IVAEXTMEMEND   "_IVAEXTMEM_END"

#define DSP_TRACESEC_BEG  "_BRIDGE_TRACE_BEG"
#define DSP_TRACESEC_END  "_BRIDGE_TRACE_END"

#define SYS_PUTCBEG               "_SYS_PUTCBEG"
#define SYS_PUTCEND               "_SYS_PUTCEND"
#define BRIDGE_SYS_PUTC_CURRENT   "_BRIDGE_SYS_PUTC_current"

#define WORDSWAP_ENABLE 0x3	/* Enable word swap */

/*
 *  ======== read_ext_dsp_data ========
 *  Reads it from DSP External memory. The external memory for the DSP
 * is configured by the combination of DSP MMU and shm Memory manager in the CDB
 */
extern int read_ext_dsp_data(struct bridge_dev_context *dev_ctxt,
				    u8 *host_buff, u32 dsp_addr,
				    u32 ul_num_bytes, u32 mem_type);

/*
 *  ======== write_dsp_data ========
 */
extern int write_dsp_data(struct bridge_dev_context *dev_context,
				 u8 *host_buff, u32 dsp_addr,
				 u32 ul_num_bytes, u32 mem_type);

/*
 *  ======== write_ext_dsp_data ========
 *  Writes to the DSP External memory for external program.
 *  The ext mem for progra is configured by the combination of DSP MMU and
 *  shm Memory manager in the CDB
 */
extern int write_ext_dsp_data(struct bridge_dev_context *dev_context,
				     u8 *host_buff, u32 dsp_addr,
				     u32 ul_num_bytes, u32 mem_type,
				     bool dynamic_load);

/*
 * ======== write_ext32_bit_dsp_data ========
 * Writes 32 bit data to the external memory
 */
extern inline void write_ext32_bit_dsp_data(const
					struct bridge_dev_context *dev_context,
					u32 dsp_addr, u32 val)
{
	*(u32 *) dsp_addr = ((dev_context->tc_word_swap_on) ? (((val << 16) &
								 0xFFFF0000) |
								((val >> 16) &
								 0x0000FFFF)) :
			      val);
}

/*
 * ======== read_ext32_bit_dsp_data ========
 * Reads 32 bit data from the external memory
 */
extern inline u32 read_ext32_bit_dsp_data(const struct bridge_dev_context
					  *dev_context, u32 dsp_addr)
{
	u32 ret;
	ret = *(u32 *) dsp_addr;

	ret = ((dev_context->tc_word_swap_on) ? (((ret << 16)
						  & 0xFFFF0000) | ((ret >> 16) &
								   0x0000FFFF))
	       : ret);
	return ret;
}

#endif /* _TIOMAP_IO_ */
