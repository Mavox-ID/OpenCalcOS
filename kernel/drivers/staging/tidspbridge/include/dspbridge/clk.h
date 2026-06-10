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
#ifndef _CLK_H
#define _CLK_H

enum dsp_clk_id {
	DSP_CLK_IVA2 = 0,
	DSP_CLK_GPT5,
	DSP_CLK_GPT6,
	DSP_CLK_GPT7,
	DSP_CLK_GPT8,
	DSP_CLK_WDT3,
	DSP_CLK_MCBSP1,
	DSP_CLK_MCBSP2,
	DSP_CLK_MCBSP3,
	DSP_CLK_MCBSP4,
	DSP_CLK_MCBSP5,
	DSP_CLK_SSI,
	DSP_CLK_NOT_DEFINED
};

/*
 *  ======== dsp_clk_exit ========
 *  Purpose:
 *      Discontinue usage of module; free resources when reference count
 *      reaches 0.
 *  Parameters:
 *  Returns:
 *  Requires:
 *      CLK initialized.
 *  Ensures:
 *      Resources used by module are freed when cRef reaches zero.
 */
extern void dsp_clk_exit(void);

/*
 *  ======== dsp_clk_init ========
 *  Purpose:
 *      Initializes private state of CLK module.
 *  Parameters:
 *  Returns:
 *      TRUE if initialized; FALSE if error occurred.
 *  Requires:
 *  Ensures:
 *      CLK initialized.
 */
extern void dsp_clk_init(void);

void dsp_gpt_wait_overflow(short int clk_id, unsigned int load);

/*
 *  ======== dsp_clk_enable ========
 *  Purpose:
 *      Enables the clock requested.
 *  Parameters:
 *  Returns:
 *      0:	Success.
 *	-EPERM:	Error occurred while enabling the clock.
 *  Requires:
 *  Ensures:
 */
extern int dsp_clk_enable(enum dsp_clk_id clk_id);

u32 dsp_clock_enable_all(u32 dsp_per_clocks);

/*
 *  ======== dsp_clk_disable ========
 *  Purpose:
 *      Disables the clock requested.
 *  Parameters:
 *  Returns:
 *      0:        Success.
 *      -EPERM:      Error occurred while disabling the clock.
 *  Requires:
 *  Ensures:
 */
extern int dsp_clk_disable(enum dsp_clk_id clk_id);

extern u32 dsp_clk_get_iva2_rate(void);

u32 dsp_clock_disable_all(u32 dsp_per_clocks);

extern void ssi_clk_prepare(bool FLAG);

#endif /* _SYNC_H */
