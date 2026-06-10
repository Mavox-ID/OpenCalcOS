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
#define CLPS711X_NR_IRQS	(33)
#define CLPS711X_NR_GPIO	(4 * 8 + 3)
#define CLPS711X_GPIO(prt, bit)	((prt) * 8 + (bit))

struct sys_timer;

extern void clps711x_map_io(void);
extern void clps711x_init_irq(void);
extern void clps711x_handle_irq(struct pt_regs *regs);
extern void clps711x_restart(char mode, const char *cmd);
extern struct sys_timer clps711x_timer;
