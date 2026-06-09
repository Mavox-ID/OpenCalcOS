/* sonet.h - SONET/SHD physical layer control */
#ifndef BEEP_SONET_H
#define BEEP_SONET_H


#include <beep/atomic.h>
#include <uapi/beep/sonet.h>

struct k_sonet_stats {
#define __HANDLE_ITEM(i) atomic_t i
	__SONET_ITEMS
#undef __HANDLE_ITEM
};

extern void sonet_copy_stats(struct k_sonet_stats *from,struct sonet_stats *to);
extern void sonet_subtract_stats(struct k_sonet_stats *from,
    struct sonet_stats *to);

#endif
