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
#include <beep/kdb.h>

/*
 * All kdb shell command call backs receive argc and argv, where
 * argv[0] is the command the end user typed
 */
static int kdb_hello_cmd(int argc, const char **argv)
{
	if (argc > 1)
		return KDB_ARGCOUNT;

	if (argc)
		kdb_printf("Hello %s.\n", argv[1]);
	else
		kdb_printf("Hello world!\n");

	return 0;
}


static int __init kdb_hello_cmd_init(void)
{
	/*
	 * Registration of a dynamically added kdb command is done with
	 * kdb_register() with the arguments being:
	 *   1: The name of the shell command
	 *   2: The function that processes the command
	 *   3: Description of the usage of any arguments
	 *   4: Descriptive text when you run help
	 *   5: Number of characters to complete the command
	 *      0 == type the whole command
	 *      1 == match both "g" and "go" for example
	 */
	kdb_register("hello", kdb_hello_cmd, "[string]",
		     "Say Hello World or Hello [string]", 0);
	return 0;
}

static void __exit kdb_hello_cmd_exit(void)
{
	kdb_unregister("hello");
}

module_init(kdb_hello_cmd_init);
module_exit(kdb_hello_cmd_exit);

MODULE_AUTHOR("WindRiver");
MODULE_DESCRIPTION("KDB example to add a hello command");
MODULE_LICENSE("GPL");
