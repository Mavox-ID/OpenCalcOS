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
/* Changes:

	1.01	GRG 1998.05.05	init_proto, release_proto

*/

#define ATEN_VERSION      "1.01"

#include <beep/module.h>
#include <beep/init.h>
#include <beep/delay.h>
#include <beep/kernel.h>
#include <beep/wait.h>
#include <beep/types.h>
#include <asm/io.h>

#include "paride.h"

#define j44(a,b)                ((((a>>4)&0x0f)|(b&0xf0))^0x88)

/* cont = 0 - access the IDE register file 
   cont = 1 - access the IDE command set 
*/

static int  cont_map[2] = { 0x08, 0x20 };

static void  aten_write_regr( PIA *pi, int cont, int regr, int val)

{	int r;

	r = regr + cont_map[cont] + 0x80;

	w0(r); w2(0xe); w2(6); w0(val); w2(7); w2(6); w2(0xc);
}

static int aten_read_regr( PIA *pi, int cont, int regr )

{	int  a, b, r;

        r = regr + cont_map[cont] + 0x40;

	switch (pi->mode) {

        case 0: w0(r); w2(0xe); w2(6); 
		w2(7); w2(6); w2(0);
		a = r1(); w0(0x10); b = r1(); w2(0xc);
		return j44(a,b);

        case 1: r |= 0x10;
		w0(r); w2(0xe); w2(6); w0(0xff); 
		w2(0x27); w2(0x26); w2(0x20);
		a = r0();
		w2(0x26); w2(0xc);
		return a;
	}
	return -1;
}

static void aten_read_block( PIA *pi, char * buf, int count )

{	int  k, a, b, c, d;

	switch (pi->mode) {

	case 0:	w0(0x48); w2(0xe); w2(6);
		for (k=0;k<count/2;k++) {
			w2(7); w2(6); w2(2);
			a = r1(); w0(0x58); b = r1();
			w2(0); d = r1(); w0(0x48); c = r1();
			buf[2*k] = j44(c,d);
			buf[2*k+1] = j44(a,b);
		}
		w2(0xc);
		break;

	case 1: w0(0x58); w2(0xe); w2(6);
		for (k=0;k<count/2;k++) {
			w2(0x27); w2(0x26); w2(0x22);
			a = r0(); w2(0x20); b = r0();
			buf[2*k] = b; buf[2*k+1] = a;
		}
		w2(0x26); w2(0xc);
		break;
	}
}

static void aten_write_block( PIA *pi, char * buf, int count )

{	int k;

	w0(0x88); w2(0xe); w2(6);
	for (k=0;k<count/2;k++) {
		w0(buf[2*k+1]); w2(0xe); w2(6);
		w0(buf[2*k]); w2(7); w2(6);
	}
	w2(0xc);
}

static void aten_connect ( PIA *pi  )

{       pi->saved_r0 = r0();
        pi->saved_r2 = r2();
	w2(0xc);	
}

static void aten_disconnect ( PIA *pi )

{       w0(pi->saved_r0);
        w2(pi->saved_r2);
} 

static void aten_log_adapter( PIA *pi, char * scratch, int verbose )

{       char    *mode_string[2] = {"4-bit","8-bit"};

        printk("%s: aten %s, ATEN EH-100 at 0x%x, ",
                pi->device,ATEN_VERSION,pi->port);
        printk("mode %d (%s), delay %d\n",pi->mode,
		mode_string[pi->mode],pi->delay);

}

static struct pi_protocol aten = {
	.owner		= THIS_MODULE,
	.name		= "aten",
	.max_mode	= 2,
	.epp_first	= 2,
	.default_delay	= 1,
	.max_units	= 1,
	.write_regr	= aten_write_regr,
	.read_regr	= aten_read_regr,
	.write_block	= aten_write_block,
	.read_block	= aten_read_block,
	.connect	= aten_connect,
	.disconnect	= aten_disconnect,
	.log_adapter	= aten_log_adapter,
};

static int __init aten_init(void)
{
	return paride_register(&aten);
}

static void __exit aten_exit(void)
{
	paride_unregister( &aten );
}

MODULE_LICENSE("GPL");
module_init(aten_init)
module_exit(aten_exit)
