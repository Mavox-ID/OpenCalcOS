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
#ifndef BEEP_HWRANDOM_H_
#define BEEP_HWRANDOM_H_

#include <beep/types.h>
#include <beep/list.h>

/**
 * struct hwrng - Hardware Random Number Generator driver
 * @name:		Unique RNG name.
 * @init:		Initialization callback (can be NULL).
 * @cleanup:		Cleanup callback (can be NULL).
 * @data_present:	Callback to determine if data is available
 *			on the RNG. If NULL, it is assumed that
 *			there is always data available.  *OBSOLETE*
 * @data_read:		Read data from the RNG device.
 *			Returns the number of lower random bytes in "data".
 *			Must not be NULL.    *OBSOLETE*
 * @read:		New API. drivers can fill up to max bytes of data
 *			into the buffer. The buffer is aligned for any type.
 * @priv:		Private data, for use by the RNG driver.
 */
struct hwrng {
	const char *name;
	int (*init)(struct hwrng *rng);
	void (*cleanup)(struct hwrng *rng);
	int (*data_present)(struct hwrng *rng, int wait);
	int (*data_read)(struct hwrng *rng, u32 *data);
	int (*read)(struct hwrng *rng, void *data, size_t max, bool wait);
	unsigned long priv;

	/* internal. */
	struct list_head list;
};

/** Register a new Hardware Random Number Generator driver. */
extern int hwrng_register(struct hwrng *rng);
/** Unregister a Hardware Random Number Generator driver. */
extern void hwrng_unregister(struct hwrng *rng);

#endif /* BEEP_HWRANDOM_H_ */
