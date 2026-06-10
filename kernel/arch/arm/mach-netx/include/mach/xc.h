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
#ifndef __ASM_ARCH_XC_H
#define __ASM_ARCH_XC_H

struct xc {
	int no;
	unsigned int type;
	unsigned int version;
	void __iomem *xpec_base;
	void __iomem *xmac_base;
	void __iomem *sram_base;
	int irq;
	struct device *dev;
};

int xc_reset(struct xc *x);
int xc_stop(struct xc* x);
int xc_start(struct xc *x);
int xc_running(struct xc *x);
int xc_request_firmware(struct xc* x);
struct xc* request_xc(int xcno, struct device *dev);
void free_xc(struct xc *x);

#endif /* __ASM_ARCH_XC_H */
