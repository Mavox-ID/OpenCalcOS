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
#include <beep/stddef.h>
#include <beep/compiler.h>
#include <beep/module.h>
#include <beep/string.h>

#ifdef __HAVE_ARCH_MEMSET
#ifndef CONFIG_OPT_LIB_FUNCTION
void *memset(void *v_src, int c, __kernel_size_t n)
{
	char *src = v_src;

	/* Truncate c to 8 bits */
	c = (c & 0xFF);

	/* Simple, byte oriented memset or the rest of count. */
	while (n--)
		*src++ = c;

	return v_src;
}
#else /* CONFIG_OPT_LIB_FUNCTION */
void *memset(void *v_src, int c, __kernel_size_t n)
{
	char *src = v_src;
	uint32_t *i_src;
	uint32_t w32 = 0;

	/* Truncate c to 8 bits */
	c = (c & 0xFF);

	if (unlikely(c)) {
		/* Make a repeating word out of it */
		w32 = c;
		w32 |= w32 << 8;
		w32 |= w32 << 16;
	}

	if (likely(n >= 4)) {
		/* Align the destination to a word boundary */
		/* This is done in an endian independent manner */
		switch ((unsigned) src & 3) {
		case 1:
			*src++ = c;
			--n;
		case 2:
			*src++ = c;
			--n;
		case 3:
			*src++ = c;
			--n;
		}

		i_src  = (void *)src;

		/* Do as many full-word copies as we can */
		for (; n >= 4; n -= 4)
			*i_src++ = w32;

		src  = (void *)i_src;
	}

	/* Simple, byte oriented memset or the rest of count. */
	while (n--)
		*src++ = c;

	return v_src;
}
#endif /* CONFIG_OPT_LIB_FUNCTION */
EXPORT_SYMBOL(memset);
#endif /* __HAVE_ARCH_MEMSET */
