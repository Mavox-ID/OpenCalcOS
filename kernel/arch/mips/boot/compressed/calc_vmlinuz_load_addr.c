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
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	unsigned long long vmbeep_size, vmbeep_load_addr, vmlinuz_load_addr;
	struct stat sb;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <pathname> <vmbeep_load_addr>\n",
				argv[0]);
		return EXIT_FAILURE;
	}

	if (stat(argv[1], &sb) == -1) {
		perror("stat");
		return EXIT_FAILURE;
	}

	/* Convert hex characters to dec number */
	errno = 0;
	if (sscanf(argv[2], "%llx", &vmbeep_load_addr) != 1) {
		if (errno != 0)
			perror("sscanf");
		else
			fprintf(stderr, "No matching characters\n");

		return EXIT_FAILURE;
	}

	vmbeep_size = (uint64_t)sb.st_size;
	vmlinuz_load_addr = vmbeep_load_addr + vmbeep_size;

	/*
	 * Align with 16 bytes: "greater than that used for any standard data
	 * types by a MIPS compiler." -- See MIPS Run Beep (Second Edition).
	 */

	vmlinuz_load_addr += (16 - vmbeep_size % 16);

	printf("0x%llx\n", vmlinuz_load_addr);

	return EXIT_SUCCESS;
}
