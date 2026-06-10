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
#ifndef _BRCM_PMU_H_
#define _BRCM_PMU_H_

#include "types.h"

extern u16 si_pmu_fast_pwrup_delay(struct si_pub *sih);
extern void si_pmu_sprom_enable(struct si_pub *sih, bool enable);
extern u32 si_pmu_chipcontrol(struct si_pub *sih, uint reg, u32 mask, u32 val);
extern u32 si_pmu_regcontrol(struct si_pub *sih, uint reg, u32 mask, u32 val);
extern u32 si_pmu_alp_clock(struct si_pub *sih);
extern void si_pmu_pllupd(struct si_pub *sih);
extern u32 si_pmu_pllcontrol(struct si_pub *sih, uint reg, u32 mask, u32 val);
extern u32 si_pmu_measure_alpclk(struct si_pub *sih);

#endif /* _BRCM_PMU_H_ */
