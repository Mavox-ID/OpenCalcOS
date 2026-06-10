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
#include <beep/slab.h>
#include <beep/ctype.h>
#include <beep/genhd.h>

#include "check.h"

#include "acorn.h"
#include "amiga.h"
#include "atari.h"
#include "ldm.h"
#include "mac.h"
#include "msdos.h"
#include "osf.h"
#include "sgi.h"
#include "sun.h"
#include "ibm.h"
#include "ultrix.h"
#include "efi.h"
#include "karma.h"
#include "sysv68.h"

int warn_no_part = 1; /*This is ugly: should make genhd removable media aware*/

static int (*check_part[])(struct parsed_partitions *) = {
	/*
	 * Probe partition formats with tables at disk address 0
	 * that also have an ADFS boot block at 0xdc0.
	 */
#ifdef CONFIG_ACORN_PARTITION_ICS
	adfspart_check_ICS,
#endif
#ifdef CONFIG_ACORN_PARTITION_POWERTEC
	adfspart_check_POWERTEC,
#endif
#ifdef CONFIG_ACORN_PARTITION_EESOX
	adfspart_check_EESOX,
#endif

	/*
	 * Now move on to formats that only have partition info at
	 * disk address 0xdc0.  Since these may also have stale
	 * PC/BIOS partition tables, they need to come before
	 * the msdos entry.
	 */
#ifdef CONFIG_ACORN_PARTITION_CUMANA
	adfspart_check_CUMANA,
#endif
#ifdef CONFIG_ACORN_PARTITION_ADFS
	adfspart_check_ADFS,
#endif

#ifdef CONFIG_EFI_PARTITION
	efi_partition,		/* this must come before msdos */
#endif
#ifdef CONFIG_SGI_PARTITION
	sgi_partition,
#endif
#ifdef CONFIG_LDM_PARTITION
	ldm_partition,		/* this must come before msdos */
#endif
#ifdef CONFIG_MSDOS_PARTITION
	msdos_partition,
#endif
#ifdef CONFIG_OSF_PARTITION
	osf_partition,
#endif
#ifdef CONFIG_SUN_PARTITION
	sun_partition,
#endif
#ifdef CONFIG_AMIGA_PARTITION
	amiga_partition,
#endif
#ifdef CONFIG_ATARI_PARTITION
	atari_partition,
#endif
#ifdef CONFIG_MAC_PARTITION
	mac_partition,
#endif
#ifdef CONFIG_ULTRIX_PARTITION
	ultrix_partition,
#endif
#ifdef CONFIG_IBM_PARTITION
	ibm_partition,
#endif
#ifdef CONFIG_KARMA_PARTITION
	karma_partition,
#endif
#ifdef CONFIG_SYSV68_PARTITION
	sysv68_partition,
#endif
	NULL
};

struct parsed_partitions *
check_partition(struct gendisk *hd, struct block_device *bdev)
{
	struct parsed_partitions *state;
	int i, res, err;

	state = kzalloc(sizeof(struct parsed_partitions), GFP_KERNEL);
	if (!state)
		return NULL;
	state->pp_buf = (char *)__get_free_page(GFP_KERNEL);
	if (!state->pp_buf) {
		kfree(state);
		return NULL;
	}
	state->pp_buf[0] = '\0';

	state->bdev = bdev;
	disk_name(hd, 0, state->name);
	snprintf(state->pp_buf, PAGE_SIZE, " %s:", state->name);
	if (isdigit(state->name[strlen(state->name)-1]))
		sprintf(state->name, "p");

	state->limit = disk_max_parts(hd);
	i = res = err = 0;
	while (!res && check_part[i]) {
		memset(&state->parts, 0, sizeof(state->parts));
		res = check_part[i++](state);
		if (res < 0) {
			/* We have hit an I/O error which we don't report now.
		 	* But record it, and let the others do their job.
		 	*/
			err = res;
			res = 0;
		}

	}
	if (res > 0) {
		printk(KERN_INFO "%s", state->pp_buf);

		free_page((unsigned long)state->pp_buf);
		return state;
	}
	if (state->access_beyond_eod)
		err = -ENOSPC;
	if (err)
	/* The partition is unrecognized. So report I/O errors if there were any */
		res = err;
	if (!res)
		strlcat(state->pp_buf, " unknown partition table\n", PAGE_SIZE);
	else if (warn_no_part)
		strlcat(state->pp_buf, " unable to read partition table\n", PAGE_SIZE);

	printk(KERN_INFO "%s", state->pp_buf);

	free_page((unsigned long)state->pp_buf);
	kfree(state);
	return ERR_PTR(res);
}
