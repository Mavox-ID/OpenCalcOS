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
#include "pwrseq.h"

/*	Description:
 *		This routine deals with the Power Configuration CMD
 *		 parsing for RTL8723/RTL8188E Series IC.
 *	Assumption:
 *		We should follow specific format that was released from HW SD.
 */
bool rtl_hal_pwrseqcmdparsing(struct rtl_priv *rtlpriv, u8 cut_version,
			      u8 faversion, u8 interface_type,
			      struct wlan_pwr_cfg pwrcfgcmd[])
{
	struct wlan_pwr_cfg cfg_cmd = {0};
	bool polling_bit = false;
	u32 ary_idx = 0;
	u8 value = 0;
	u32 offset = 0;
	u32 polling_count = 0;
	u32 max_polling_cnt = 5000;

	do {
		cfg_cmd = pwrcfgcmd[ary_idx];
		RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
			"rtl_hal_pwrseqcmdparsing(): offset(%#x),cut_msk(%#x), famsk(%#x),"
			"interface_msk(%#x), base(%#x), cmd(%#x), msk(%#x), value(%#x)\n",
			GET_PWR_CFG_OFFSET(cfg_cmd),
					   GET_PWR_CFG_CUT_MASK(cfg_cmd),
			GET_PWR_CFG_FAB_MASK(cfg_cmd),
					     GET_PWR_CFG_INTF_MASK(cfg_cmd),
			GET_PWR_CFG_BASE(cfg_cmd), GET_PWR_CFG_CMD(cfg_cmd),
			GET_PWR_CFG_MASK(cfg_cmd), GET_PWR_CFG_VALUE(cfg_cmd));

		if ((GET_PWR_CFG_FAB_MASK(cfg_cmd)&faversion) &&
		    (GET_PWR_CFG_CUT_MASK(cfg_cmd)&cut_version) &&
		    (GET_PWR_CFG_INTF_MASK(cfg_cmd)&interface_type)) {
			switch (GET_PWR_CFG_CMD(cfg_cmd)) {
			case PWR_CMD_READ:
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					"rtl_hal_pwrseqcmdparsing(): PWR_CMD_READ\n");
				break;
			case PWR_CMD_WRITE:
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					"rtl_hal_pwrseqcmdparsing(): PWR_CMD_WRITE\n");
				offset = GET_PWR_CFG_OFFSET(cfg_cmd);

				/*Read the value from system register*/
				value = rtl_read_byte(rtlpriv, offset);
				value &= (~(GET_PWR_CFG_MASK(cfg_cmd)));
				value |= (GET_PWR_CFG_VALUE(cfg_cmd) &
					  GET_PWR_CFG_MASK(cfg_cmd));

				/*Write the value back to sytem register*/
				rtl_write_byte(rtlpriv, offset, value);
				break;
			case PWR_CMD_POLLING:
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					"rtl_hal_pwrseqcmdparsing(): PWR_CMD_POLLING\n");
				polling_bit = false;
				offset = GET_PWR_CFG_OFFSET(cfg_cmd);

				do {
					value = rtl_read_byte(rtlpriv, offset);

					value &= GET_PWR_CFG_MASK(cfg_cmd);
					if (value ==
					    (GET_PWR_CFG_VALUE(cfg_cmd)
					    & GET_PWR_CFG_MASK(cfg_cmd)))
						polling_bit = true;
					else
						udelay(10);

					if (polling_count++ > max_polling_cnt)
						return false;
				} while (!polling_bit);
				break;
			case PWR_CMD_DELAY:
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					"rtl_hal_pwrseqcmdparsing(): PWR_CMD_DELAY\n");
				if (GET_PWR_CFG_VALUE(cfg_cmd) ==
				    PWRSEQ_DELAY_US)
					udelay(GET_PWR_CFG_OFFSET(cfg_cmd));
				else
					mdelay(GET_PWR_CFG_OFFSET(cfg_cmd));
				break;
			case PWR_CMD_END:
				RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
					 "rtl_hal_pwrseqcmdparsing(): PWR_CMD_END\n");
				return true;
			default:
				RT_ASSERT(false,
					 "rtl_hal_pwrseqcmdparsing(): Unknown CMD!!\n");
				break;
			}

		}
		ary_idx++;
	} while (1);

	return true;
}
