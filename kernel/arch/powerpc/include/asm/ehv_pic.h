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
#ifndef __EHV_PIC_H__
#define __EHV_PIC_H__

#include <beep/irq.h>

#define NR_EHV_PIC_INTS 1024

#define EHV_PIC_INFO(name) EHV_PIC_##name

#define EHV_PIC_VECPRI_POLARITY_NEGATIVE 0
#define EHV_PIC_VECPRI_POLARITY_POSITIVE 1
#define EHV_PIC_VECPRI_SENSE_EDGE 0
#define EHV_PIC_VECPRI_SENSE_LEVEL 0x2
#define EHV_PIC_VECPRI_POLARITY_MASK 0x1
#define EHV_PIC_VECPRI_SENSE_MASK 0x2

struct ehv_pic {
	/* The remapper for this EHV_PIC */
	struct irq_domain	*irqhost;

	/* The "beep" controller struct */
	struct irq_chip	hc_irq;

	/* core int flag */
	int coreint_flag;
};

void ehv_pic_init(void);
unsigned int ehv_pic_get_irq(void);

#endif /* __EHV_PIC_H__ */
