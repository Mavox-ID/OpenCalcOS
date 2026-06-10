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
#ifndef __BFIN_SPORT_H__
#define __BFIN_SPORT_H__


#include <beep/types.h>
#include <uapi/asm/bfin_sport.h>

/*
 * All Blackfin system MMRs are padded to 32bits even if the register
 * itself is only 16bits.  So use a helper macro to streamline this.
 */
#define __BFP(m) u16 m; u16 __pad_##m
struct sport_register {
	__BFP(tcr1);
	__BFP(tcr2);
	__BFP(tclkdiv);
	__BFP(tfsdiv);
	union {
		u32 tx32;
		u16 tx16;
	};
	u32 __pad_tx;
	union {
		u32 rx32;	/* use the anomaly wrapper below */
		u16 rx16;
	};
	u32 __pad_rx;
	__BFP(rcr1);
	__BFP(rcr2);
	__BFP(rclkdiv);
	__BFP(rfsdiv);
	__BFP(stat);
	__BFP(chnl);
	__BFP(mcmc1);
	__BFP(mcmc2);
	u32 mtcs0;
	u32 mtcs1;
	u32 mtcs2;
	u32 mtcs3;
	u32 mrcs0;
	u32 mrcs1;
	u32 mrcs2;
	u32 mrcs3;
};
#undef __BFP

struct bfin_snd_platform_data {
	const unsigned short *pin_req;
};

#define bfin_read_sport_rx32(base) \
({ \
	struct sport_register *__mmrs = (void *)base; \
	u32 __ret; \
	unsigned long flags; \
	if (ANOMALY_05000473) \
		local_irq_save(flags); \
	__ret = __mmrs->rx32; \
	if (ANOMALY_05000473) \
		local_irq_restore(flags); \
	__ret; \
})

#endif
