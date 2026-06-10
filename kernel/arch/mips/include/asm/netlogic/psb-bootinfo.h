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
#ifndef _ASM_NETLOGIC_BOOTINFO_H
#define _ASM_NETLOGIC_BOOTINFO_H

struct psb_info {
	uint64_t boot_level;
	uint64_t io_base;
	uint64_t output_device;
	uint64_t uart_print;
	uint64_t led_output;
	uint64_t init;
	uint64_t exit;
	uint64_t warm_reset;
	uint64_t wakeup;
	uint64_t online_cpu_map;
	uint64_t master_reentry_sp;
	uint64_t master_reentry_gp;
	uint64_t master_reentry_fn;
	uint64_t slave_reentry_fn;
	uint64_t magic_dword;
	uint64_t uart_putchar;
	uint64_t size;
	uint64_t uart_getchar;
	uint64_t nmi_handler;
	uint64_t psb_version;
	uint64_t mac_addr;
	uint64_t cpu_frequency;
	uint64_t board_version;
	uint64_t malloc;
	uint64_t free;
	uint64_t global_shmem_addr;
	uint64_t global_shmem_size;
	uint64_t psb_os_cpu_map;
	uint64_t userapp_cpu_map;
	uint64_t wakeup_os;
	uint64_t psb_mem_map;
	uint64_t board_major_version;
	uint64_t board_minor_version;
	uint64_t board_manf_revision;
	uint64_t board_serial_number;
	uint64_t psb_physaddr_map;
	uint64_t xlr_loaderip_config;
	uint64_t bldr_envp;
	uint64_t avail_mem_map;
};

enum {
	NETLOGIC_IO_SPACE = 0x10,
	PCIX_IO_SPACE,
	PCIX_CFG_SPACE,
	PCIX_MEMORY_SPACE,
	HT_IO_SPACE,
	HT_CFG_SPACE,
	HT_MEMORY_SPACE,
	SRAM_SPACE,
	FLASH_CONTROLLER_SPACE
};

#define NLM_MAX_ARGS	64
#define NLM_MAX_ENVS	32

/* This is what netlboot passes and beep boot_mem_map is subtly different */
#define NLM_BOOT_MEM_MAP_MAX	32
struct nlm_boot_mem_map {
	int nr_map;
	struct nlm_boot_mem_map_entry {
		uint64_t addr;		/* start of memory segment */
		uint64_t size;		/* size of memory segment */
		uint32_t type;		/* type of memory segment */
	} map[NLM_BOOT_MEM_MAP_MAX];
};

/* Pointer to saved boot loader info */
extern struct psb_info nlm_prom_info;

#endif
