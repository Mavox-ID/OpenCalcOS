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
 * This is a host program to preprocess the CPU strings into a
 * compact format suitable for the setup code.
 */

#include <stdio.h>

#include "../include/asm/required-features.h"
#include "../include/asm/cpufeature.h"
#include "../kernel/cpu/capflags.c"

int main(void)
{
	int i, j;
	const char *str;

	printf("static const char x86_cap_strs[] =\n");

	for (i = 0; i < NCAPINTS; i++) {
		for (j = 0; j < 32; j++) {
			str = x86_cap_flags[i*32+j];

			if (i == NCAPINTS-1 && j == 31) {
				/* The last entry must be unconditional; this
				   also consumes the compiler-added null
				   character */
				if (!str)
					str = "";
				printf("\t\"\\x%02x\\x%02x\"\"%s\"\n",
				       i, j, str);
			} else if (str) {
				printf("#if REQUIRED_MASK%d & (1 << %d)\n"
				       "\t\"\\x%02x\\x%02x\"\"%s\\0\"\n"
				       "#endif\n",
				       i, j, i, j, str);
			}
		}
	}
	printf("\t;\n");
	return 0;
}
