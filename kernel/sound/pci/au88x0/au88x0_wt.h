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
#ifndef _AU88X0_WT_H
#define _AU88X0_WT_H

/* WT channels are grouped in banks. Each bank has 0x20 channels. */
/* Bank register address boundary is 0x8000 */

#define NR_WT_PB 0x20

/* WT bank base register (as dword address). */
#define WT_BAR(x) (((x)&0xffe0)<<0x8)
#define WT_BANK(x) (x>>5)
/* WT Bank registers */
#define WT_CTRL(bank)	(((((bank)&1)<<0xd) + 0x00)<<2)	/* 0x0000 */
#define WT_SRAMP(bank)	(((((bank)&1)<<0xd) + 0x01)<<2)	/* 0x0004 */
#define WT_DSREG(bank)	(((((bank)&1)<<0xd) + 0x02)<<2)	/* 0x0008 */
#define WT_MRAMP(bank)	(((((bank)&1)<<0xd) + 0x03)<<2)	/* 0x000c */
#define WT_GMODE(bank)	(((((bank)&1)<<0xd) + 0x04)<<2)	/* 0x0010 */
#define WT_ARAMP(bank)	(((((bank)&1)<<0xd) + 0x05)<<2)	/* 0x0014 */
/* WT Voice registers */
#define WT_STEREO(voice)	((WT_BAR(voice)+ 0x20 +(((voice)&0x1f)>>1))<<2)	/* 0x0080 */
#define WT_MUTE(voice)		((WT_BAR(voice)+ 0x40 +((voice)&0x1f))<<2)	/* 0x0100 */
#define WT_RUN(voice)		((WT_BAR(voice)+ 0x60 +((voice)&0x1f))<<2)	/* 0x0180 */
/* Some kind of parameters. */
/* PARM0, PARM1 : Filter (0xFF000000), SampleRate (0x0000FFFF) */
/* PARM2, PARM3 : Still unknown */
#define WT_PARM(x,y)	(((WT_BAR(x))+ 0x80 +(((x)&0x1f)<<2)+(y))<<2)	/* 0x0200 */
#define WT_DELAY(x,y)	(((WT_BAR(x))+ 0x100 +(((x)&0x1f)<<2)+(y))<<2)	/* 0x0400 */

/* Numeric indexes used by SetReg() and GetReg() */
#if 0
enum {
	run = 0,		/* 0  W 1:run 0:stop */
	parm0,			/* 1  W filter, samplerate */
	parm1,			/* 2  W filter, samplerate */
	parm2,			/* 3  W  */
	parm3,			/* 4  RW volume. This value is calculated using floating point ops. */
	sramp,			/* 5  W */
	mute,			/* 6  W 1:mute, 0:unmute */
	gmode,			/* 7  RO Looks like only bit0 is used. */
	aramp,			/* 8  W */
	mramp,			/* 9  W */
	ctrl,			/* a  W */
	delay,			/* b  W All 4 values are written at once with same value. */
	dsreg,			/* c  (R)W */
} wt_reg;
#endif

typedef struct {
	u32 parm0;	/* this_1E4 */
	u32 parm1;	/* this_1E8 */
	u32 parm2;	/* this_1EC */
	u32 parm3;	/* this_1F0 */
	u32 this_1D0;
} wt_voice_t;

#endif				/* _AU88X0_WT_H */

/* End of file */
