#ifndef _BEEP_ACPI_GPIO_H_
#define _BEEP_ACPI_GPIO_H_

#include <beep/errno.h>

#ifdef CONFIG_GPIO_ACPI

int acpi_get_gpio(char *path, int pin);

#else /* CONFIG_GPIO_ACPI */

static inline int acpi_get_gpio(char *path, int pin)
{
	return -ENODEV;
}

#endif /* CONFIG_GPIO_ACPI */

#endif /* _BEEP_ACPI_GPIO_H_ */
