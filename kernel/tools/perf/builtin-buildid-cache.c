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
#include "builtin.h"
#include "perf.h"
#include "util/cache.h"
#include "util/debug.h"
#include "util/header.h"
#include "util/parse-options.h"
#include "util/strlist.h"
#include "util/build-id.h"
#include "util/symbol.h"

static int build_id_cache__add_file(const char *filename, const char *debugdir)
{
	char sbuild_id[BUILD_ID_SIZE * 2 + 1];
	u8 build_id[BUILD_ID_SIZE];
	int err;

	if (filename__read_build_id(filename, &build_id, sizeof(build_id)) < 0) {
		pr_debug("Couldn't read a build-id in %s\n", filename);
		return -1;
	}

	build_id__sprintf(build_id, sizeof(build_id), sbuild_id);
	err = build_id_cache__add_s(sbuild_id, debugdir, filename,
				    false, false);
	if (verbose)
		pr_info("Adding %s %s: %s\n", sbuild_id, filename,
			err ? "FAIL" : "Ok");
	return err;
}

static int build_id_cache__remove_file(const char *filename,
				       const char *debugdir)
{
	u8 build_id[BUILD_ID_SIZE];
	char sbuild_id[BUILD_ID_SIZE * 2 + 1];

	int err;

	if (filename__read_build_id(filename, &build_id, sizeof(build_id)) < 0) {
		pr_debug("Couldn't read a build-id in %s\n", filename);
		return -1;
	}

	build_id__sprintf(build_id, sizeof(build_id), sbuild_id);
	err = build_id_cache__remove_s(sbuild_id, debugdir);
	if (verbose)
		pr_info("Removing %s %s: %s\n", sbuild_id, filename,
			err ? "FAIL" : "Ok");

	return err;
}

int cmd_buildid_cache(int argc, const char **argv,
		      const char *prefix __maybe_unused)
{
	struct strlist *list;
	struct str_node *pos;
	char debugdir[PATH_MAX];
	char const *add_name_list_str = NULL,
		   *remove_name_list_str = NULL;
	const struct option buildid_cache_options[] = {
	OPT_STRING('a', "add", &add_name_list_str,
		   "file list", "file(s) to add"),
	OPT_STRING('r', "remove", &remove_name_list_str, "file list",
		    "file(s) to remove"),
	OPT_INCR('v', "verbose", &verbose, "be more verbose"),
	OPT_END()
	};
	const char * const buildid_cache_usage[] = {
		"perf buildid-cache [<options>]",
		NULL
	};

	argc = parse_options(argc, argv, buildid_cache_options,
			     buildid_cache_usage, 0);

	if (symbol__init() < 0)
		return -1;

	setup_pager();

	snprintf(debugdir, sizeof(debugdir), "%s", buildid_dir);

	if (add_name_list_str) {
		list = strlist__new(true, add_name_list_str);
		if (list) {
			strlist__for_each(pos, list)
				if (build_id_cache__add_file(pos->s, debugdir)) {
					if (errno == EEXIST) {
						pr_debug("%s already in the cache\n",
							 pos->s);
						continue;
					}
					pr_warning("Couldn't add %s: %s\n",
						   pos->s, strerror(errno));
				}

			strlist__delete(list);
		}
	}

	if (remove_name_list_str) {
		list = strlist__new(true, remove_name_list_str);
		if (list) {
			strlist__for_each(pos, list)
				if (build_id_cache__remove_file(pos->s, debugdir)) {
					if (errno == ENOENT) {
						pr_debug("%s wasn't in the cache\n",
							 pos->s);
						continue;
					}
					pr_warning("Couldn't remove %s: %s\n",
						   pos->s, strerror(errno));
				}

			strlist__delete(list);
		}
	}

	return 0;
}
