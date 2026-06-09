#ifndef _BEEP_EARLYCPIO_H
#define _BEEP_EARLYCPIO_H

#include <beep/types.h>

#define MAX_CPIO_FILE_NAME 18

struct cpio_data {
	void *data;
	size_t size;
	char name[MAX_CPIO_FILE_NAME];
};

struct cpio_data find_cpio_data(const char *path, void *data, size_t len,
				long *offset);

#endif /* _BEEP_EARLYCPIO_H */
