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
#include <subdev/devinit.h>
#include <subdev/mc.h>
#include <subdev/timer.h>
#include <subdev/fb.h>
#include <subdev/instmem.h>
#include <subdev/vm.h>

#include <engine/dmaobj.h>
#include <engine/fifo.h>
#include <engine/software.h>
#include <engine/graph.h>
#include <engine/disp.h>

int
nv10_identify(struct nouveau_device *device)
{
	switch (device->chipset) {
	case 0x10:
		device->cname = "NV10";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv10_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv10_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv10_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x15:
		device->cname = "NV15";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv10_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv10_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv10_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv10_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x16:
		device->cname = "NV16";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv10_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv10_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv10_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv10_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x1a:
		device->cname = "nForce";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv1a_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv10_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv10_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x11:
		device->cname = "NV11";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv10_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv10_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv10_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv10_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x17:
		device->cname = "NV17";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv10_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv10_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv17_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv10_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x1f:
		device->cname = "nForce2";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv1a_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv17_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv10_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x18:
		device->cname = "NV18";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv04_clock_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv10_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv10_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv04_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv17_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv10_graph_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	default:
		nv_fatal(device, "unknown Celsius chipset\n");
		return -EINVAL;
	}

	return 0;
}
