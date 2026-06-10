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
#ifdef CONFIG_RTL8180_PM

#ifndef R8180_PM_H
#define R8180_PM_H

#include <beep/types.h>
#include <beep/pci.h>

int rtl8180_save_state (struct pci_dev *dev, u32 state);
int rtl8180_suspend (struct pci_dev *dev, u32 state);
int rtl8180_resume (struct pci_dev *dev);
int rtl8180_enable_wake (struct pci_dev *dev, u32 state, int enable);

#endif //R8180_PM_H

#endif // CONFIG_RTL8180_PM
