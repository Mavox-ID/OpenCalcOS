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
#ifndef ASM_ARCH_PFIFO_H
#define ASM_ARCH_PFIFO_H

static inline int pfifo_push(int no, unsigned int pointer)
{
	writel(pointer, NETX_PFIFO_BASE(no));
	return 0;
}

static inline unsigned int pfifo_pop(int no)
{
	return readl(NETX_PFIFO_BASE(no));
}

static inline int pfifo_fill_level(int no)
{

	return readl(NETX_PFIFO_FILL_LEVEL(no));
}

static inline int pfifo_full(int no)
{
	return readl(NETX_PFIFO_FULL) & (1<<no) ? 1 : 0;
}

static inline int pfifo_empty(int no)
{
	return readl(NETX_PFIFO_EMPTY) & (1<<no) ? 1 : 0;
}

int pfifo_request(unsigned int pfifo_mask);
void pfifo_free(unsigned int pfifo_mask);

#endif /* ASM_ARCH_PFIFO_H */
