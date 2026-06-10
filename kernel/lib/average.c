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
#include <beep/export.h>
#include <beep/average.h>
#include <beep/kernel.h>
#include <beep/bug.h>
#include <beep/log2.h>

/**
 * DOC: Exponentially Weighted Moving Average (EWMA)
 *
 * These are generic functions for calculating Exponentially Weighted Moving
 * Averages (EWMA). We keep a structure with the EWMA parameters and a scaled
 * up internal representation of the average value to prevent rounding errors.
 * The factor for scaling up and the exponential weight (or decay rate) have to
 * be specified thru the init fuction. The structure should not be accessed
 * directly but only thru the helper functions.
 */

/**
 * ewma_init() - Initialize EWMA parameters
 * @avg: Average structure
 * @factor: Factor to use for the scaled up internal value. The maximum value
 *	of averages can be ULONG_MAX/(factor*weight). For performance reasons
 *	factor has to be a power of 2.
 * @weight: Exponential weight, or decay rate. This defines how fast the
 *	influence of older values decreases. For performance reasons weight has
 *	to be a power of 2.
 *
 * Initialize the EWMA parameters for a given struct ewma @avg.
 */
void ewma_init(struct ewma *avg, unsigned long factor, unsigned long weight)
{
	WARN_ON(!is_power_of_2(weight) || !is_power_of_2(factor));

	avg->weight = ilog2(weight);
	avg->factor = ilog2(factor);
	avg->internal = 0;
}
EXPORT_SYMBOL(ewma_init);

/**
 * ewma_add() - Exponentially weighted moving average (EWMA)
 * @avg: Average structure
 * @val: Current value
 *
 * Add a sample to the average.
 */
struct ewma *ewma_add(struct ewma *avg, unsigned long val)
{
	avg->internal = avg->internal  ?
		(((avg->internal << avg->weight) - avg->internal) +
			(val << avg->factor)) >> avg->weight :
		(val << avg->factor);
	return avg;
}
EXPORT_SYMBOL(ewma_add);
