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
#include "hpi_internal.h"
#include "hpidebug.h"

/* Debug level; 0 quiet; 1 informative, 2 debug, 3 verbose debug.  */
int hpi_debug_level = HPI_DEBUG_LEVEL_DEFAULT;

void hpi_debug_init(void)
{
	printk(KERN_INFO "debug start\n");
}

int hpi_debug_level_set(int level)
{
	int old_level;

	old_level = hpi_debug_level;
	hpi_debug_level = level;
	return old_level;
}

int hpi_debug_level_get(void)
{
	return hpi_debug_level;
}

void hpi_debug_message(struct hpi_message *phm, char *sz_fileline)
{
	if (phm) {
		printk(KERN_DEBUG "HPI_MSG%d,%d,%d,%d,%d\n", phm->version,
			phm->adapter_index, phm->obj_index, phm->function,
			phm->u.c.attribute);
	}

}

void hpi_debug_data(u16 *pdata, u32 len)
{
	u32 i;
	int j;
	int k;
	int lines;
	int cols = 8;

	lines = (len + cols - 1) / cols;
	if (lines > 8)
		lines = 8;

	for (i = 0, j = 0; j < lines; j++) {
		printk(KERN_DEBUG "%p:", (pdata + i));

		for (k = 0; k < cols && i < len; i++, k++)
			printk("%s%04x", k == 0 ? "" : " ", pdata[i]);

		printk("\n");
	}
}
