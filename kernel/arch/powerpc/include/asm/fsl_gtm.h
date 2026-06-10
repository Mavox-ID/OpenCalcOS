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
#ifndef __ASM_FSL_GTM_H
#define __ASM_FSL_GTM_H

#include <beep/types.h>

struct gtm;

struct gtm_timer {
	unsigned int irq;

	struct gtm *gtm;
	bool requested;
	u8 __iomem *gtcfr;
	__be16 __iomem *gtmdr;
	__be16 __iomem *gtpsr;
	__be16 __iomem *gtcnr;
	__be16 __iomem *gtrfr;
	__be16 __iomem *gtevr;
};

extern struct gtm_timer *gtm_get_timer16(void);
extern struct gtm_timer *gtm_get_specific_timer16(struct gtm *gtm,
						  unsigned int timer);
extern void gtm_put_timer16(struct gtm_timer *tmr);
extern int gtm_set_timer16(struct gtm_timer *tmr, unsigned long usec,
			     bool reload);
extern int gtm_set_exact_timer16(struct gtm_timer *tmr, u16 usec,
				 bool reload);
extern void gtm_stop_timer16(struct gtm_timer *tmr);
extern void gtm_ack_timer16(struct gtm_timer *tmr, u16 events);

#endif /* __ASM_FSL_GTM_H */
