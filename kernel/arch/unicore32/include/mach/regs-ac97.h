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
#define PKUNITY_AC97_CONR		(PKUNITY_AC97_BASE + 0x0000)
#define PKUNITY_AC97_OCR		(PKUNITY_AC97_BASE + 0x0004)
#define PKUNITY_AC97_ICR		(PKUNITY_AC97_BASE + 0x0008)
#define PKUNITY_AC97_CRAC		(PKUNITY_AC97_BASE + 0x000C)
#define PKUNITY_AC97_INTR		(PKUNITY_AC97_BASE + 0x0010)
#define PKUNITY_AC97_INTRSTAT		(PKUNITY_AC97_BASE + 0x0014)
#define PKUNITY_AC97_INTRCLEAR		(PKUNITY_AC97_BASE + 0x0018)
#define PKUNITY_AC97_ENABLE		(PKUNITY_AC97_BASE + 0x001C)
#define PKUNITY_AC97_OUT_FIFO		(PKUNITY_AC97_BASE + 0x0020)
#define PKUNITY_AC97_IN_FIFO		(PKUNITY_AC97_BASE + 0x0030)

#define AC97_CODEC_REG(v)               FIELD((v), 7, 16)
#define AC97_CODEC_VAL(v)               FIELD((v), 16, 0)
#define AC97_CODEC_WRITECOMPLETE        FIELD(1, 1, 2)

/*
 * VAR PLAY SAMPLE RATE
 */
#define AC97_CMD_VPSAMPLE		(FIELD(3, 2, 16) | FIELD(3, 2, 0))

/*
 * FIX CAPTURE SAMPLE RATE
 */
#define AC97_CMD_FCSAMPLE		FIELD(7, 3, 0)

#define AC97_CMD_RESET			FIELD(1, 1, 0)
#define AC97_CMD_ENABLE			FIELD(1, 1, 0)
#define AC97_CMD_DISABLE		FIELD(0, 1, 0)
