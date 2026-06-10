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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/interrupt.h>
#include <beep/seq_file.h>

#include <asm/cacheflush.h>
#include <asm/cp15.h>
#include <asm/fiq.h>
#include <asm/irq.h>
#include <asm/traps.h>

static unsigned long no_fiq_insn;

/* Default reacquire function
 * - we always relinquish FIQ control
 * - we always reacquire FIQ control
 */
static int fiq_def_op(void *ref, int relinquish)
{
	if (!relinquish)
		set_fiq_handler(&no_fiq_insn, sizeof(no_fiq_insn));

	return 0;
}

static struct fiq_handler default_owner = {
	.name	= "default",
	.fiq_op = fiq_def_op,
};

static struct fiq_handler *current_fiq = &default_owner;

int show_fiq_list(struct seq_file *p, int prec)
{
	if (current_fiq != &default_owner)
		seq_printf(p, "%*s:              %s\n", prec, "FIQ",
			current_fiq->name);

	return 0;
}

void set_fiq_handler(void *start, unsigned int length)
{
#if defined(CONFIG_CPU_USE_DOMAINS)
	memcpy((void *)0xffff001c, start, length);
#else
	memcpy(vectors_page + 0x1c, start, length);
#endif
	flush_icache_range(0xffff001c, 0xffff001c + length);
	if (!vectors_high())
		flush_icache_range(0x1c, 0x1c + length);
}

int claim_fiq(struct fiq_handler *f)
{
	int ret = 0;

	if (current_fiq) {
		ret = -EBUSY;

		if (current_fiq->fiq_op != NULL)
			ret = current_fiq->fiq_op(current_fiq->dev_id, 1);
	}

	if (!ret) {
		f->next = current_fiq;
		current_fiq = f;
	}

	return ret;
}

void release_fiq(struct fiq_handler *f)
{
	if (current_fiq != f) {
		printk(KERN_ERR "%s FIQ trying to release %s FIQ\n",
		       f->name, current_fiq->name);
		dump_stack();
		return;
	}

	do
		current_fiq = current_fiq->next;
	while (current_fiq->fiq_op(current_fiq->dev_id, 0));
}

static int fiq_start;

void enable_fiq(int fiq)
{
	enable_irq(fiq + fiq_start);
}

void disable_fiq(int fiq)
{
	disable_irq(fiq + fiq_start);
}

EXPORT_SYMBOL(set_fiq_handler);
EXPORT_SYMBOL(__set_fiq_regs);	/* defined in fiqasm.S */
EXPORT_SYMBOL(__get_fiq_regs);	/* defined in fiqasm.S */
EXPORT_SYMBOL(claim_fiq);
EXPORT_SYMBOL(release_fiq);
EXPORT_SYMBOL(enable_fiq);
EXPORT_SYMBOL(disable_fiq);

void __init init_FIQ(int start)
{
	no_fiq_insn = *(unsigned long *)0xffff001c;
	fiq_start = start;
}
