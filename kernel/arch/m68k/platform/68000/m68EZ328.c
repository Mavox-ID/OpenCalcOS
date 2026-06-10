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
/*
 *  m68EZ328.c - 68EZ328 specific config
 *
 *  Copyright (C) 1993 Hamish Macdonald
 *  Copyright (C) 1999 D. Jeff Dionne
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the main directory of this archive
 * for more details.
 */

/***************************************************************************/

#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/rtc.h>
#include <asm/pgtable.h>
#include <asm/machdep.h>
#include <asm/MC68EZ328.h>
#ifdef CONFIG_UCSIMM
#include <asm/bootstd.h>
#endif

/***************************************************************************/

int m68328_hwclk(int set, struct rtc_time *t);

/***************************************************************************/

void m68ez328_reset(void)
{
  local_irq_disable();
  asm volatile (
    "moveal #0x10c00000, %a0;\n"
    "moveb #0, 0xFFFFF300;\n"
    "moveal 0(%a0), %sp;\n"
    "moveal 4(%a0), %a0;\n"
    "jmp (%a0);\n"
    );
}

/***************************************************************************/

unsigned char *cs8900a_hwaddr;
static int errno;

#ifdef CONFIG_UCSIMM
_bsc0(char *, getserialnum)
_bsc1(unsigned char *, gethwaddr, int, a)
_bsc1(char *, getbenv, char *, a)
#endif

void config_BSP(char *command, int len)
{
  unsigned char *p;

  printk(KERN_INFO "\n68EZ328 DragonBallEZ support (C) 1999 Rt-Control, Inc\n");

#ifdef CONFIG_UCSIMM
  printk(KERN_INFO "uCsimm serial string [%s]\n",getserialnum());
  p = cs8900a_hwaddr = gethwaddr(0);
  printk(KERN_INFO "uCsimm hwaddr %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
         p[0], p[1], p[2], p[3], p[4], p[5]);

  p = getbenv("APPEND");
  if (p) strcpy(p,command);
  else command[0] = 0;
#endif
 
  mach_hwclk = m68328_hwclk;
  mach_reset = m68ez328_reset;
}

/***************************************************************************/
