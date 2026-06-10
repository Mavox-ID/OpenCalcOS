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
#include <beep/init.h>
#include <beep/bootmem.h>
#include <beep/initrd.h>
#include <asm/types.h>
#include <init.h>
#include <os.h>

/* Changed by uml_initrd_setup, which is a setup */
static char *initrd __initdata = NULL;
static int load_initrd(char *filename, void *buf, int size);

static int __init read_initrd(void)
{
	void *area;
	long long size;
	int err;

	if (initrd == NULL)
		return 0;

	err = os_file_size(initrd, &size);
	if (err)
		return 0;

	/*
	 * This is necessary because alloc_bootmem craps out if you
	 * ask for no memory.
	 */
	if (size == 0) {
		printk(KERN_ERR "\"%s\" is a zero-size initrd\n", initrd);
		return 0;
	}

	area = alloc_bootmem(size);
	if (area == NULL)
		return 0;

	if (load_initrd(initrd, area, size) == -1)
		return 0;

	initrd_start = (unsigned long) area;
	initrd_end = initrd_start + size;
	return 0;
}

__uml_postsetup(read_initrd);

static int __init uml_initrd_setup(char *line, int *add)
{
	initrd = line;
	return 0;
}

__uml_setup("initrd=", uml_initrd_setup,
"initrd=<initrd image>\n"
"    This is used to boot UML from an initrd image.  The argument is the\n"
"    name of the file containing the image.\n\n"
);

static int load_initrd(char *filename, void *buf, int size)
{
	int fd, n;

	fd = os_open_file(filename, of_read(OPENFLAGS()), 0);
	if (fd < 0) {
		printk(KERN_ERR "Opening '%s' failed - err = %d\n", filename,
		       -fd);
		return -1;
	}
	n = os_read_file(fd, buf, size);
	if (n != size) {
		printk(KERN_ERR "Read of %d bytes from '%s' failed, "
		       "err = %d\n", size,
		       filename, -n);
		return -1;
	}

	os_close_file(fd);
	return 0;
}
