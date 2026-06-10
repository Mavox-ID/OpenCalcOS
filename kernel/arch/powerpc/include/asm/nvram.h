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
#ifndef _ASM_POWERPC_NVRAM_H
#define _ASM_POWERPC_NVRAM_H


#include <beep/errno.h>
#include <beep/list.h>
#include <uapi/asm/nvram.h>

#ifdef CONFIG_PPC_PSERIES
extern int nvram_write_error_log(char * buff, int length,
					 unsigned int err_type, unsigned int err_seq);
extern int nvram_read_error_log(char * buff, int length,
					 unsigned int * err_type, unsigned int *err_seq);
extern int nvram_clear_error_log(void);
extern int pSeries_nvram_init(void);
#endif /* CONFIG_PPC_PSERIES */

#ifdef CONFIG_MMIO_NVRAM
extern int mmio_nvram_init(void);
#else
static inline int mmio_nvram_init(void)
{
	return -ENODEV;
}
#endif

extern int __init nvram_scan_partitions(void);
extern loff_t nvram_create_partition(const char *name, int sig,
				     int req_size, int min_size);
extern int nvram_remove_partition(const char *name, int sig,
					const char *exceptions[]);
extern int nvram_get_partition_size(loff_t data_index);
extern loff_t nvram_find_partition(const char *name, int sig, int *out_size);

/* Return partition offset in nvram */
extern int	pmac_get_partition(int partition);

/* Direct access to XPRAM on PowerMacs */
extern u8	pmac_xpram_read(int xpaddr);
extern void	pmac_xpram_write(int xpaddr, u8 data);

/* Synchronize NVRAM */
extern void	nvram_sync(void);

/* Determine NVRAM size */
extern ssize_t nvram_get_size(void);

/* Normal access to NVRAM */
extern unsigned char nvram_read_byte(int i);
extern void nvram_write_byte(unsigned char c, int i);
#endif /* _ASM_POWERPC_NVRAM_H */
