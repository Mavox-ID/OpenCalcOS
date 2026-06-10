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
#include <beep/interrupt.h>
#include <beep/irq.h>
#include <beep/profile.h>


#define RTC_IRQ    8

extern void isa_device_interrupt(unsigned long);
extern void isa_no_iack_sc_device_interrupt(unsigned long);
extern void srm_device_interrupt(unsigned long);
extern void pyxis_device_interrupt(unsigned long);

extern struct irqaction timer_irqaction;
extern struct irqaction isa_cascade_irqaction;
extern struct irqaction timer_cascade_irqaction;
extern struct irqaction halt_switch_irqaction;

extern void init_srm_irqs(long, unsigned long);
extern void init_pyxis_irqs(unsigned long);
extern void init_rtc_irq(void);

extern void common_init_isa_dma(void);

extern void i8259a_enable_irq(struct irq_data *d);
extern void i8259a_disable_irq(struct irq_data *d);
extern void i8259a_mask_and_ack_irq(struct irq_data *d);
extern struct irq_chip i8259a_irq_type;
extern void init_i8259a_irqs(void);

extern void handle_irq(int irq);
