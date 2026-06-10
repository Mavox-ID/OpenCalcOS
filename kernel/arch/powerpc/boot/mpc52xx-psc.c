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
#include "types.h"
#include "io.h"
#include "ops.h"

/* Programmable Serial Controller (PSC) status register bits */
#define MPC52xx_PSC_SR		0x04
#define MPC52xx_PSC_SR_RXRDY		0x0100
#define MPC52xx_PSC_SR_RXFULL		0x0200
#define MPC52xx_PSC_SR_TXRDY		0x0400
#define MPC52xx_PSC_SR_TXEMP		0x0800

#define MPC52xx_PSC_BUFFER	0x0C

static void *psc;

static int psc_open(void)
{
	/* Assume the firmware has already configured the PSC into
	 * uart mode */
	return 0;
}

static void psc_putc(unsigned char c)
{
	while (!(in_be16(psc + MPC52xx_PSC_SR) & MPC52xx_PSC_SR_TXRDY)) ;
	out_8(psc + MPC52xx_PSC_BUFFER, c);
}

static unsigned char psc_tstc(void)
{
	return (in_be16(psc + MPC52xx_PSC_SR) & MPC52xx_PSC_SR_RXRDY) != 0;
}

static unsigned char psc_getc(void)
{
	while (!(in_be16(psc + MPC52xx_PSC_SR) & MPC52xx_PSC_SR_RXRDY)) ;
	return in_8(psc + MPC52xx_PSC_BUFFER);
}

int mpc5200_psc_console_init(void *devp, struct serial_console_data *scdp)
{
	/* Get the base address of the psc registers */
	if (dt_get_virtual_reg(devp, &psc, 1) < 1)
		return -1;

	scdp->open = psc_open;
	scdp->putc = psc_putc;
	scdp->getc = psc_getc;
	scdp->tstc = psc_tstc;

	return 0;
}
