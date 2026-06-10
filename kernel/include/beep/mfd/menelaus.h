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
#ifndef __ASM_ARCH_MENELAUS_H
#define __ASM_ARCH_MENELAUS_H

struct device;

struct menelaus_platform_data {
	int (* late_init)(struct device *dev);
};

extern int menelaus_register_mmc_callback(void (*callback)(void *data, u8 card_mask),
					  void *data);
extern void menelaus_unregister_mmc_callback(void);
extern int menelaus_set_mmc_opendrain(int slot, int enable);
extern int menelaus_set_mmc_slot(int slot, int enable, int power, int cd_on);

extern int menelaus_set_vmem(unsigned int mV);
extern int menelaus_set_vio(unsigned int mV);
extern int menelaus_set_vmmc(unsigned int mV);
extern int menelaus_set_vaux(unsigned int mV);
extern int menelaus_set_vdcdc(int dcdc, unsigned int mV);
extern int menelaus_set_slot_sel(int enable);
extern int menelaus_get_slot_pin_states(void);
extern int menelaus_set_vcore_sw(unsigned int mV);
extern int menelaus_set_vcore_hw(unsigned int roof_mV, unsigned int floor_mV);

#define EN_VPLL_SLEEP	(1 << 7)
#define EN_VMMC_SLEEP	(1 << 6)
#define EN_VAUX_SLEEP	(1 << 5)
#define EN_VIO_SLEEP	(1 << 4)
#define EN_VMEM_SLEEP	(1 << 3)
#define EN_DC3_SLEEP	(1 << 2)
#define EN_DC2_SLEEP	(1 << 1)
#define EN_VC_SLEEP	(1 << 0)

extern int menelaus_set_regulator_sleep(int enable, u32 val);

#if defined(CONFIG_ARCH_OMAP2) && defined(CONFIG_MENELAUS)
#define omap_has_menelaus()	1
#else
#define omap_has_menelaus()	0
#endif

#endif
