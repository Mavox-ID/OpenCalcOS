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
#include <engine/mpeg.h>
#include <engine/disp.h>

int
nv40_identify(struct nouveau_device *device)
{
	switch (device->chipset) {
	case 0x40:
		device->cname = "NV40";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv40_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x41:
		device->cname = "NV41";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv41_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv41_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x42:
		device->cname = "NV42";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv41_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv41_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x43:
		device->cname = "NV43";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv41_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv41_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x45:
		device->cname = "NV45";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv40_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv04_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x47:
		device->cname = "G70";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv47_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv41_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x49:
		device->cname = "G71";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv49_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv41_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x4b:
		device->cname = "G73";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv04_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv49_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv41_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x44:
		device->cname = "NV44";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv44_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv44_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv44_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x46:
		device->cname = "G72";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv44_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv46_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv44_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x4a:
		device->cname = "NV44A";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv44_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv44_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv44_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x4c:
		device->cname = "C61";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv44_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv46_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv44_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x4e:
		device->cname = "C51";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv44_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv4e_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv44_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x63:
		device->cname = "C73";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv44_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv46_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv44_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x67:
		device->cname = "C67";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv44_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv46_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv44_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	case 0x68:
		device->cname = "C68";
		device->oclass[NVDEV_SUBDEV_VBIOS  ] = &nouveau_bios_oclass;
		device->oclass[NVDEV_SUBDEV_GPIO   ] = &nv10_gpio_oclass;
		device->oclass[NVDEV_SUBDEV_I2C    ] = &nouveau_i2c_oclass;
		device->oclass[NVDEV_SUBDEV_CLOCK  ] = &nv40_clock_oclass;
		device->oclass[NVDEV_SUBDEV_THERM  ] = &nv40_therm_oclass;
		device->oclass[NVDEV_SUBDEV_DEVINIT] = &nv1a_devinit_oclass;
		device->oclass[NVDEV_SUBDEV_MC     ] = &nv44_mc_oclass;
		device->oclass[NVDEV_SUBDEV_TIMER  ] = &nv04_timer_oclass;
		device->oclass[NVDEV_SUBDEV_FB     ] = &nv46_fb_oclass;
		device->oclass[NVDEV_SUBDEV_INSTMEM] = &nv40_instmem_oclass;
		device->oclass[NVDEV_SUBDEV_VM     ] = &nv44_vmmgr_oclass;
		device->oclass[NVDEV_ENGINE_DMAOBJ ] = &nv04_dmaeng_oclass;
		device->oclass[NVDEV_ENGINE_FIFO   ] = &nv40_fifo_oclass;
		device->oclass[NVDEV_ENGINE_SW     ] = &nv10_software_oclass;
		device->oclass[NVDEV_ENGINE_GR     ] = &nv40_graph_oclass;
		device->oclass[NVDEV_ENGINE_MPEG   ] = &nv40_mpeg_oclass;
		device->oclass[NVDEV_ENGINE_DISP   ] = &nv04_disp_oclass;
		break;
	default:
		nv_fatal(device, "unknown Curie chipset\n");
		return -EINVAL;
	}

	return 0;
}
