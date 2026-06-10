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
#define SDIO_HEADER_LEN			4

/* SD block size can not bigger than 64 due to buf size limit in firmware */
/* define SD block size for data Tx/Rx */
#define SDIO_BLOCK_SIZE			64

/* Number of blocks for firmware transfer */
#define FIRMWARE_TRANSFER_NBLOCK	2

/* This is for firmware specific length */
#define FW_EXTRA_LEN			36

#define MRVDRV_SIZE_OF_CMD_BUFFER       (2 * 1024)

#define MRVDRV_BT_RX_PACKET_BUFFER_SIZE \
	(HCI_MAX_FRAME_SIZE + FW_EXTRA_LEN)

#define ALLOC_BUF_SIZE	(((max_t (int, MRVDRV_BT_RX_PACKET_BUFFER_SIZE, \
			MRVDRV_SIZE_OF_CMD_BUFFER) + SDIO_HEADER_LEN \
			+ SDIO_BLOCK_SIZE - 1) / SDIO_BLOCK_SIZE) \
			* SDIO_BLOCK_SIZE)

/* The number of times to try when polling for status */
#define MAX_POLL_TRIES			100

/* Max retry number of CMD53 write */
#define MAX_WRITE_IOMEM_RETRY		2

/* register bitmasks */
#define HOST_POWER_UP				BIT(1)
#define HOST_CMD53_FIN				BIT(2)

#define HIM_DISABLE				0xff
#define HIM_ENABLE				(BIT(0) | BIT(1))

#define UP_LD_HOST_INT_STATUS			BIT(0)
#define DN_LD_HOST_INT_STATUS			BIT(1)

#define DN_LD_CARD_RDY				BIT(0)
#define CARD_IO_READY				BIT(3)

#define FIRMWARE_READY				0xfedc


struct btmrvl_sdio_card_reg {
	u8 cfg;
	u8 host_int_mask;
	u8 host_intstatus;
	u8 card_status;
	u8 sq_read_base_addr_a0;
	u8 sq_read_base_addr_a1;
	u8 card_revision;
	u8 card_fw_status0;
	u8 card_fw_status1;
	u8 card_rx_len;
	u8 card_rx_unit;
	u8 io_port_0;
	u8 io_port_1;
	u8 io_port_2;
};

struct btmrvl_sdio_card {
	struct sdio_func *func;
	u32 ioport;
	const char *helper;
	const char *firmware;
	const struct btmrvl_sdio_card_reg *reg;
	u16 sd_blksz_fw_dl;
	u8 rx_unit;
	struct btmrvl_private *priv;
};

struct btmrvl_sdio_device {
	const char *helper;
	const char *firmware;
	const struct btmrvl_sdio_card_reg *reg;
	u16 sd_blksz_fw_dl;
};


/* Platform specific DMA alignment */
#define BTSDIO_DMA_ALIGN		8

/* Macros for Data Alignment : size */
#define ALIGN_SZ(p, a)	\
	(((p) + ((a) - 1)) & ~((a) - 1))

/* Macros for Data Alignment : address */
#define ALIGN_ADDR(p, a)	\
	((((unsigned long)(p)) + (((unsigned long)(a)) - 1)) & \
					~(((unsigned long)(a)) - 1))
