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
#include <subdev/ltcg.h>
#include <subdev/ibus.h>
#include <subdev/instmem.h>
#include <subdev/vm.h>
#include <subdev/bar.h>

#include <engine/dmaobj.h>
#include <engine/fifo.h>
#include <engine/software.h>
#include <engine/graph.h>
#include <engine/vp.h>
#include <engine/bsp.h>
#include <engine/ppp.h>
#include <engine/copy.h>
#include <engine/disp.h>

int
nvc0_identify(struct nouveau_device *device)
{
	switch (device->chipset) {
	case 0xc0:
		device->cname = "GF100";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nvc0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvc0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nvc0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nvc0_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nvc0_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nvc0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nvc0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nvc0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xc4:
		device->cname = "GF104";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nvc0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvc0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nvc0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nvc0_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nvc0_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nvc0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nvc0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nvc0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xc3:
		device->cname = "GF106";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nvc0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvc0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nvc0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nvc0_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nvc0_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nvc0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nvc0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nvc0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xce:
		device->cname = "GF114";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nvc0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvc0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nvc0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nvc0_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nvc0_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nvc0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nvc0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nvc0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xcf:
		device->cname = "GF116";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nvc0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvc0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nvc0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nvc0_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nvc0_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nvc0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nvc0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nvc0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xc1:
		device->cname = "GF108";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nvc0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvc0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nvc0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nvc0_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nvc0_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nvc0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nvc0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nvc0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xc8:
		device->cname = "GF110";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv50_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nvc0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvc0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nvc0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nvc0_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nvc0_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nvc0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nvc0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_COPY1  ] = &nvc0_copy1_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nva3_disp_oclass;
		break;
	case 0xd9:
		device->cname = "GF119";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nvd0_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nvc0_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv50_therm_oclass;
		device->oclass[NVDEV_SUBDEV_MXM    ] = &nv50_mxm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv50_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nvc0_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nvc0_fb_oclass;
		device->oclass[NVDEV_SUBDEV_LTCG   ] = &nvc0_ltcg_oclass;
		device->oclass[NVDEV_SUBDEV_IBUS   ] = &nvc0_ibus_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv50_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nvc0_vmmgr_oclass;
		device->oclass[NVDEV_SUBDEV_BAR    ] = &nvc0_bar_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nvd0_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nvc0_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nvc0_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nvc0_graph_oclass;
		device->oclass[NVDEV_ENGINE_VP     ] = &nvc0_vp_oclass;
		device->oclass[NVDEV_ENGINE_BSP    ] = &nvc0_bsp_oclass;
		device->oclass[NVDEV_ENGINE_PPP    ] = &nvc0_ppp_oclass;
		device->oclass[NVDEV_ENGINE_COPY0  ] = &nvc0_copy0_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nvd0_disp_oclass;
		break;
	default:
		nv_fatal(device, "unknown Fermi chipset\n");
		return -EINVAL;
	}

	return 0;
}
