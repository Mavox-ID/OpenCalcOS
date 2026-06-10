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
/*
 * This file is licensed under the GPL2 license.
 *
 *#############################################################################
 * GPL
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 *#############################################################################
 */

#ifndef _SYNAPTICS_RMI4_H_INCLUDED_
#define _SYNAPTICS_RMI4_H_INCLUDED_

/**
 * struct synaptics_rmi4_platform_data - contains the rmi4 platform data
 * @irq_number: irq number
 * @irq_type: irq type
 * @x flip: x flip flag
 * @y flip: y flip flag
 *
 * This structure gives platform data for rmi4.
 */
struct synaptics_rmi4_platform_data {
	int irq_number;
	int irq_type;
	bool x_flip;
	bool y_flip;
};

#endif
