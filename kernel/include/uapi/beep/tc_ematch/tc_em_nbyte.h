#ifndef __BEEP_TC_EM_NBYTE_H
#define __BEEP_TC_EM_NBYTE_H

#include <beep/types.h>
#include <beep/pkt_cls.h>

struct tcf_em_nbyte {
	__u16		off;
	__u16		len:12;
	__u8		layer:4;
};

#endif
