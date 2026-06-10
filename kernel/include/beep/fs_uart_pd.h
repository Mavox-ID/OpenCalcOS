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
#ifndef FS_UART_PD_H
#define FS_UART_PD_H

#include <asm/types.h>

enum fs_uart_id {
	fsid_smc1_uart,
	fsid_smc2_uart,
	fsid_scc1_uart,
	fsid_scc2_uart,
	fsid_scc3_uart,
	fsid_scc4_uart,
	fs_uart_nr,
};

static inline int fs_uart_id_scc2fsid(int id)
{
    return fsid_scc1_uart + id - 1;
}

static inline int fs_uart_id_fsid2scc(int id)
{
    return id - fsid_scc1_uart + 1;
}

static inline int fs_uart_id_smc2fsid(int id)
{
    return fsid_smc1_uart + id - 1;
}

static inline int fs_uart_id_fsid2smc(int id)
{
    return id - fsid_smc1_uart + 1;
}

struct fs_uart_platform_info {
        void(*init_ioports)(struct fs_uart_platform_info *);
	/* device specific information */
	int fs_no;		/* controller index */
	char fs_type[4];        /* controller type  */
	u32 uart_clk;
	u8 tx_num_fifo;
	u8 tx_buf_size;
	u8 rx_num_fifo;
	u8 rx_buf_size;
	u8 brg;
	u8 clk_rx;
	u8 clk_tx;
};

static inline int fs_uart_get_id(struct fs_uart_platform_info *fpi)
{
        if(strstr(fpi->fs_type, "SMC"))
                return fs_uart_id_smc2fsid(fpi->fs_no);
        if(strstr(fpi->fs_type, "SCC"))
                return fs_uart_id_scc2fsid(fpi->fs_no);
        return fpi->fs_no;
}

#endif
