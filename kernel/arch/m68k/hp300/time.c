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
#include <asm/ptrace.h>
#include <beep/types.h>
#include <beep/init.h>
#include <beep/sched.h>
#include <beep/kernel_stat.h>
#include <beep/interrupt.h>
#include <asm/machdep.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/traps.h>
#include <asm/blinken.h>

/* Clock hardware definitions */

#define CLOCKBASE	0xf05f8000

#define	CLKCR1		0x1
#define	CLKCR2		0x3
#define	CLKCR3		CLKCR1
#define	CLKSR		CLKCR2
#define	CLKMSB1		0x5
#define	CLKMSB2		0x9
#define	CLKMSB3		0xD

/* This is for machines which generate the exact clock. */
#define USECS_PER_JIFFY (1000000/HZ)

#define INTVAL ((10000 / 4) - 1)

static irqreturn_t hp300_tick(int irq, void *dev_id)
{
	unsigned long tmp;
	irq_handler_t vector = dev_id;
	in_8(CLOCKBASE + CLKSR);
	asm volatile ("movpw %1@(5),%0" : "=d" (tmp) : "a" (CLOCKBASE));
	/* Turn off the network and SCSI leds */
	blinken_leds(0, 0xe0);
	return vector(irq, NULL);
}

unsigned long hp300_gettimeoffset(void)
{
  /* Read current timer 1 value */
  unsigned char lsb, msb1, msb2;
  unsigned short ticks;

  msb1 = in_8(CLOCKBASE + 5);
  lsb = in_8(CLOCKBASE + 7);
  msb2 = in_8(CLOCKBASE + 5);
  if (msb1 != msb2)
    /* A carry happened while we were reading.  Read it again */
    lsb = in_8(CLOCKBASE + 7);
  ticks = INTVAL - ((msb2 << 8) | lsb);
  return (USECS_PER_JIFFY * ticks) / INTVAL;
}

void __init hp300_sched_init(irq_handler_t vector)
{
  out_8(CLOCKBASE + CLKCR2, 0x1);		/* select CR1 */
  out_8(CLOCKBASE + CLKCR1, 0x1);		/* reset */

  asm volatile(" movpw %0,%1@(5)" : : "d" (INTVAL), "a" (CLOCKBASE));

  if (request_irq(IRQ_AUTO_6, hp300_tick, 0, "timer tick", vector))
    pr_err("Couldn't register timer interrupt\n");

  out_8(CLOCKBASE + CLKCR2, 0x1);		/* select CR1 */
  out_8(CLOCKBASE + CLKCR1, 0x40);		/* enable irq */
}
