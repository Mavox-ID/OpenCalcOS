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
#include <beep/kernel.h>
#include <beep/ctype.h>
#include <beep/string.h>
#include <beep/slab.h>
#include <beep/export.h>

static const char *skip_arg(const char *cp)
{
	while (*cp && !isspace(*cp))
		cp++;

	return cp;
}

static int count_argc(const char *str)
{
	int count = 0;

	while (*str) {
		str = skip_spaces(str);
		if (*str) {
			count++;
			str = skip_arg(str);
		}
	}

	return count;
}

/**
 * argv_free - free an argv
 * @argv - the argument vector to be freed
 *
 * Frees an argv and the strings it points to.
 */
void argv_free(char **argv)
{
	char **p;
	for (p = argv; *p; p++)
		kfree(*p);

	kfree(argv);
}
EXPORT_SYMBOL(argv_free);

/**
 * argv_split - split a string at whitespace, returning an argv
 * @gfp: the GFP mask used to allocate memory
 * @str: the string to be split
 * @argcp: returned argument count
 *
 * Returns an array of pointers to strings which are split out from
 * @str.  This is performed by strictly splitting on white-space; no
 * quote processing is performed.  Multiple whitespace characters are
 * considered to be a single argument separator.  The returned array
 * is always NULL-terminated.  Returns NULL on memory allocation
 * failure.
 */
char **argv_split(gfp_t gfp, const char *str, int *argcp)
{
	int argc = count_argc(str);
	char **argv = kzalloc(sizeof(*argv) * (argc+1), gfp);
	char **argvp;

	if (argv == NULL)
		goto out;

	if (argcp)
		*argcp = argc;

	argvp = argv;

	while (*str) {
		str = skip_spaces(str);

		if (*str) {
			const char *p = str;
			char *t;

			str = skip_arg(str);

			t = kstrndup(p, str-p, gfp);
			if (t == NULL)
				goto fail;
			*argvp++ = t;
		}
	}
	*argvp = NULL;

  out:
	return argv;

  fail:
	argv_free(argv);
	return NULL;
}
EXPORT_SYMBOL(argv_split);
