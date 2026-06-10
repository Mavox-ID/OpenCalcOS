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
#ifndef __TPA6130A2_H__
#define __TPA6130A2_H__

/* Register addresses */
#define TPA6130A2_REG_CONTROL		0x01
#define TPA6130A2_REG_VOL_MUTE		0x02
#define TPA6130A2_REG_OUT_IMPEDANCE	0x03
#define TPA6130A2_REG_VERSION		0x04

#define TPA6130A2_CACHEREGNUM	(TPA6130A2_REG_VERSION + 1)

/* Register bits */
/* TPA6130A2_REG_CONTROL (0x01) */
#define TPA6130A2_SWS			(0x01 << 0)
#define TPA6130A2_TERMAL		(0x01 << 1)
#define TPA6130A2_MODE(x)		(x << 4)
#define TPA6130A2_MODE_STEREO		(0x00)
#define TPA6130A2_MODE_DUAL_MONO	(0x01)
#define TPA6130A2_MODE_BRIDGE		(0x02)
#define TPA6130A2_MODE_MASK		(0x03)
#define TPA6130A2_HP_EN_R		(0x01 << 6)
#define TPA6130A2_HP_EN_L		(0x01 << 7)

/* TPA6130A2_REG_VOL_MUTE (0x02) */
#define TPA6130A2_VOLUME(x)		((x & 0x3f) << 0)
#define TPA6130A2_MUTE_R		(0x01 << 6)
#define TPA6130A2_MUTE_L		(0x01 << 7)

/* TPA6130A2_REG_OUT_IMPEDANCE (0x03) */
#define TPA6130A2_HIZ_R			(0x01 << 0)
#define TPA6130A2_HIZ_L			(0x01 << 1)

/* TPA6130A2_REG_VERSION (0x04) */
#define TPA6130A2_VERSION_MASK		(0x0f)

extern int tpa6130a2_add_controls(struct snd_soc_codec *codec);
extern int tpa6130a2_stereo_enable(struct snd_soc_codec *codec, int enable);

#endif /* __TPA6130A2_H__ */
