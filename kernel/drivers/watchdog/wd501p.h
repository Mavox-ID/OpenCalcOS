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
#define WDT_COUNT0		(io+0)
#define WDT_COUNT1		(io+1)
#define WDT_COUNT2		(io+2)
#define WDT_CR			(io+3)
#define WDT_SR			(io+4)	/* Start buzzer on PCI write */
#define WDT_RT			(io+5)	/* Stop buzzer on PCI write */
#define WDT_BUZZER		(io+6)	/* PCI only: rd=disable, wr=enable */
#define WDT_DC			(io+7)

/* The following are only on the PCI card, they're outside of I/O space on
 * the ISA card: */
#define WDT_CLOCK		(io+12)	/* COUNT2: rd=16.67MHz, wr=2.0833MHz */
/* inverted opto isolated reset output: */
#define WDT_OPTONOTRST		(io+13)	/* wr=enable, rd=disable */
/* opto isolated reset output: */
#define WDT_OPTORST		(io+14)	/* wr=enable, rd=disable */
/* programmable outputs: */
#define WDT_PROGOUT		(io+15)	/* wr=enable, rd=disable */

							 /* FAN 501 500 */
#define WDC_SR_WCCR		1	/* Active low */ /*  X   X   X  */
#define WDC_SR_TGOOD		2			 /*  X   X   -  */
#define WDC_SR_ISOI0		4			 /*  X   X   X  */
#define WDC_SR_ISII1		8			 /*  X   X   X  */
#define WDC_SR_FANGOOD		16			 /*  X   -   -  */
#define WDC_SR_PSUOVER		32	/* Active low */ /*  X   X   -  */
#define WDC_SR_PSUUNDR		64	/* Active low */ /*  X   X   -  */
#define WDC_SR_IRQ		128	/* Active low */ /*  X   X   X  */

