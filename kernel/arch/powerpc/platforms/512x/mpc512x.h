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
#ifndef __MPC512X_H__
#define __MPC512X_H__
extern void __init mpc512x_init_IRQ(void);
extern void __init mpc512x_init(void);
extern int __init mpc5121_clk_init(void);
void __init mpc512x_declare_of_platform_devices(void);
extern void mpc512x_restart(char *cmd);

#if defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)
void mpc512x_init_diu(void);
void mpc512x_setup_diu(void);
#else
#define mpc512x_init_diu NULL
#define mpc512x_setup_diu NULL
#endif

#endif				/* __MPC512X_H__ */
