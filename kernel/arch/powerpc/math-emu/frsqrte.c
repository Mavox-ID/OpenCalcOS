#include <beep/types.h>
#include <beep/errno.h>
#include <asm/uaccess.h>

int
frsqrte(void *frD, void *frB)
{
#ifdef DEBUG
	printk("%s: %p %p\n", __func__, frD, frB);
#endif
	return 0;
}
