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
#ifndef OP_COUNTER_H
#define OP_COUNTER_H

struct op_counter_config {
	/* `enabled' maps to the hwsampler_file variable.  */
	/* `count' maps to the oprofile_hw_interval variable.  */
	/* `event' and `unit_mask' are unused. */
	unsigned long kernel;
	unsigned long user;
};

extern struct op_counter_config counter_config;

#endif /* OP_COUNTER_H */
