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
#include "cthardware.h"
#include "cthw20k1.h"
#include "cthw20k2.h"
#include <beep/bug.h>

int create_hw_obj(struct pci_dev *pci, enum CHIPTYP chip_type,
		  enum CTCARDS model, struct hw **rhw)
{
	int err;

	switch (chip_type) {
	case ATC20K1:
		err = create_20k1_hw_obj(rhw);
		break;
	case ATC20K2:
		err = create_20k2_hw_obj(rhw);
		break;
	default:
		err = -ENODEV;
		break;
	}
	if (err)
		return err;

	(*rhw)->pci = pci;
	(*rhw)->chip_type = chip_type;
	(*rhw)->model = model;

	return 0;
}

int destroy_hw_obj(struct hw *hw)
{
	int err;

	switch (hw->pci->device) {
	case 0x0005:	/* 20k1 device */
		err = destroy_20k1_hw_obj(hw);
		break;
	case 0x000B:	/* 20k2 device */
		err = destroy_20k2_hw_obj(hw);
		break;
	default:
		err = -ENODEV;
		break;
	}

	return err;
}

unsigned int get_field(unsigned int data, unsigned int field)
{
	int i;

	BUG_ON(!field);
	/* @field should always be greater than 0 */
	for (i = 0; !(field & (1 << i)); )
		i++;

	return (data & field) >> i;
}

void set_field(unsigned int *data, unsigned int field, unsigned int value)
{
	int i;

	BUG_ON(!field);
	/* @field should always be greater than 0 */
	for (i = 0; !(field & (1 << i)); )
		i++;

	*data = (*data & (~field)) | ((value << i) & field);
}

