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
#ifndef __ARCH_ASM_MACH_OMAP2_CM2XXX_H
#define __ARCH_ASM_MACH_OMAP2_CM2XXX_H

#include "prcm-common.h"
#include "cm2xxx_3xxx.h"

#define OMAP2420_CM_REGADDR(module, reg)				\
			OMAP2_L4_IO_ADDRESS(OMAP2420_CM_BASE + (module) + (reg))
#define OMAP2430_CM_REGADDR(module, reg)				\
			OMAP2_L4_IO_ADDRESS(OMAP2430_CM_BASE + (module) + (reg))

/*
 * Module specific CM register offsets from CM_BASE + domain offset
 * Use cm_{read,write}_mod_reg() with these registers.
 * These register offsets generally appear in more than one PRCM submodule.
 */

/* OMAP2-specific register offsets */

#define OMAP24XX_CM_FCLKEN2				0x0004
#define OMAP24XX_CM_ICLKEN4				0x001c
#define OMAP24XX_CM_AUTOIDLE4				0x003c
#define OMAP24XX_CM_IDLEST4				0x002c

/* CM_IDLEST bit field values to indicate deasserted IdleReq */

#define OMAP24XX_CM_IDLEST_VAL				0


/* Clock management domain register get/set */

#ifndef __ASSEMBLER__

extern void omap2xxx_cm_clkdm_enable_hwsup(s16 module, u32 mask);
extern void omap2xxx_cm_clkdm_disable_hwsup(s16 module, u32 mask);

extern void omap2xxx_cm_set_dpll_disable_autoidle(void);
extern void omap2xxx_cm_set_dpll_auto_low_power_stop(void);

extern void omap2xxx_cm_set_apll54_disable_autoidle(void);
extern void omap2xxx_cm_set_apll54_auto_low_power_stop(void);
extern void omap2xxx_cm_set_apll96_disable_autoidle(void);
extern void omap2xxx_cm_set_apll96_auto_low_power_stop(void);

extern bool omap2xxx_cm_is_clkdm_in_hwsup(s16 module, u32 mask);
extern int omap2xxx_cm_wait_module_ready(s16 prcm_mod, u8 idlest_id,
					 u8 idlest_shift);
extern int omap2xxx_cm_split_idlest_reg(void __iomem *idlest_reg,
					s16 *prcm_inst, u8 *idlest_reg_id);

extern int __init omap2xxx_cm_init(void);

#endif

#endif
