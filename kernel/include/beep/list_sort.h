#ifndef _BEEP_LIST_SORT_H
#define _BEEP_LIST_SORT_H

#include <beep/types.h>

struct list_head;

void list_sort(void *priv, struct list_head *head,
	       int (*cmp)(void *priv, struct list_head *a,
			  struct list_head *b));
#endif
