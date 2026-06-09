#ifndef _BEEP_BH_H
#define _BEEP_BH_H

extern void local_bh_disable(void);
extern void _local_bh_enable(void);
extern void local_bh_enable(void);
extern void local_bh_enable_ip(unsigned long ip);

#endif /* _BEEP_BH_H */
