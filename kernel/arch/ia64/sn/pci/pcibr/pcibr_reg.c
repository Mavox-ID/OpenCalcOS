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
#include <beep/interrupt.h>
#include <beep/types.h>
#include <asm/sn/io.h>
#include <asm/sn/pcibr_provider.h>
#include <asm/sn/pcibus_provider_defs.h>
#include <asm/sn/pcidev.h>
#include <asm/sn/pic.h>
#include <asm/sn/tiocp.h>

union br_ptr {
	struct tiocp tio;
	struct pic pic;
};

/*
 * Control Register Access -- Read/Write                            0000_0020
 */
void pcireg_control_bit_clr(struct pcibus_info *pcibus_info, u64 bits)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			__sn_clrq_relaxed(&ptr->tio.cp_control, bits);
			break;
		case PCIBR_BRIDGETYPE_PIC:
			__sn_clrq_relaxed(&ptr->pic.p_wid_control, bits);
			break;
		default:
			panic
			    ("pcireg_control_bit_clr: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}
}

void pcireg_control_bit_set(struct pcibus_info *pcibus_info, u64 bits)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			__sn_setq_relaxed(&ptr->tio.cp_control, bits);
			break;
		case PCIBR_BRIDGETYPE_PIC:
			__sn_setq_relaxed(&ptr->pic.p_wid_control, bits);
			break;
		default:
			panic
			    ("pcireg_control_bit_set: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}
}

/*
 * PCI/PCIX Target Flush Register Access -- Read Only		    0000_0050
 */
u64 pcireg_tflush_get(struct pcibus_info *pcibus_info)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;
	u64 ret = 0;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			ret = __sn_readq_relaxed(&ptr->tio.cp_tflush);
			break;
		case PCIBR_BRIDGETYPE_PIC:
			ret = __sn_readq_relaxed(&ptr->pic.p_wid_tflush);
			break;
		default:
			panic
			    ("pcireg_tflush_get: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}

	/* Read of the Target Flush should always return zero */
	if (ret != 0)
		panic("pcireg_tflush_get:Target Flush failed\n");

	return ret;
}

/*
 * Interrupt Status Register Access -- Read Only		    0000_0100
 */
u64 pcireg_intr_status_get(struct pcibus_info * pcibus_info)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;
	u64 ret = 0;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			ret = __sn_readq_relaxed(&ptr->tio.cp_int_status);
			break;
		case PCIBR_BRIDGETYPE_PIC:
			ret = __sn_readq_relaxed(&ptr->pic.p_int_status);
			break;
		default:
			panic
			    ("pcireg_intr_status_get: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}
	return ret;
}

/*
 * Interrupt Enable Register Access -- Read/Write                   0000_0108
 */
void pcireg_intr_enable_bit_clr(struct pcibus_info *pcibus_info, u64 bits)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			__sn_clrq_relaxed(&ptr->tio.cp_int_enable, bits);
			break;
		case PCIBR_BRIDGETYPE_PIC:
			__sn_clrq_relaxed(&ptr->pic.p_int_enable, bits);
			break;
		default:
			panic
			    ("pcireg_intr_enable_bit_clr: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}
}

void pcireg_intr_enable_bit_set(struct pcibus_info *pcibus_info, u64 bits)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			__sn_setq_relaxed(&ptr->tio.cp_int_enable, bits);
			break;
		case PCIBR_BRIDGETYPE_PIC:
			__sn_setq_relaxed(&ptr->pic.p_int_enable, bits);
			break;
		default:
			panic
			    ("pcireg_intr_enable_bit_set: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}
}

/*
 * Intr Host Address Register (int_addr) -- Read/Write  0000_0130 - 0000_0168
 */
void pcireg_intr_addr_addr_set(struct pcibus_info *pcibus_info, int int_n,
			       u64 addr)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			__sn_clrq_relaxed(&ptr->tio.cp_int_addr[int_n],
			    TIOCP_HOST_INTR_ADDR);
			__sn_setq_relaxed(&ptr->tio.cp_int_addr[int_n],
			    (addr & TIOCP_HOST_INTR_ADDR));
			break;
		case PCIBR_BRIDGETYPE_PIC:
			__sn_clrq_relaxed(&ptr->pic.p_int_addr[int_n],
			    PIC_HOST_INTR_ADDR);
			__sn_setq_relaxed(&ptr->pic.p_int_addr[int_n],
			    (addr & PIC_HOST_INTR_ADDR));
			break;
		default:
			panic
			    ("pcireg_intr_addr_addr_get: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}
}

/*
 * Force Interrupt Register Access -- Write Only	0000_01C0 - 0000_01F8
 */
void pcireg_force_intr_set(struct pcibus_info *pcibus_info, int int_n)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			writeq(1, &ptr->tio.cp_force_pin[int_n]);
			break;
		case PCIBR_BRIDGETYPE_PIC:
			writeq(1, &ptr->pic.p_force_pin[int_n]);
			break;
		default:
			panic
			    ("pcireg_force_intr_set: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}
}

/*
 * Device(x) Write Buffer Flush Reg Access -- Read Only 0000_0240 - 0000_0258
 */
u64 pcireg_wrb_flush_get(struct pcibus_info *pcibus_info, int device)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;
	u64 ret = 0;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			ret =
			    __sn_readq_relaxed(&ptr->tio.cp_wr_req_buf[device]);
			break;
		case PCIBR_BRIDGETYPE_PIC:
			ret =
			    __sn_readq_relaxed(&ptr->pic.p_wr_req_buf[device]);
			break;
		default:
		      panic("pcireg_wrb_flush_get: unknown bridgetype bridge 0x%p", ptr);
		}

	}
	/* Read of the Write Buffer Flush should always return zero */
	return ret;
}

void pcireg_int_ate_set(struct pcibus_info *pcibus_info, int ate_index,
			u64 val)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			writeq(val, &ptr->tio.cp_int_ate_ram[ate_index]);
			break;
		case PCIBR_BRIDGETYPE_PIC:
			writeq(val, &ptr->pic.p_int_ate_ram[ate_index]);
			break;
		default:
			panic
			    ("pcireg_int_ate_set: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}
}

u64 __iomem *pcireg_int_ate_addr(struct pcibus_info *pcibus_info, int ate_index)
{
	union br_ptr __iomem *ptr = (union br_ptr __iomem *)pcibus_info->pbi_buscommon.bs_base;
	u64 __iomem *ret = NULL;

	if (pcibus_info) {
		switch (pcibus_info->pbi_bridge_type) {
		case PCIBR_BRIDGETYPE_TIOCP:
			ret = &ptr->tio.cp_int_ate_ram[ate_index];
			break;
		case PCIBR_BRIDGETYPE_PIC:
			ret = &ptr->pic.p_int_ate_ram[ate_index];
			break;
		default:
			panic
			    ("pcireg_int_ate_addr: unknown bridgetype bridge 0x%p",
			     ptr);
		}
	}
	return ret;
}
