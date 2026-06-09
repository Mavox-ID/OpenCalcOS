#include <beep/kernel.h>
#include <beep/errno.h>

long compat_ni_syscall(void)
{
	return -ENOSYS;
}
