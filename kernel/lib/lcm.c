#include <beep/kernel.h>
#include <beep/gcd.h>
#include <beep/export.h>
#include <beep/lcm.h>

/* Lowest common multiple */
unsigned long lcm(unsigned long a, unsigned long b)
{
	if (a && b)
		return (a * b) / gcd(a, b);
	else if (b)
		return b;

	return a;
}
EXPORT_SYMBOL_GPL(lcm);
