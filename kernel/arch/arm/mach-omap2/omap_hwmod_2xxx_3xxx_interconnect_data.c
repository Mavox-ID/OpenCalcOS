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
#include <asm/sizes.h>

#include "omap_hwmod.h"

#include "omap_hwmod_common_data.h"

struct omap_hwmod_addr_space omap2430_mmc1_addr_space[] = {
	{
		.pa_start	= 0x4809c000,
		.pa_end		= 0x4809c1ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

struct omap_hwmod_addr_space omap2430_mmc2_addr_space[] = {
	{
		.pa_start	= 0x480b4000,
		.pa_end		= 0x480b41ff,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

struct omap_hwmod_addr_space omap2_i2c1_addr_space[] = {
	{
		.pa_start	= 0x48070000,
		.pa_end		= 0x48070000 + SZ_128 - 1,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

struct omap_hwmod_addr_space omap2_i2c2_addr_space[] = {
	{
		.pa_start	= 0x48072000,
		.pa_end		= 0x48072000 + SZ_128 - 1,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

struct omap_hwmod_addr_space omap2_dss_addrs[] = {
	{
		.pa_start	= 0x48050000,
		.pa_end		= 0x48050000 + SZ_1K - 1,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

struct omap_hwmod_addr_space omap2_dss_dispc_addrs[] = {
	{
		.pa_start	= 0x48050400,
		.pa_end		= 0x48050400 + SZ_1K - 1,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

struct omap_hwmod_addr_space omap2_dss_rfbi_addrs[] = {
	{
		.pa_start	= 0x48050800,
		.pa_end		= 0x48050800 + SZ_1K - 1,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

struct omap_hwmod_addr_space omap2_dss_venc_addrs[] = {
	{
		.pa_start	= 0x48050C00,
		.pa_end		= 0x48050C00 + SZ_1K - 1,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

struct omap_hwmod_addr_space omap2_timer10_addrs[] = {
	{
		.pa_start	= 0x48086000,
		.pa_end		= 0x48086000 + SZ_1K - 1,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

struct omap_hwmod_addr_space omap2_timer11_addrs[] = {
	{
		.pa_start	= 0x48088000,
		.pa_end		= 0x48088000 + SZ_1K - 1,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

struct omap_hwmod_addr_space omap2xxx_timer12_addrs[] = {
	{
		.pa_start	= 0x4808a000,
		.pa_end		= 0x4808a000 + SZ_1K - 1,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

struct omap_hwmod_addr_space omap2_mcspi1_addr_space[] = {
	{
		.pa_start	= 0x48098000,
		.pa_end		= 0x48098000 + SZ_256 - 1,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

struct omap_hwmod_addr_space omap2_mcspi2_addr_space[] = {
	{
		.pa_start	= 0x4809a000,
		.pa_end		= 0x4809a000 + SZ_256 - 1,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

struct omap_hwmod_addr_space omap2430_mcspi3_addr_space[] = {
	{
		.pa_start	= 0x480b8000,
		.pa_end		= 0x480b8000 + SZ_256 - 1,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

struct omap_hwmod_addr_space omap2_dma_system_addrs[] = {
	{
		.pa_start	= 0x48056000,
		.pa_end		= 0x48056000 + SZ_4K - 1,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

struct omap_hwmod_addr_space omap2_mailbox_addrs[] = {
	{
		.pa_start	= 0x48094000,
		.pa_end		= 0x48094000 + SZ_512 - 1,
		.flags		= ADDR_TYPE_RT,
	},
	{ }
};

struct omap_hwmod_addr_space omap2_mcbsp1_addrs[] = {
	{
		.name		= "mpu",
		.pa_start	= 0x48074000,
		.pa_end		= 0x480740ff,
		.flags		= ADDR_TYPE_RT
	},
	{ }
};

struct omap_hwmod_addr_space omap2_hdq1w_addr_space[] = {
	{
		.pa_start       = 0x480b2000,
		.pa_end         = 0x480b2fff,
		.flags          = ADDR_TYPE_RT,
	},
	{ }
};
