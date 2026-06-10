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
void cm_control(u32, u32);

#define CM_CTRL	__io_address(INTEGRATOR_HDR_CTRL)

#define CM_CTRL_LED			(1 << 0)
#define CM_CTRL_nMBDET			(1 << 1)
#define CM_CTRL_REMAP			(1 << 2)
#define CM_CTRL_RESET			(1 << 3)

/*
 * Integrator/AP,PP2 specific
 */
#define CM_CTRL_HIGHVECTORS		(1 << 4)
#define CM_CTRL_BIGENDIAN		(1 << 5)
#define CM_CTRL_FASTBUS			(1 << 6)
#define CM_CTRL_SYNC			(1 << 7)

/*
 * ARM926/946/966 Integrator/CP specific
 */
#define CM_CTRL_LCDBIASEN		(1 << 8)
#define CM_CTRL_LCDBIASUP		(1 << 9)
#define CM_CTRL_LCDBIASDN		(1 << 10)
#define CM_CTRL_LCDMUXSEL_MASK		(7 << 11)
#define CM_CTRL_LCDMUXSEL_GENLCD	(1 << 11)
#define CM_CTRL_LCDMUXSEL_VGA565_TFT555	(2 << 11)
#define CM_CTRL_LCDMUXSEL_SHARPLCD	(3 << 11)
#define CM_CTRL_LCDMUXSEL_VGA555_TFT555	(4 << 11)
#define CM_CTRL_LCDEN0			(1 << 14)
#define CM_CTRL_LCDEN1			(1 << 15)
#define CM_CTRL_STATIC1			(1 << 16)
#define CM_CTRL_STATIC2			(1 << 17)
#define CM_CTRL_STATIC			(1 << 18)
#define CM_CTRL_n24BITEN		(1 << 19)
#define CM_CTRL_EBIWP			(1 << 20)
