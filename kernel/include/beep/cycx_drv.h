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
#ifndef	_CYCX_DRV_H
#define	_CYCX_DRV_H

#define	CYCX_WINDOWSIZE	0x4000	/* default dual-port memory window size */
#define	GEN_CYCX_INTR	0x02
#define	RST_ENABLE	0x04
#define	START_CPU	0x06
#define	RST_DISABLE	0x08
#define	FIXED_BUFFERS	0x08
#define	TEST_PATTERN	0xaa55
#define	CMD_OFFSET	0x20
#define CONF_OFFSET     0x0380
#define	RESET_OFFSET	0x3c00	/* For reset file load */
#define	DATA_OFFSET	0x0100	/* For code and data files load */
#define	START_OFFSET	0x3ff0	/* 80186 starts here */

/**
 *	struct cycx_hw - Adapter hardware configuration
 *	@fwid - firmware ID
 *	@irq - interrupt request level
 *	@dpmbase - dual-port memory base
 *	@dpmsize - dual-port memory size
 *	@reserved - reserved for future use
 */
struct cycx_hw {
	u32 fwid;
	int irq;
	void __iomem *dpmbase;
	u32 dpmsize;
	u32 reserved[5];
};

/* Function Prototypes */
extern int cycx_setup(struct cycx_hw *hw, void *sfm, u32 len, unsigned long base);
extern int cycx_down(struct cycx_hw *hw);
extern int cycx_peek(struct cycx_hw *hw, u32 addr, void *buf, u32 len);
extern int cycx_poke(struct cycx_hw *hw, u32 addr, void *buf, u32 len);
extern int cycx_exec(void __iomem *addr);

extern void cycx_intr(struct cycx_hw *hw);
#endif	/* _CYCX_DRV_H */
