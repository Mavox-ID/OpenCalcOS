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
#include <beep/init.h>
#include <beep/io.h>
#include <beep/spinlock.h>

#include <asm/dma.h>
#include <asm/scatterlist.h>

#include <asm/mach/dma.h>
#include <asm/hardware/dec21285.h>

#if 0
static int fb_dma_request(unsigned int chan, dma_t *dma)
{
	return -EINVAL;
}

static void fb_dma_enable(unsigned int chan, dma_t *dma)
{
}

static void fb_dma_disable(unsigned int chan, dma_t *dma)
{
}

static struct dma_ops fb_dma_ops = {
	.type		= "fb",
	.request	= fb_dma_request,
	.enable		= fb_dma_enable,
	.disable	= fb_dma_disable,
};
#endif

static int __init fb_dma_init(void)
{
#if 0
	dma[_DC21285_DMA(0)].d_ops = &fb_dma_ops;
	dma[_DC21285_DMA(1)].d_ops = &fb_dma_ops;
#endif
#ifdef CONFIG_ISA_DMA
	if (footbridge_cfn_mode())
		isa_init_dma();
#endif
	return 0;
}
core_initcall(fb_dma_init);
