/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _PPC_MEDIABAY_H
#define _PPC_MEDIABAY_H

#ifdef __KERNEL__

#define MB_FD		0	/* media bay contains floppy drive (automatic eject ?) */
#define MB_FD1		1	/* media bay contains floppy drive (manual eject ?) */
#define MB_SOUND	2	/* sound device ? */
#define MB_CD		3	/* media bay contains ATA drive such as CD or ZIP */
#define MB_PCI		5	/* media bay contains a PCI device */
#define MB_POWER	6	/* media bay contains a Power device (???) */
#define MB_NO		7	/* media bay contains nothing */

struct macio_dev;

#ifdef CONFIG_PMAC_MEDIABAY

/* Check the content type of the bay, returns MB_NO if the bay is still
 * transitionning
 */
extern int check_media_bay(struct macio_dev *bay);

/* The ATA driver uses the calls below to temporarily hold on the
 * media bay callbacks while initializing the interface
 */
extern void lock_media_bay(struct macio_dev *bay);
extern void unlock_media_bay(struct macio_dev *bay);

#else

static inline int check_media_bay(struct macio_dev *bay)
{
	return MB_NO;
}

static inline void lock_media_bay(struct macio_dev *bay) { }
static inline void unlock_media_bay(struct macio_dev *bay) { }

#endif

#endif /* __KERNEL__ */
#endif /* _PPC_MEDIABAY_H */
