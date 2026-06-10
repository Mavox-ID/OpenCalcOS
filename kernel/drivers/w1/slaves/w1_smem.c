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
#include <asm/types.h>

#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/moduleparam.h>
#include <beep/device.h>
#include <beep/types.h>

#include "../w1.h"
#include "../w1_int.h"
#include "../w1_family.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Evgeniy Polyakov <zbr@ioremap.net>");
MODULE_DESCRIPTION("Driver for 1-wire Dallas network protocol, 64bit memory family.");

static struct w1_family w1_smem_family_01 = {
	.fid = W1_FAMILY_SMEM_01,
};

static struct w1_family w1_smem_family_81 = {
	.fid = W1_FAMILY_SMEM_81,
};

static int __init w1_smem_init(void)
{
	int err;

	err = w1_register_family(&w1_smem_family_01);
	if (err)
		return err;

	err = w1_register_family(&w1_smem_family_81);
	if (err) {
		w1_unregister_family(&w1_smem_family_01);
		return err;
	}

	return 0;
}

static void __exit w1_smem_fini(void)
{
	w1_unregister_family(&w1_smem_family_01);
	w1_unregister_family(&w1_smem_family_81);
}

module_init(w1_smem_init);
module_exit(w1_smem_fini);
