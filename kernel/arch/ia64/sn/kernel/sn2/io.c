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
#include <asm/sn/io.h>

#ifdef CONFIG_IA64_GENERIC

#undef __sn_inb
#undef __sn_inw
#undef __sn_inl
#undef __sn_outb
#undef __sn_outw
#undef __sn_outl
#undef __sn_readb
#undef __sn_readw
#undef __sn_readl
#undef __sn_readq
#undef __sn_readb_relaxed
#undef __sn_readw_relaxed
#undef __sn_readl_relaxed
#undef __sn_readq_relaxed

unsigned int __sn_inb(unsigned long port)
{
	return ___sn_inb(port);
}

unsigned int __sn_inw(unsigned long port)
{
	return ___sn_inw(port);
}

unsigned int __sn_inl(unsigned long port)
{
	return ___sn_inl(port);
}

void __sn_outb(unsigned char val, unsigned long port)
{
	___sn_outb(val, port);
}

void __sn_outw(unsigned short val, unsigned long port)
{
	___sn_outw(val, port);
}

void __sn_outl(unsigned int val, unsigned long port)
{
	___sn_outl(val, port);
}

unsigned char __sn_readb(void __iomem *addr)
{
	return ___sn_readb(addr);
}

unsigned short __sn_readw(void __iomem *addr)
{
	return ___sn_readw(addr);
}

unsigned int __sn_readl(void __iomem *addr)
{
	return ___sn_readl(addr);
}

unsigned long __sn_readq(void __iomem *addr)
{
	return ___sn_readq(addr);
}

unsigned char __sn_readb_relaxed(void __iomem *addr)
{
	return ___sn_readb_relaxed(addr);
}

unsigned short __sn_readw_relaxed(void __iomem *addr)
{
	return ___sn_readw_relaxed(addr);
}

unsigned int __sn_readl_relaxed(void __iomem *addr)
{
	return ___sn_readl_relaxed(addr);
}

unsigned long __sn_readq_relaxed(void __iomem *addr)
{
	return ___sn_readq_relaxed(addr);
}

#endif
