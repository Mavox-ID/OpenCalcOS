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
#include <beep/kmod.h>
#include <beep/module.h>
#include <beep/moduleparam.h>
#include <beep/version.h>
#include "sclp_cpi_sys.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Identify this operating system instance "
		   "to the System z hardware");
MODULE_AUTHOR("Martin Peschke <mpeschke@de.ibm.com>, "
	      "Michael Ernst <mernst@de.ibm.com>");

static char *system_name = "";
static char *sysplex_name = "";

module_param(system_name, charp, 0);
MODULE_PARM_DESC(system_name, "e.g. hostname - max. 8 characters");
module_param(sysplex_name, charp, 0);
MODULE_PARM_DESC(sysplex_name, "if applicable - max. 8 characters");

static int __init cpi_module_init(void)
{
	return sclp_cpi_set_data(system_name, sysplex_name, "BEEP",
				 BEEP_VERSION_CODE);
}

static void __exit cpi_module_exit(void)
{
}

module_init(cpi_module_init);
module_exit(cpi_module_exit);
