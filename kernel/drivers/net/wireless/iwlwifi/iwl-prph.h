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
#ifndef	__iwl_prph_h__
#define __iwl_prph_h__

/*
 * Registers in this file are internal, not PCI bus memory mapped.
 * Driver accesses these via HBUS_TARG_PRPH_* registers.
 */
#define PRPH_BASE	(0x00000)
#define PRPH_END	(0xFFFFF)

/* APMG (power management) constants */
#define APMG_BASE			(PRPH_BASE + 0x3000)
#define APMG_CLK_CTRL_REG		(APMG_BASE + 0x0000)
#define APMG_CLK_EN_REG			(APMG_BASE + 0x0004)
#define APMG_CLK_DIS_REG		(APMG_BASE + 0x0008)
#define APMG_PS_CTRL_REG		(APMG_BASE + 0x000c)
#define APMG_PCIDEV_STT_REG		(APMG_BASE + 0x0010)
#define APMG_RFKILL_REG			(APMG_BASE + 0x0014)
#define APMG_RTC_INT_STT_REG		(APMG_BASE + 0x001c)
#define APMG_RTC_INT_MSK_REG		(APMG_BASE + 0x0020)
#define APMG_DIGITAL_SVR_REG		(APMG_BASE + 0x0058)
#define APMG_ANALOG_SVR_REG		(APMG_BASE + 0x006C)

#define APMS_CLK_VAL_MRB_FUNC_MODE	(0x00000001)
#define APMG_CLK_VAL_DMA_CLK_RQT	(0x00000200)
#define APMG_CLK_VAL_BSM_CLK_RQT	(0x00000800)

#define APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS	(0x00400000)
#define APMG_PS_CTRL_VAL_RESET_REQ		(0x04000000)
#define APMG_PS_CTRL_MSK_PWR_SRC		(0x03000000)
#define APMG_PS_CTRL_VAL_PWR_SRC_VMAIN		(0x00000000)
#define APMG_PS_CTRL_VAL_PWR_SRC_VAUX		(0x02000000)
#define APMG_SVR_VOLTAGE_CONFIG_BIT_MSK	(0x000001E0) /* bit 8:5 */
#define APMG_SVR_DIGITAL_VOLTAGE_1_32		(0x00000060)

#define APMG_PCIDEV_STT_VAL_L1_ACT_DIS		(0x00000800)

/**
 * Tx Scheduler
 *
 * The Tx Scheduler selects the next frame to be transmitted, choosing TFDs
 * (Transmit Frame Descriptors) from up to 16 circular Tx queues resident in
 * host DRAM.  It steers each frame's Tx command (which contains the frame
 * data) into one of up to 7 prioritized Tx DMA FIFO channels within the
 * device.  A queue maps to only one (selectable by driver) Tx DMA channel,
 * but one DMA channel may take input from several queues.
 *
 * Tx DMA FIFOs have dedicated purposes.
 *
 * For 5000 series and up, they are used differently
 * (cf. iwl5000_default_queue_to_tx_fifo in iwl-5000.c):
 *
 * 0 -- EDCA BK (background) frames, lowest priority
 * 1 -- EDCA BE (best effort) frames, normal priority
 * 2 -- EDCA VI (video) frames, higher priority
 * 3 -- EDCA VO (voice) and management frames, highest priority
 * 4 -- unused
 * 5 -- unused
 * 6 -- unused
 * 7 -- Commands
 *
 * Driver should normally map queues 0-6 to Tx DMA/FIFO channels 0-6.
 * In addition, driver can map the remaining queues to Tx DMA/FIFO
 * channels 0-3 to support 11n aggregation via EDCA DMA channels.
 *
 * The driver sets up each queue to work in one of two modes:
 *
 * 1)  Scheduler-Ack, in which the scheduler automatically supports a
 *     block-ack (BA) window of up to 64 TFDs.  In this mode, each queue
 *     contains TFDs for a unique combination of Recipient Address (RA)
 *     and Traffic Identifier (TID), that is, traffic of a given
 *     Quality-Of-Service (QOS) priority, destined for a single station.
 *
 *     In scheduler-ack mode, the scheduler keeps track of the Tx status of
 *     each frame within the BA window, including whether it's been transmitted,
 *     and whether it's been acknowledged by the receiving station.  The device
 *     automatically processes block-acks received from the receiving STA,
 *     and reschedules un-acked frames to be retransmitted (successful
 *     Tx completion may end up being out-of-order).
 *
 *     The driver must maintain the queue's Byte Count table in host DRAM
 *     for this mode.
 *     This mode does not support fragmentation.
 *
 * 2)  FIFO (a.k.a. non-Scheduler-ACK), in which each TFD is processed in order.
 *     The device may automatically retry Tx, but will retry only one frame
 *     at a time, until receiving ACK from receiving station, or reaching
 *     retry limit and giving up.
 *
 *     The command queue (#4/#9) must use this mode!
 *     This mode does not require use of the Byte Count table in host DRAM.
 *
 * Driver controls scheduler operation via 3 means:
 * 1)  Scheduler registers
 * 2)  Shared scheduler data base in internal SRAM
 * 3)  Shared data in host DRAM
 *
 * Initialization:
 *
 * When loading, driver should allocate memory for:
 * 1)  16 TFD circular buffers, each with space for (typically) 256 TFDs.
 * 2)  16 Byte Count circular buffers in 16 KBytes contiguous memory
 *     (1024 bytes for each queue).
 *
 * After receiving "Alive" response from uCode, driver must initialize
 * the scheduler (especially for queue #4/#9, the command queue, otherwise
 * the driver can't issue commands!):
 */
