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
#ifndef __DVI_H__
#define __DVI_H__

/*Definition TMDS Device ID register*/
#define     VT1632_DEVICE_ID_REG        0x02
#define     VT1632_DEVICE_ID            0x92

#define     GET_DVI_SIZE_BY_SYSTEM_BIOS     0x01
#define     GET_DVI_SIZE_BY_VGA_BIOS        0x02
#define     GET_DVI_SZIE_BY_HW_STRAPPING    0x03

/* Definition DVI Panel ID*/
/* Resolution: 640x480,   Channel: single, Dithering: Enable */
#define     DVI_PANEL_ID0_640X480       0x00
/* Resolution: 800x600,   Channel: single, Dithering: Enable */
#define     DVI_PANEL_ID1_800x600       0x01
/* Resolution: 1024x768,  Channel: single, Dithering: Enable */
#define     DVI_PANEL_ID1_1024x768      0x02
/* Resolution: 1280x768,  Channel: single, Dithering: Enable */
#define     DVI_PANEL_ID1_1280x768      0x03
/* Resolution: 1280x1024, Channel: dual,   Dithering: Enable */
#define     DVI_PANEL_ID1_1280x1024     0x04
/* Resolution: 1400x1050, Channel: dual,   Dithering: Enable */
#define     DVI_PANEL_ID1_1400x1050     0x05
/* Resolution: 1600x1200, Channel: dual,   Dithering: Enable */
#define     DVI_PANEL_ID1_1600x1200     0x06

/* Define the version of EDID*/
#define     EDID_VERSION_1      1
#define     EDID_VERSION_2      2

#define     DEV_CONNECT_DVI     0x01
#define     DEV_CONNECT_HDMI    0x02

int viafb_dvi_sense(void);
void viafb_dvi_disable(void);
void viafb_dvi_enable(void);
bool viafb_tmds_trasmitter_identify(void);
void viafb_init_dvi_size(struct tmds_chip_information *tmds_chip,
	struct tmds_setting_information *tmds_setting);
void viafb_dvi_set_mode(const struct fb_var_screeninfo *var,
	u16 cxres, u16 cyres, int iga);

#endif /* __DVI_H__ */
