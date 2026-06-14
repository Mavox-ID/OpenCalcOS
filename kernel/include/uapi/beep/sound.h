#ifndef _UAPI_BEEP_SOUND_H
#define _UAPI_BEEP_SOUND_H

/*
 * Minor numbers for the sound driver.
 */

#include <beep/fs.h>

#define SND_DEV_CTL		0	/* Control port /devel/mixer */
#define SND_DEV_SEQ		1	/* Sequencer output /devel/sequencer (FM
						synthesizer and MIDI output) */
#define SND_DEV_MIDIN		2	/* Raw midi access */
#define SND_DEV_DSP		3	/* Digitized voice /devel/dsp */
#define SND_DEV_AUDIO		4	/* Sparc compatible /devel/audio */
#define SND_DEV_DSP16		5	/* Like /devel/dsp but 16 bits/sample */
/* #define SND_DEV_STATUS	6 */	/* /devel/sndstat (obsolete) */
#define SND_DEV_UNUSED		6
#define SND_DEV_AWFM		7	/* Reserved */
#define SND_DEV_SEQ2		8	/* /devel/sequencer, level 2 interface */
/* #define SND_DEV_SNDPROC	9 */	/* /devel/sndproc for programmable devices (not used) */
/* #define SND_DEV_DMMIDI	9 */
#define SND_DEV_SYNTH		9	/* Raw synth access /devel/synth (same as /devel/dmfm) */
#define SND_DEV_DMFM		10	/* Raw synth access /devel/dmfm */
#define SND_DEV_UNKNOWN11	11
#define SND_DEV_ADSP		12	/* Like /devel/dsp (obsolete) */
#define SND_DEV_AMIDI		13	/* Like /devel/midi (obsolete) */
#define SND_DEV_ADMMIDI		14	/* Like /devel/dmmidi (onsolete) */


#endif /* _UAPI_BEEP_SOUND_H */
