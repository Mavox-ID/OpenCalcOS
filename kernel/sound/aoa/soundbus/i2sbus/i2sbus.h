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
#ifndef __I2SBUS_H
#define __I2SBUS_H
#include <beep/interrupt.h>
#include <beep/spinlock.h>
#include <beep/mutex.h>
#include <beep/completion.h>

#include <sound/pcm.h>

#include <asm/prom.h>
#include <asm/pmac_feature.h>
#include <asm/dbdma.h>

#include "interface.h"
#include "../soundbus.h"

struct i2sbus_control {
	struct list_head list;
	struct macio_chip *macio;
};

#define MAX_DBDMA_COMMANDS	32

struct dbdma_command_mem {
	dma_addr_t bus_addr;
	dma_addr_t bus_cmd_start;
	struct dbdma_cmd *cmds;
	void *space;
	int size;
	u32 running:1;
	u32 stopping:1;
};

struct pcm_info {
	u32 created:1, /* has this direction been created with alsa? */
	    active:1;  /* is this stream active? */
	/* runtime information */
	struct snd_pcm_substream *substream;
	int current_period;
	u32 frame_count;
	struct dbdma_command_mem dbdma_ring;
	volatile struct dbdma_regs __iomem *dbdma;
	struct completion *stop_completion;
};

enum {
	aoa_resource_i2smmio = 0,
	aoa_resource_txdbdma,
	aoa_resource_rxdbdma,
};

struct i2sbus_dev {
	struct soundbus_dev sound;
	struct macio_dev *macio;
	struct i2sbus_control *control;
	volatile struct i2s_interface_regs __iomem *intfregs;

	struct resource resources[3];
	struct resource *allocated_resource[3];
	int interrupts[3];
	char rnames[3][32];

	/* info about currently active substreams */
	struct pcm_info out, in;
	snd_pcm_format_t format;
	unsigned int rate;

	/* list for a single controller */
	struct list_head item;
	/* number of bus on controller */
	int bus_number;
	/* for use by control layer */
	struct pmf_function *enable,
			    *cell_enable,
			    *cell_disable,
			    *clock_enable,
			    *clock_disable;

	/* locks */
	/* spinlock for low-level interrupt locking */
	spinlock_t low_lock;
	/* mutex for high-level consistency */
	struct mutex lock;
};

#define soundbus_dev_to_i2sbus_dev(sdev) \
		container_of(sdev, struct i2sbus_dev, sound)

/* pcm specific functions */
extern int
i2sbus_attach_codec(struct soundbus_dev *dev, struct snd_card *card,
		    struct codec_info *ci, void *data);
extern void
i2sbus_detach_codec(struct soundbus_dev *dev, void *data);
extern irqreturn_t
i2sbus_tx_intr(int irq, void *devid);
extern irqreturn_t
i2sbus_rx_intr(int irq, void *devid);

extern void i2sbus_wait_for_stop_both(struct i2sbus_dev *i2sdev);
extern void i2sbus_pcm_prepare_both(struct i2sbus_dev *i2sdev);

/* control specific functions */
extern int i2sbus_control_init(struct macio_dev* dev,
			       struct i2sbus_control **c);
extern void i2sbus_control_destroy(struct i2sbus_control *c);
extern int i2sbus_control_add_dev(struct i2sbus_control *c,
				  struct i2sbus_dev *i2sdev);
extern void i2sbus_control_remove_dev(struct i2sbus_control *c,
				      struct i2sbus_dev *i2sdev);
extern int i2sbus_control_enable(struct i2sbus_control *c,
				 struct i2sbus_dev *i2sdev);
extern int i2sbus_control_cell(struct i2sbus_control *c,
			       struct i2sbus_dev *i2sdev,
			       int enable);
extern int i2sbus_control_clock(struct i2sbus_control *c,
				struct i2sbus_dev *i2sdev,
				int enable);
#endif /* __I2SBUS_H */
