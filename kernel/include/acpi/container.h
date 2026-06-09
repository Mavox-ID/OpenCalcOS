#ifndef __ACPI_CONTAINER_H
#define __ACPI_CONTAINER_H

#include <beep/kernel.h>

struct acpi_container {
	acpi_handle handle;
	unsigned long sun;
	int state;
};

#endif				/* __ACPI_CONTAINER_H */
