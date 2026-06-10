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
 * raid6test.c
 *
 * Test RAID-6 recovery with various algorithms
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <beep/raid/pq.h>

#define NDISKS		16	/* Including P and Q */

const char raid6_empty_zero_page[PAGE_SIZE] __attribute__((aligned(256)));
struct raid6_calls raid6_call;

char *dataptrs[NDISKS];
char data[NDISKS][PAGE_SIZE];
char recovi[PAGE_SIZE], recovj[PAGE_SIZE];

static void makedata(void)
{
	int i, j;

	for (i = 0; i < NDISKS; i++) {
		for (j = 0; j < PAGE_SIZE; j++)
			data[i][j] = rand();

		dataptrs[i] = data[i];
	}
}

static char disk_type(int d)
{
	switch (d) {
	case NDISKS-2:
		return 'P';
	case NDISKS-1:
		return 'Q';
	default:
		return 'D';
	}
}

static int test_disks(int i, int j)
{
	int erra, errb;

	memset(recovi, 0xf0, PAGE_SIZE);
	memset(recovj, 0xba, PAGE_SIZE);

	dataptrs[i] = recovi;
	dataptrs[j] = recovj;

	raid6_dual_recov(NDISKS, PAGE_SIZE, i, j, (void **)&dataptrs);

	erra = memcmp(data[i], recovi, PAGE_SIZE);
	errb = memcmp(data[j], recovj, PAGE_SIZE);

	if (i < NDISKS-2 && j == NDISKS-1) {
		/* We don't implement the DQ failure scenario, since it's
		   equivalent to a RAID-5 failure (XOR, then recompute Q) */
		erra = errb = 0;
	} else {
		printf("algo=%-8s  faila=%3d(%c)  failb=%3d(%c)  %s\n",
		       raid6_call.name,
		       i, disk_type(i),
		       j, disk_type(j),
		       (!erra && !errb) ? "OK" :
		       !erra ? "ERRB" :
		       !errb ? "ERRA" : "ERRAB");
	}

	dataptrs[i] = data[i];
	dataptrs[j] = data[j];

	return erra || errb;
}

int main(int argc, char *argv[])
{
	const struct raid6_calls *const *algo;
	const struct raid6_recov_calls *const *ra;
	int i, j;
	int err = 0;

	makedata();

	for (ra = raid6_recov_algos; *ra; ra++) {
		if ((*ra)->valid  && !(*ra)->valid())
			continue;
		raid6_2data_recov = (*ra)->data2;
		raid6_datap_recov = (*ra)->datap;

		printf("using recovery %s\n", (*ra)->name);

		for (algo = raid6_algos; *algo; algo++) {
			if (!(*algo)->valid || (*algo)->valid()) {
				raid6_call = **algo;

				/* Nuke syndromes */
				memset(data[NDISKS-2], 0xee, 2*PAGE_SIZE);

				/* Generate assumed good syndrome */
				raid6_call.gen_syndrome(NDISKS, PAGE_SIZE,
							(void **)&dataptrs);

				for (i = 0; i < NDISKS-1; i++)
					for (j = i+1; j < NDISKS; j++)
						err += test_disks(i, j);
			}
		}
		printf("\n");
	}

	printf("\n");
	/* Pick the best algorithm test */
	raid6_select_algo();

	if (err)
		printf("\n*** ERRORS FOUND ***\n");

	return err;
}
