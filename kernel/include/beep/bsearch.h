#ifndef _BEEP_BSEARCH_H
#define _BEEP_BSEARCH_H

#include <beep/types.h>

void *bsearch(const void *key, const void *base, size_t num, size_t size,
	      int (*cmp)(const void *key, const void *elt));

#endif /* _BEEP_BSEARCH_H */
