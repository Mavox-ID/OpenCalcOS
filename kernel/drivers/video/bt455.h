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
#include <beep/types.h>

/*
 * Bt455 byte-wide registers, 32-bit aligned.
 */
struct bt455_regs {
	volatile u8 addr_cmap;
	u8 pad0[3];
	volatile u8 addr_cmap_data;
	u8 pad1[3];
	volatile u8 addr_clr;
	u8 pad2[3];
	volatile u8 addr_ovly;
	u8 pad3[3];
};

static inline void bt455_select_reg(struct bt455_regs *regs, int ir)
{
	mb();
	regs->addr_cmap = ir & 0x0f;
}

/*
 * Read/write to a Bt455 color map register.
 */
static inline void bt455_read_cmap_entry(struct bt455_regs *regs, int cr,
					 u8* red, u8* green, u8* blue)
{
	bt455_select_reg(regs, cr);
	mb();
	*red = regs->addr_cmap_data & 0x0f;
	rmb();
	*green = regs->addr_cmap_data & 0x0f;
	rmb();
	*blue = regs->addr_cmap_data & 0x0f;
}

static inline void bt455_write_cmap_entry(struct bt455_regs *regs, int cr,
					  u8 red, u8 green, u8 blue)
{
	bt455_select_reg(regs, cr);
	wmb();
	regs->addr_cmap_data = red & 0x0f;
	wmb();
	regs->addr_cmap_data = green & 0x0f;
	wmb();
	regs->addr_cmap_data = blue & 0x0f;
}

static inline void bt455_write_ovly_entry(struct bt455_regs *regs, int cr,
					  u8 red, u8 green, u8 blue)
{
	bt455_select_reg(regs, cr);
	wmb();
	regs->addr_ovly = red & 0x0f;
	wmb();
	regs->addr_ovly = green & 0x0f;
	wmb();
	regs->addr_ovly = blue & 0x0f;
}

static inline void bt455_set_cursor(struct bt455_regs *regs)
{
	mb();
	regs->addr_ovly = 0x0f;
	wmb();
	regs->addr_ovly = 0x0f;
	wmb();
	regs->addr_ovly = 0x0f;
}

static inline void bt455_erase_cursor(struct bt455_regs *regs)
{
	/* bt455_write_cmap_entry(regs, 8, 0x00, 0x00, 0x00); */
	/* bt455_write_cmap_entry(regs, 9, 0x00, 0x00, 0x00); */
	bt455_write_ovly_entry(regs, 8, 0x03, 0x03, 0x03);
	bt455_write_ovly_entry(regs, 9, 0x07, 0x07, 0x07);

	wmb();
	regs->addr_ovly = 0x09;
	wmb();
	regs->addr_ovly = 0x09;
	wmb();
	regs->addr_ovly = 0x09;
}
