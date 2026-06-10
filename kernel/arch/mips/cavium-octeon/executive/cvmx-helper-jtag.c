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
/**
 *
 * Helper utilities for qlm_jtag.
 *
 */

#include <asm/octeon/octeon.h>
#include <asm/octeon/cvmx-helper-jtag.h>


/**
 * Initialize the internal QLM JTAG logic to allow programming
 * of the JTAG chain by the cvmx_helper_qlm_jtag_*() functions.
 * These functions should only be used at the direction of Cavium
 * Networks. Programming incorrect values into the JTAG chain
 * can cause chip damage.
 */
void cvmx_helper_qlm_jtag_init(void)
{
	union cvmx_ciu_qlm_jtgc jtgc;
	uint32_t clock_div = 0;
	uint32_t divisor = cvmx_sysinfo_get()->cpu_clock_hz / (25 * 1000000);
	divisor = (divisor - 1) >> 2;
	/* Convert the divisor into a power of 2 shift */
	while (divisor) {
		clock_div++;
		divisor = divisor >> 1;
	}

	/*
	 * Clock divider for QLM JTAG operations.  eclk is divided by
	 * 2^(CLK_DIV + 2)
	 */
	jtgc.u64 = 0;
	jtgc.s.clk_div = clock_div;
	jtgc.s.mux_sel = 0;
	if (OCTEON_IS_MODEL(OCTEON_CN52XX))
		jtgc.s.bypass = 0x3;
	else
		jtgc.s.bypass = 0xf;
	cvmx_write_csr(CVMX_CIU_QLM_JTGC, jtgc.u64);
	cvmx_read_csr(CVMX_CIU_QLM_JTGC);
}

/**
 * Write up to 32bits into the QLM jtag chain. Bits are shifted
 * into the MSB and out the LSB, so you should shift in the low
 * order bits followed by the high order bits. The JTAG chain is
 * 4 * 268 bits long, or 1072.
 *
 * @qlm:    QLM to shift value into
 * @bits:   Number of bits to shift in (1-32).
 * @data:   Data to shift in. Bit 0 enters the chain first, followed by
 *               bit 1, etc.
 *
 * Returns The low order bits of the JTAG chain that shifted out of the
 *         circle.
 */
uint32_t cvmx_helper_qlm_jtag_shift(int qlm, int bits, uint32_t data)
{
	union cvmx_ciu_qlm_jtgd jtgd;
	jtgd.u64 = 0;
	jtgd.s.shift = 1;
	jtgd.s.shft_cnt = bits - 1;
	jtgd.s.shft_reg = data;
	if (!OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X))
		jtgd.s.select = 1 << qlm;
	cvmx_write_csr(CVMX_CIU_QLM_JTGD, jtgd.u64);
	do {
		jtgd.u64 = cvmx_read_csr(CVMX_CIU_QLM_JTGD);
	} while (jtgd.s.shift);
	return jtgd.s.shft_reg >> (32 - bits);
}

/**
 * Shift long sequences of zeros into the QLM JTAG chain. It is
 * common to need to shift more than 32 bits of zeros into the
 * chain. This function is a convience wrapper around
 * cvmx_helper_qlm_jtag_shift() to shift more than 32 bits of
 * zeros at a time.
 *
 * @qlm:    QLM to shift zeros into
 * @bits:
 */
void cvmx_helper_qlm_jtag_shift_zeros(int qlm, int bits)
{
	while (bits > 0) {
		int n = bits;
		if (n > 32)
			n = 32;
		cvmx_helper_qlm_jtag_shift(qlm, n, 0);
		bits -= n;
	}
}

/**
 * Program the QLM JTAG chain into all lanes of the QLM. You must
 * have already shifted in 268*4, or 1072 bits into the JTAG
 * chain. Updating invalid values can possibly cause chip damage.
 *
 * @qlm:    QLM to program
 */
void cvmx_helper_qlm_jtag_update(int qlm)
{
	union cvmx_ciu_qlm_jtgd jtgd;

	/* Update the new data */
	jtgd.u64 = 0;
	jtgd.s.update = 1;
	if (!OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X))
		jtgd.s.select = 1 << qlm;
	cvmx_write_csr(CVMX_CIU_QLM_JTGD, jtgd.u64);
	do {
		jtgd.u64 = cvmx_read_csr(CVMX_CIU_QLM_JTGD);
	} while (jtgd.s.update);
}
