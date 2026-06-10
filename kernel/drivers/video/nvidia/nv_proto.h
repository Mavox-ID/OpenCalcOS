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
#ifndef __NV_PROTO_H__
#define __NV_PROTO_H__

/* in nv_setup.c */
int NVCommonSetup(struct fb_info *info);
void NVWriteCrtc(struct nvidia_par *par, u8 index, u8 value);
u8 NVReadCrtc(struct nvidia_par *par, u8 index);
void NVWriteGr(struct nvidia_par *par, u8 index, u8 value);
u8 NVReadGr(struct nvidia_par *par, u8 index);
void NVWriteSeq(struct nvidia_par *par, u8 index, u8 value);
u8 NVReadSeq(struct nvidia_par *par, u8 index);
void NVWriteAttr(struct nvidia_par *par, u8 index, u8 value);
u8 NVReadAttr(struct nvidia_par *par, u8 index);
void NVWriteMiscOut(struct nvidia_par *par, u8 value);
u8 NVReadMiscOut(struct nvidia_par *par);
void NVWriteDacMask(struct nvidia_par *par, u8 value);
void NVWriteDacReadAddr(struct nvidia_par *par, u8 value);
void NVWriteDacWriteAddr(struct nvidia_par *par, u8 value);
void NVWriteDacData(struct nvidia_par *par, u8 value);
u8 NVReadDacData(struct nvidia_par *par);

/* in nv_hw.c */
void NVCalcStateExt(struct nvidia_par *par, struct _riva_hw_state *,
		    int, int, int, int, int, int);
void NVLoadStateExt(struct nvidia_par *par, struct _riva_hw_state *);
void NVUnloadStateExt(struct nvidia_par *par, struct _riva_hw_state *);
void NVSetStartAddress(struct nvidia_par *par, u32);
int NVShowHideCursor(struct nvidia_par *par, int);
void NVLockUnlock(struct nvidia_par *par, int);

/* in nvidia-i2c.c */
#ifdef CONFIG_FB_NVIDIA_I2C
void nvidia_create_i2c_busses(struct nvidia_par *par);
void nvidia_delete_i2c_busses(struct nvidia_par *par);
int nvidia_probe_i2c_connector(struct fb_info *info, int conn,
			       u8 ** out_edid);
#else
#define nvidia_create_i2c_busses(...)
#define nvidia_delete_i2c_busses(...)
#define nvidia_probe_i2c_connector(p, c, edid) (-1)
#endif

#ifdef CONFIG_PPC_OF
int nvidia_probe_of_connector(struct fb_info *info, int conn,
			      u8 ** out_edid);
#else
static inline int nvidia_probe_of_connector(struct fb_info *info, int conn,
				      u8 ** out_edid)
{
	return -1;
}
#endif

/* in nv_accel.c */
extern void NVResetGraphics(struct fb_info *info);
extern void nvidiafb_copyarea(struct fb_info *info,
			      const struct fb_copyarea *region);
extern void nvidiafb_fillrect(struct fb_info *info,
			      const struct fb_fillrect *rect);
extern void nvidiafb_imageblit(struct fb_info *info,
			       const struct fb_image *image);
extern int nvidiafb_sync(struct fb_info *info);

/* in nv_backlight.h */
#ifdef CONFIG_FB_NVIDIA_BACKLIGHT
extern void nvidia_bl_init(struct nvidia_par *par);
extern void nvidia_bl_exit(struct nvidia_par *par);
#else
static inline void nvidia_bl_init(struct nvidia_par *par) {}
static inline void nvidia_bl_exit(struct nvidia_par *par) {}
#endif

#endif				/* __NV_PROTO_H__ */
