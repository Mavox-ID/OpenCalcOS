#if defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
PHDRS
{
  text PT_LOAD FILEHDR PHDRS FLAGS (7);
  data PT_LOAD FLAGS (7);
}
#ifdef CONFIG_SUN3
#include "vmbeep-sun3.lds"
#else
#include "vmbeep-std.lds"
#endif
#else
#include "vmbeep-nommu.lds"
#endif
