/*
 * This supplies .note.* sections to go into the PT_NOTE inside the vDSO text.
 * Here we can supply some information useful to userland.
 */

#include <beep/uts.h>
#include <beep/version.h>
#include <beep/elfnote.h>

ELFNOTE_START(Beep, 0, "a")
	.long BEEP_VERSION_CODE
ELFNOTE_END
