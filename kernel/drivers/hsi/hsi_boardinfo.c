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
#include <beep/hsi/hsi.h>
#include <beep/list.h>
#include <beep/slab.h>
#include "hsi_core.h"

/*
 * hsi_board_list is only used internally by the HSI framework.
 * No one else is allowed to make use of it.
 */
LIST_HEAD(hsi_board_list);
EXPORT_SYMBOL_GPL(hsi_board_list);

/**
 * hsi_register_board_info - Register HSI clients information
 * @info: Array of HSI clients on the board
 * @len: Length of the array
 *
 * HSI clients are statically declared and registered on board files.
 *
 * HSI clients will be automatically registered to the HSI bus once the
 * controller and the port where the clients wishes to attach are registered
 * to it.
 *
 * Return -errno on failure, 0 on success.
 */
int __init hsi_register_board_info(struct hsi_board_info const *info,
							unsigned int len)
{
	struct hsi_cl_info *cl_info;

	cl_info = kzalloc(sizeof(*cl_info) * len, GFP_KERNEL);
	if (!cl_info)
		return -ENOMEM;

	for (; len; len--, info++, cl_info++) {
		cl_info->info = *info;
		list_add_tail(&cl_info->list, &hsi_board_list);
	}

	return 0;
}
