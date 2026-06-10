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
#include <beep/serial.h>
#include <beep/module.h>
#include <beep/netdevice.h>
#include <beep/interrupt.h>
#include <beep/delay.h>
#include <beep/platform_device.h>
#include <beep/dma-mapping.h>
#include <beep/slab.h>

#include <net/irda/irda.h>
#include <net/irda/wrapper.h>
#include <net/irda/irda_device.h>

#include <asm/irq.h>
#include <asm/cacheflush.h>
#include <asm/dma.h>
#include <asm/portmux.h>
#undef DRIVER_NAME

#ifdef CONFIG_SIR_BFIN_DMA
struct dma_rx_buf {
	char *buf;
	int head;
	int tail;
};
#endif

struct bfin_sir_port {
	unsigned char __iomem   *membase;
	unsigned int            irq;
	unsigned int            lsr;
	unsigned long           clk;
	struct net_device       *dev;
#ifdef CONFIG_SIR_BFIN_DMA
	int                     tx_done;
	struct dma_rx_buf       rx_dma_buf;
	struct timer_list       rx_dma_timer;
	int                     rx_dma_nrows;
#endif
	unsigned int            tx_dma_channel;
	unsigned int            rx_dma_channel;
};

struct bfin_sir_port_res {
	unsigned long   base_addr;
	int             irq;
	unsigned int    rx_dma_channel;
	unsigned int    tx_dma_channel;
};

struct bfin_sir_self {
	struct bfin_sir_port    *sir_port;
	spinlock_t              lock;
	unsigned int            open;
	int                     speed;
	int                     newspeed;

	struct sk_buff          *txskb;
	struct sk_buff          *rxskb;
	struct net_device_stats stats;
	struct device           *dev;
	struct irlap_cb         *irlap;
	struct qos_info         qos;

	iobuff_t                tx_buff;
	iobuff_t                rx_buff;

	struct work_struct      work;
	int                     mtt;
};

#define DRIVER_NAME "bfin_sir"

#define port_membase(port)     (((struct bfin_sir_port *)(port))->membase)
#define get_lsr_cache(port)    (((struct bfin_sir_port *)(port))->lsr)
#define put_lsr_cache(port, v) (((struct bfin_sir_port *)(port))->lsr = (v))
#include <asm/bfin_serial.h>

static const unsigned short per[][4] = {
	/* rx pin      tx pin     NULL  uart_number */
	{P_UART0_RX, P_UART0_TX,    0,    0},
	{P_UART1_RX, P_UART1_TX,    0,    1},
	{P_UART2_RX, P_UART2_TX,    0,    2},
	{P_UART3_RX, P_UART3_TX,    0,    3},
};
