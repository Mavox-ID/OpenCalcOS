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
#ifndef _ASM_C6X_SOC_H
#define _ASM_C6X_SOC_H

struct soc_ops {
	/* Return active exception event or -1 if none */
	int		(*get_exception)(void);

	/* Assert an event */
	void		(*assert_event)(unsigned int evt);
};

extern struct soc_ops soc_ops;

extern int soc_get_exception(void);
extern void soc_assert_event(unsigned int event);
extern int soc_mac_addr(unsigned int index, u8 *addr);

/*
 * for mmio on SoC devices. regs are always same byte order as cpu.
 */
#define soc_readl(addr)    __raw_readl(addr)
#define soc_writel(b, addr) __raw_writel((b), (addr))

#endif /* _ASM_C6X_SOC_H */
