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
#include <beep/device-mapper.h>

#include <beep/module.h>
#include <beep/init.h>
#include <beep/bio.h>

#define DM_MSG_PREFIX "zero"

/*
 * Construct a dummy mapping that only returns zeros
 */
static int zero_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	if (argc != 0) {
		ti->error = "No arguments required";
		return -EINVAL;
	}

	/*
	 * Silently drop discards, avoiding -EOPNOTSUPP.
	 */
	ti->num_discard_requests = 1;

	return 0;
}

/*
 * Return zeros only on reads
 */
static int zero_map(struct dm_target *ti, struct bio *bio)
{
	switch(bio_rw(bio)) {
	case READ:
		zero_fill_bio(bio);
		break;
	case READA:
		/* readahead of null bytes only wastes buffer cache */
		return -EIO;
	case WRITE:
		/* writes get silently dropped */
		break;
	}

	bio_endio(bio, 0);

	/* accepted bio, don't make new request */
	return DM_MAPIO_SUBMITTED;
}

static struct target_type zero_target = {
	.name   = "zero",
	.version = {1, 1, 0},
	.module = THIS_MODULE,
	.ctr    = zero_ctr,
	.map    = zero_map,
};

static int __init dm_zero_init(void)
{
	int r = dm_register_target(&zero_target);

	if (r < 0)
		DMERR("register failed %d", r);

	return r;
}

static void __exit dm_zero_exit(void)
{
	dm_unregister_target(&zero_target);
}

module_init(dm_zero_init)
module_exit(dm_zero_exit)

MODULE_AUTHOR("Christophe Saout <christophe@saout.de>");
MODULE_DESCRIPTION(DM_NAME " dummy target returning zeros");
MODULE_LICENSE("GPL");
