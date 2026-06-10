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
#include <subdev/device.h>
#include <subdev/bios.h>
#include <subdev/gpio.h>
#include <subdev/i2c.h>
#include <subdev/clock.h>
#include <subdev/therm.h>
#include <subdev/mxm.h>
#include <subdev/devinit.h>
#include <subdev/mc.h>
#include <subdev/timer.h>
#include <subdev/fb.h>
#include <subdev/instmem.h>
#include <subdev/vm.h>
#include <subdev/bar.h>

#include <engine/dmaobj.h>
#include <engine/fifo.h>
#include <engine/software.h>
#include <engine/graph.h>
#include <engine/mpeg.h>
#include <engine/vp.h>
#include <engine/crypt.h>
#include <engine/bsp.h>
#include <engine/ppp.h>
#include <engine/copy.h>
#include <engine/disp.h>

int
nv50_identify(struct nouveau_device *device)
{
	switch (device->chipset) {
	case 0x50:
		device->cname = "G80";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv50_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv50_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv50_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv50_disp_oclass;
		break;
	case 0x84:
		device->cname = "G84";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv50_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv84_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_CRYPT  ] = &nv84_crypt_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv84_disp_oclass;
		break;
	case 0x86:
		device->cname = "G86";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv50_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv84_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_CRYPT  ] = &nv84_crypt_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv84_disp_oclass;
		break;
	case 0x92:
		device->cname = "G92";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv50_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv84_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_CRYPT  ] = &nv84_crypt_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv84_disp_oclass;
		break;
	case 0x94:
		device->cname = "G94";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv50_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv84_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_CRYPT  ] = &nv84_crypt_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv94_disp_oclass;
		break;
	case 0x96:
		device->cname = "G96";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv50_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv84_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_CRYPT  ] = &nv84_crypt_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv94_disp_oclass;
		break;
	case 0x98:
		device->cname = "G98";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv98_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_CRYPT  ] = &nv98_crypt_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nv98_ppp_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv94_disp_oclass;
		break;
	case 0xa0:
		device->cname = "G200";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv98_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv84_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_CRYPT  ] = &nv84_crypt_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva0_disp_oclass;
		break;
	case 0xaa:
		device->cname = "MCP77/MCP78";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv98_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_CRYPT  ] = &nv98_crypt_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nv98_ppp_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv94_disp_oclass;
		break;
	case 0xac:
		device->cname = "MCP79/MCP7A";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv50_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv98_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_CRYPT  ] = &nv98_crypt_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nv98_ppp_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv94_disp_oclass;
		break;
	case 0xa3:
		device->cname = "GT215";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nva3_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv98_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv84_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nv98_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nva3_copy_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xa5:
		device->cname = "GT216";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nva3_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv98_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nv98_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nva3_copy_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xa8:
		device->cname = "GT218";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nva3_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv98_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nv98_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nva3_copy_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xaf:
		device->cname = "MCP89";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nva3_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv98_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv50_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv50_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nv50_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv50_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv84_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv50_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv50_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nv84_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nv84_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nv98_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nva3_copy_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	default:
		nv_fatal(device, "unknown Tesla chipset\n");
		return -EINVAL;
	}

	return 0;
}