#define SCD_MEM_LOWER_BOUND		(0x0000)

/**
 * Max Tx window size is the max number of contiguous TFDs that the scheduler
 * can keep track of at one time when creating block-ack chains of frames.
 * Note that "64" matches the number of ack bits in a block-ack packet.
 */
#define SCD_WIN_SIZE				64
#define SCD_FRAME_LIMIT				64

#define SCD_TXFIFO_POS_TID			(0)
#define SCD_TXFIFO_POS_RA			(4)
#define SCD_QUEUE_RA_TID_MAP_RATID_MSK	(0x01FF)

/* agn SCD */
#define SCD_QUEUE_STTS_REG_POS_TXF	(0)
#define SCD_QUEUE_STTS_REG_POS_ACTIVE	(3)
#define SCD_QUEUE_STTS_REG_POS_WSL	(4)
#define SCD_QUEUE_STTS_REG_POS_SCD_ACT_EN (19)
#define SCD_QUEUE_STTS_REG_MSK		(0x017F0000)

#define SCD_QUEUE_CTX_REG1_CREDIT_POS		(8)
#define SCD_QUEUE_CTX_REG1_CREDIT_MSK		(0x00FFFF00)
#define SCD_QUEUE_CTX_REG1_SUPER_CREDIT_POS	(24)
#define SCD_QUEUE_CTX_REG1_SUPER_CREDIT_MSK	(0xFF000000)
#define SCD_QUEUE_CTX_REG2_WIN_SIZE_POS		(0)
#define SCD_QUEUE_CTX_REG2_WIN_SIZE_MSK		(0x0000007F)
#define SCD_QUEUE_CTX_REG2_FRAME_LIMIT_POS	(16)
#define SCD_QUEUE_CTX_REG2_FRAME_LIMIT_MSK	(0x007F0000)

/* Context Data */
#define SCD_CONTEXT_MEM_LOWER_BOUND	(SCD_MEM_LOWER_BOUND + 0x600)
#define SCD_CONTEXT_MEM_UPPER_BOUND	(SCD_MEM_LOWER_BOUND + 0x6A0)

/* Tx status */
#define SCD_TX_STTS_MEM_LOWER_BOUND	(SCD_MEM_LOWER_BOUND + 0x6A0)
#define SCD_TX_STTS_MEM_UPPER_BOUND	(SCD_MEM_LOWER_BOUND + 0x7E0)

/* Translation Data */
#define SCD_TRANS_TBL_MEM_LOWER_BOUND	(SCD_MEM_LOWER_BOUND + 0x7E0)
#define SCD_TRANS_TBL_MEM_UPPER_BOUND	(SCD_MEM_LOWER_BOUND + 0x808)

#define SCD_CONTEXT_QUEUE_OFFSET(x)\
	(SCD_CONTEXT_MEM_LOWER_BOUND + ((x) * 8))

#define SCD_TX_STTS_QUEUE_OFFSET(x)\
	(SCD_TX_STTS_MEM_LOWER_BOUND + ((x) * 16))

#define SCD_TRANS_TBL_OFFSET_QUEUE(x) \
	((SCD_TRANS_TBL_MEM_LOWER_BOUND + ((x) * 2)) & 0xfffc)

#define SCD_BASE			(PRPH_BASE + 0xa02c00)

#define SCD_SRAM_BASE_ADDR	(SCD_BASE + 0x0)
#define SCD_DRAM_BASE_ADDR	(SCD_BASE + 0x8)
#define SCD_AIT			(SCD_BASE + 0x0c)
#define SCD_TXFACT		(SCD_BASE + 0x10)
#define SCD_ACTIVE		(SCD_BASE + 0x14)
#define SCD_QUEUECHAIN_SEL	(SCD_BASE + 0xe8)
#define SCD_CHAINEXT_EN		(SCD_BASE + 0x244)
#define SCD_AGGR_SEL		(SCD_BASE + 0x248)
#define SCD_INTERRUPT_MASK	(SCD_BASE + 0x108)

static inline unsigned int SCD_QUEUE_WRPTR(unsigned int chnl)
{
	if (chnl < 20)
		return SCD_BASE + 0x18 + chnl * 4;
	WARN_ON_ONCE(chnl >= 32);
	return SCD_BASE + 0x284 + (chnl - 20) * 4;
}

static inline unsigned int SCD_QUEUE_RDPTR(unsigned int chnl)
{
	if (chnl < 20)
		return SCD_BASE + 0x68 + chnl * 4;
	WARN_ON_ONCE(chnl >= 32);
	return SCD_BASE + 0x2B4 + (chnl - 20) * 4;
}

static inline unsigned int SCD_QUEUE_STATUS_BITS(unsigned int chnl)
{
	if (chnl < 20)
		return SCD_BASE + 0x10c + chnl * 4;
	WARN_ON_ONCE(chnl >= 32);
	return SCD_BASE + 0x384 + (chnl - 20) * 4;
}

/*********************** END TX SCHEDULER *************************************/

#endif				/* __iwl_prph_h__ */
