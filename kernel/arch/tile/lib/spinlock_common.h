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
/*
 * The mfspr in __spinlock_relax() is 5 or 6 cycles plus 2 for loop
 * overhead.
 */
#ifdef __tilegx__
#define CYCLES_PER_RELAX_LOOP 7
#else
#define CYCLES_PER_RELAX_LOOP 8
#endif

/*
 * Idle the core for CYCLES_PER_RELAX_LOOP * iterations cycles.
 */
static inline void
relax(int iterations)
{
	for (/*above*/; iterations > 0; iterations--)
		__insn_mfspr(SPR_PASS);
	barrier();
}

/* Perform bounded exponential backoff.*/
static void delay_backoff(int iterations)
{
	u32 exponent, loops;

	/*
	 * 2^exponent is how many times we go around the loop,
	 * which takes 8 cycles.  We want to start with a 16- to 31-cycle
	 * loop, so we need to go around minimum 2 = 2^1 times, so we
	 * bias the original value up by 1.
	 */
	exponent = iterations + 1;

	/*
	 * Don't allow exponent to exceed 7, so we have 128 loops,
	 * or 1,024 (to 2,047) cycles, as our maximum.
	 */
	if (exponent > 8)
		exponent = 8;

	loops = 1 << exponent;

	/* Add a randomness factor so two cpus never get in lock step. */
	loops += __insn_crc32_32(stack_pointer, get_cycles_low()) &
		(loops - 1);

	relax(loops);
}
