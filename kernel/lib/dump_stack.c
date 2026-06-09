/*
 * Provide a default dump_stack() function for architectures
 * which don't implement their own.
 */

#include <beep/kernel.h>
#include <beep/export.h>

void dump_stack(void)
{
	printk(KERN_NOTICE
		"This architecture does not implement dump_stack()\n");
}

EXPORT_SYMBOL(dump_stack);
