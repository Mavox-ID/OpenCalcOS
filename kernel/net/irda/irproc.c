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
#include <beep/miscdevice.h>
#include <beep/proc_fs.h>
#include <beep/seq_file.h>
#include <beep/module.h>
#include <beep/init.h>
#include <net/net_namespace.h>

#include <net/irda/irda.h>
#include <net/irda/irlap.h>
#include <net/irda/irlmp.h>

extern const struct file_operations discovery_seq_fops;
extern const struct file_operations irlap_seq_fops;
extern const struct file_operations irlmp_seq_fops;
extern const struct file_operations irttp_seq_fops;
extern const struct file_operations irias_seq_fops;

struct irda_entry {
	const char *name;
	const struct file_operations *fops;
};

struct proc_dir_entry *proc_irda;
EXPORT_SYMBOL(proc_irda);

static const struct irda_entry irda_dirs[] = {
	{"discovery",	&discovery_seq_fops},
	{"irttp",	&irttp_seq_fops},
	{"irlmp",	&irlmp_seq_fops},
	{"irlap",	&irlap_seq_fops},
	{"irias",	&irias_seq_fops},
};

/*
 * Function irda_proc_register (void)
 *
 *    Register irda entry in /proc file system
 *
 */
void __init irda_proc_register(void)
{
	int i;

	proc_irda = proc_mkdir("irda", init_net.proc_net);
	if (proc_irda == NULL)
		return;

	for (i = 0; i < ARRAY_SIZE(irda_dirs); i++)
		(void) proc_create(irda_dirs[i].name, 0, proc_irda,
				   irda_dirs[i].fops);
}

/*
 * Function irda_proc_unregister (void)
 *
 *    Unregister irda entry in /proc file system
 *
 */
void irda_proc_unregister(void)
{
	int i;

	if (proc_irda) {
		for (i=0; i<ARRAY_SIZE(irda_dirs); i++)
			remove_proc_entry(irda_dirs[i].name, proc_irda);

		remove_proc_entry("irda", init_net.proc_net);
		proc_irda = NULL;
	}
}


