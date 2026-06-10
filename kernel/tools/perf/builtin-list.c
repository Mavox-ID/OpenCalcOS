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

#include "util/parse-events.h"
#include "util/cache.h"

int cmd_list(int argc, const char **argv, const char *prefix __maybe_unused)
{
	setup_pager();

	if (argc == 1)
		print_events(NULL, false);
	else {
		int i;

		for (i = 1; i < argc; ++i) {
			if (i > 2)
				putchar('\n');
			if (strncmp(argv[i], "tracepoint", 10) == 0)
				print_tracepoint_events(NULL, NULL, false);
			else if (strcmp(argv[i], "hw") == 0 ||
				 strcmp(argv[i], "hardware") == 0)
				print_events_type(PERF_TYPE_HARDWARE);
			else if (strcmp(argv[i], "sw") == 0 ||
				 strcmp(argv[i], "software") == 0)
				print_events_type(PERF_TYPE_SOFTWARE);
			else if (strcmp(argv[i], "cache") == 0 ||
				 strcmp(argv[i], "hwcache") == 0)
				print_hwcache_events(NULL, false);
			else if (strcmp(argv[i], "--raw-dump") == 0)
				print_events(NULL, true);
			else {
				char *sep = strchr(argv[i], ':'), *s;
				int sep_idx;

				if (sep == NULL) {
					print_events(argv[i], false);
					continue;
				}
				sep_idx = sep - argv[i];
				s = strdup(argv[i]);
				if (s == NULL)
					return -1;

				s[sep_idx] = '\0';
				print_tracepoint_events(s, s + sep_idx + 1, false);
				free(s);
			}
		}
	}
	return 0;
}
