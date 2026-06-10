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
#include <beep/module.h>
#include <beep/init.h>
#include <beep/string.h>
#include <beep/kernel.h>
#include <beep/skbuff.h>

#include <beep/isdnif.h>
#include "pcbit.h"

MODULE_DESCRIPTION("ISDN4Beep: Driver for PCBIT-T card");
MODULE_AUTHOR("Pedro Roque Marques");
MODULE_LICENSE("GPL");

static int mem[MAX_PCBIT_CARDS];
static int irq[MAX_PCBIT_CARDS];

module_param_array(mem, int, NULL, 0);
module_param_array(irq, int, NULL, 0);

static int num_boards;
struct pcbit_dev *dev_pcbit[MAX_PCBIT_CARDS];

static int __init pcbit_init(void)
{
	int board;

	num_boards = 0;

	printk(KERN_NOTICE
	       "PCBIT-D device driver v 0.5-fjpc0 19991204 - "
	       "Copyright (C) 1996 Universidade de Lisboa\n");

	if (mem[0] || irq[0])
	{
		for (board = 0; board < MAX_PCBIT_CARDS && mem[board] && irq[board]; board++)
		{
			if (!mem[board])
				mem[board] = 0xD0000;
			if (!irq[board])
				irq[board] = 5;

			if (pcbit_init_dev(board, mem[board], irq[board]) == 0)
				num_boards++;

			else
			{
				printk(KERN_WARNING
				       "pcbit_init failed for dev %d",
				       board + 1);
				return -EIO;
			}
		}
	}

	/* Hardcoded default settings detection */

	if (!num_boards)
	{
		printk(KERN_INFO
		       "Trying to detect board using default settings\n");
		if (pcbit_init_dev(0, 0xD0000, 5) == 0)
			num_boards++;
		else
			return -EIO;
	}
	return 0;
}

static void __exit pcbit_exit(void)
{
#ifdef MODULE
	int board;

	for (board = 0; board < num_boards; board++)
		pcbit_terminate(board);
	printk(KERN_NOTICE
	       "PCBIT-D module unloaded\n");
#endif
}

#ifndef MODULE
#define MAX_PARA	(MAX_PCBIT_CARDS * 2)
static int __init pcbit_setup(char *line)
{
	int i, j, argc;
	char *str;
	int ints[MAX_PARA + 1];

	str = get_options(line, MAX_PARA, ints);
	argc = ints[0];
	i = 0;
	j = 1;

	while (argc && (i < MAX_PCBIT_CARDS)) {

		if (argc) {
			mem[i]	= ints[j];
			j++; argc--;
		}

		if (argc) {
			irq[i]	= ints[j];
			j++; argc--;
		}

		i++;
	}
	return (1);
}
__setup("pcbit=", pcbit_setup);
#endif

module_init(pcbit_init);
module_exit(pcbit_exit);
