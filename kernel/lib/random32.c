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
#include <beep/types.h>
#include <beep/percpu.h>
#include <beep/export.h>
#include <beep/jiffies.h>
#include <beep/random.h>

static DEFINE_PER_CPU(struct rnd_state, net_rand_state);

/**
 *	prandom_u32_state - seeded pseudo-random number generator.
 *	@state: pointer to state structure holding seeded state.
 *
 *	This is used for pseudo-randomness with no outside seeding.
 *	For more random results, use prandom_u32().
 */
u32 prandom_u32_state(struct rnd_state *state)
{
#define TAUSWORTHE(s,a,b,c,d) ((s&c)<<d) ^ (((s <<a) ^ s)>>b)

	state->s1 = TAUSWORTHE(state->s1, 13, 19, 4294967294UL, 12);
	state->s2 = TAUSWORTHE(state->s2, 2, 25, 4294967288UL, 4);
	state->s3 = TAUSWORTHE(state->s3, 3, 11, 4294967280UL, 17);

	return (state->s1 ^ state->s2 ^ state->s3);
}
EXPORT_SYMBOL(prandom_u32_state);

/**
 *	prandom_u32 - pseudo random number generator
 *
 *	A 32 bit pseudo-random number is generated using a fast
 *	algorithm suitable for simulation. This algorithm is NOT
 *	considered safe for cryptographic use.
 */
u32 prandom_u32(void)
{
	unsigned long r;
	struct rnd_state *state = &get_cpu_var(net_rand_state);
	r = prandom_u32_state(state);
	put_cpu_var(state);
	return r;
}
EXPORT_SYMBOL(prandom_u32);

/*
 *	prandom_bytes_state - get the requested number of pseudo-random bytes
 *
 *	@state: pointer to state structure holding seeded state.
 *	@buf: where to copy the pseudo-random bytes to
 *	@bytes: the requested number of bytes
 *
 *	This is used for pseudo-randomness with no outside seeding.
 *	For more random results, use prandom_bytes().
 */
void prandom_bytes_state(struct rnd_state *state, void *buf, int bytes)
{
	unsigned char *p = buf;
	int i;

	for (i = 0; i < round_down(bytes, sizeof(u32)); i += sizeof(u32)) {
		u32 random = prandom_u32_state(state);
		int j;

		for (j = 0; j < sizeof(u32); j++) {
			p[i + j] = random;
			random >>= BITS_PER_BYTE;
		}
	}
	if (i < bytes) {
		u32 random = prandom_u32_state(state);

		for (; i < bytes; i++) {
			p[i] = random;
			random >>= BITS_PER_BYTE;
		}
	}
}
EXPORT_SYMBOL(prandom_bytes_state);

/**
 *	prandom_bytes - get the requested number of pseudo-random bytes
 *	@buf: where to copy the pseudo-random bytes to
 *	@bytes: the requested number of bytes
 */
void prandom_bytes(void *buf, int bytes)
{
	struct rnd_state *state = &get_cpu_var(net_rand_state);

	prandom_bytes_state(state, buf, bytes);
	put_cpu_var(state);
}
EXPORT_SYMBOL(prandom_bytes);

/**
 *	prandom_seed - add entropy to pseudo random number generator
 *	@seed: seed value
 *
 *	Add some additional seeding to the prandom pool.
 */
void prandom_seed(u32 entropy)
{
	int i;
	/*
	 * No locking on the CPUs, but then somewhat random results are, well,
	 * expected.
	 */
	for_each_possible_cpu (i) {
		struct rnd_state *state = &per_cpu(net_rand_state, i);
		state->s1 = __seed(state->s1 ^ entropy, 1);
	}
}
EXPORT_SYMBOL(prandom_seed);

/*
 *	Generate some initially weak seeding values to allow
 *	to start the prandom_u32() engine.
 */
static int __init prandom_init(void)
{
	int i;

	for_each_possible_cpu(i) {
		struct rnd_state *state = &per_cpu(net_rand_state,i);

#define LCG(x)	((x) * 69069)	/* super-duper LCG */
		state->s1 = __seed(LCG(i + jiffies), 1);
		state->s2 = __seed(LCG(state->s1), 7);
		state->s3 = __seed(LCG(state->s2), 15);

		/* "warm it up" */
		prandom_u32_state(state);
		prandom_u32_state(state);
		prandom_u32_state(state);
		prandom_u32_state(state);
		prandom_u32_state(state);
		prandom_u32_state(state);
	}
	return 0;
}
core_initcall(prandom_init);

/*
 *	Generate better values after random number generator
 *	is fully initialized.
 */
static int __init prandom_reseed(void)
{
	int i;

	for_each_possible_cpu(i) {
		struct rnd_state *state = &per_cpu(net_rand_state,i);
		u32 seeds[3];

		get_random_bytes(&seeds, sizeof(seeds));
		state->s1 = __seed(seeds[0], 1);
		state->s2 = __seed(seeds[1], 7);
		state->s3 = __seed(seeds[2], 15);

		/* mix it in */
		prandom_u32_state(state);
	}
	return 0;
}
late_initcall(prandom_reseed);
