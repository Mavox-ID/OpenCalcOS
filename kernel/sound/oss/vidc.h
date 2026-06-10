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
/* vidc_fill.S */

/*
 * Filler routines for different channels and sample sizes
 */

extern unsigned long vidc_fill_1x8_u(unsigned long ibuf, unsigned long iend,
				     unsigned long obuf, int mask);
extern unsigned long vidc_fill_2x8_u(unsigned long ibuf, unsigned long iend,
				     unsigned long obuf, int mask);
extern unsigned long vidc_fill_1x8_s(unsigned long ibuf, unsigned long iend,
				     unsigned long obuf, int mask);
extern unsigned long vidc_fill_2x8_s(unsigned long ibuf, unsigned long iend,
				     unsigned long obuf, int mask);
extern unsigned long vidc_fill_1x16_s(unsigned long ibuf, unsigned long iend,
				      unsigned long obuf, int mask);
extern unsigned long vidc_fill_2x16_s(unsigned long ibuf, unsigned long iend,
				      unsigned long obuf, int mask);

/*
 * DMA Interrupt handler
 */

extern irqreturn_t vidc_sound_dma_irq(int irqnr, void *ref);

/*
 * Filler routine pointer
 */

extern unsigned long (*vidc_filler) (unsigned long ibuf, unsigned long iend,
				     unsigned long obuf, int mask);

/*
 * Virtual DMA buffer exhausted
 */

extern irqreturn_t (*dma_interrupt) (void);

/*
 * Virtual DMA buffer addresses
 */

extern unsigned long dma_start, dma_count, dma_bufsize;
extern unsigned long dma_buf[2], dma_pbuf[2];

/* vidc_synth.c */

extern void     vidc_synth_init(struct address_info *hw_config);
extern void	vidc_synth_exit(struct address_info *hw_config);
extern int      vidc_synth_get_volume(void);
extern int      vidc_synth_set_volume(int vol);
