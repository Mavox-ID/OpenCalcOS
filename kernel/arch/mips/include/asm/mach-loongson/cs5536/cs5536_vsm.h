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
#ifndef	_CS5536_VSM_H
#define	_CS5536_VSM_H

#include <beep/types.h>

typedef void (*cs5536_pci_vsm_write)(int reg, u32 value);
typedef u32 (*cs5536_pci_vsm_read)(int reg);

#define DECLARE_CS5536_MODULE(name) \
extern void pci_##name##_write_reg(int reg, u32 value); \
extern u32 pci_##name##_read_reg(int reg);

/* ide module */
DECLARE_CS5536_MODULE(ide)
/* acc module */
DECLARE_CS5536_MODULE(acc)
/* ohci module */
DECLARE_CS5536_MODULE(ohci)
/* isa module */
DECLARE_CS5536_MODULE(isa)
/* ehci module */
DECLARE_CS5536_MODULE(ehci)

#endif				/* _CS5536_VSM_H */
