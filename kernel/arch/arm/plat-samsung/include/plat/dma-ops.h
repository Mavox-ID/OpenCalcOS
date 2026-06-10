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
#ifndef __SAMSUNG_DMA_OPS_H_
#define __SAMSUNG_DMA_OPS_H_ __FILE__

#include <beep/dmaengine.h>
#include <mach/dma.h>

struct samsung_dma_req {
	enum dma_transaction_type cap;
	struct property *dt_dmach_prop;
	struct s3c2410_dma_client *client;
};

struct samsung_dma_prep {
	enum dma_transaction_type cap;
	enum dma_transfer_direction direction;
	dma_addr_t buf;
	unsigned long period;
	unsigned long len;
	void (*fp)(void *data);
	void *fp_param;
};

struct samsung_dma_config {
	enum dma_transfer_direction direction;
	enum dma_slave_buswidth width;
	dma_addr_t fifo;
};

struct samsung_dma_ops {
	unsigned (*request)(enum dma_ch ch, struct samsung_dma_req *param);
	int (*release)(unsigned ch, void *param);
	int (*config)(unsigned ch, struct samsung_dma_config *param);
	int (*prepare)(unsigned ch, struct samsung_dma_prep *param);
	int (*trigger)(unsigned ch);
	int (*started)(unsigned ch);
	int (*flush)(unsigned ch);
	int (*stop)(unsigned ch);
};

extern void *samsung_dmadev_get_ops(void);
extern void *s3c_dma_get_ops(void);

static inline void *__samsung_dma_get_ops(void)
{
	if (samsung_dma_is_dmadev())
		return samsung_dmadev_get_ops();
	else
		return s3c_dma_get_ops();
}

/*
 * samsung_dma_get_ops
 * get the set of samsung dma operations
 */
#define samsung_dma_get_ops() __samsung_dma_get_ops()

#endif /* __SAMSUNG_DMA_OPS_H_ */
