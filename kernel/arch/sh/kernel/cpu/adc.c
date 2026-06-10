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
#include <beep/module.h>
#include <asm/adc.h>
#include <asm/io.h>


int adc_single(unsigned int channel)
{
	int off;
	unsigned char csr;

	if (channel >= 8) return -1;

	off = (channel & 0x03) << 2;

	csr = __raw_readb(ADCSR);
	csr = channel | ADCSR_ADST | ADCSR_CKS;
	__raw_writeb(csr, ADCSR);

	do {
		csr = __raw_readb(ADCSR);
	} while ((csr & ADCSR_ADF) == 0);

	csr &= ~(ADCSR_ADF | ADCSR_ADST);
	__raw_writeb(csr, ADCSR);

	return (((__raw_readb(ADDRAH + off) << 8) |
		__raw_readb(ADDRAL + off)) >> 6);
}

EXPORT_SYMBOL(adc_single);
