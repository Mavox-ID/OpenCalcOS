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

#ifdef __HAVE_ARCH_MEMCPY
#ifndef CONFIG_OPT_LIB_FUNCTION
void *memcpy(void *v_dst, const void *v_src, __kernel_size_t c)
{
	const char *src = v_src;
	char *dst = v_dst;

	/* Simple, byte oriented memcpy. */
	while (c--)
		*dst++ = *src++;

	return v_dst;
}
#else /* CONFIG_OPT_LIB_FUNCTION */
void *memcpy(void *v_dst, const void *v_src, __kernel_size_t c)
{
	const char *src = v_src;
	char *dst = v_dst;

	/* The following code tries to optimize the copy by using unsigned
	 * alignment. This will work fine if both source and destination are
	 * aligned on the same boundary. However, if they are aligned on
	 * different boundaries shifts will be necessary. This might result in
	 * bad performance on MicroBlaze systems without a barrel shifter.
	 */
	const uint32_t *i_src;
	uint32_t *i_dst;

	if (likely(c >= 4)) {
		unsigned  value, buf_hold;

		/* Align the destination to a word boundary. */
		/* This is done in an endian independent manner. */
		switch ((unsigned long)dst & 3) {
		case 1:
			*dst++ = *src++;
			--c;
		case 2:
			*dst++ = *src++;
			--c;
		case 3:
			*dst++ = *src++;
			--c;
		}

		i_dst = (void *)dst;

		/* Choose a copy scheme based on the source */
		/* alignment relative to destination. */
		switch ((unsigned long)src & 3) {
		case 0x0:	/* Both byte offsets are aligned */
			i_src  = (const void *)src;

			for (; c >= 4; c -= 4)
				*i_dst++ = *i_src++;

			src  = (const void *)i_src;
			break;
		case 0x1:	/* Unaligned - Off by 1 */
			/* Word align the source */
			i_src = (const void *) ((unsigned)src & ~3);
#ifndef __MICROBLAZEEL__
			/* Load the holding buffer */
			buf_hold = *i_src++ << 8;

			for (; c >= 4; c -= 4) {
				value = *i_src++;
				*i_dst++ = buf_hold | value >> 24;
				buf_hold = value << 8;
			}
#else
			/* Load the holding buffer */
			buf_hold = (*i_src++ & 0xFFFFFF00) >>8;

			for (; c >= 4; c -= 4) {
				value = *i_src++;
				*i_dst++ = buf_hold | ((value & 0xFF) << 24);
				buf_hold = (value & 0xFFFFFF00) >>8;
			}
#endif
			/* Realign the source */
			src = (const void *)i_src;
			src -= 3;
			break;
		case 0x2:	/* Unaligned - Off by 2 */
			/* Word align the source */
			i_src = (const void *) ((unsigned)src & ~3);
#ifndef __MICROBLAZEEL__
			/* Load the holding buffer */
			buf_hold = *i_src++ << 16;

			for (; c >= 4; c -= 4) {
				value = *i_src++;
				*i_dst++ = buf_hold | value >> 16;
				buf_hold = value << 16;
			}
#else
			/* Load the holding buffer */
			buf_hold = (*i_src++ & 0xFFFF0000 )>>16;

			for (; c >= 4; c -= 4) {
				value = *i_src++;
				*i_dst++ = buf_hold | ((value & 0xFFFF)<<16);
				buf_hold = (value & 0xFFFF0000) >>16;
			}
#endif
			/* Realign the source */
			src = (const void *)i_src;
			src -= 2;
			break;
		case 0x3:	/* Unaligned - Off by 3 */
			/* Word align the source */
			i_src = (const void *) ((unsigned)src & ~3);
#ifndef __MICROBLAZEEL__
			/* Load the holding buffer */
			buf_hold = *i_src++ << 24;

			for (; c >= 4; c -= 4) {
				value = *i_src++;
				*i_dst++ = buf_hold | value >> 8;
				buf_hold = value << 24;
			}
#else
			/* Load the holding buffer */
			buf_hold = (*i_src++ & 0xFF000000) >> 24;

			for (; c >= 4; c -= 4) {
				value = *i_src++;
				*i_dst++ = buf_hold | ((value & 0xFFFFFF) << 8);
				buf_hold = (value & 0xFF000000) >> 24;
			}
#endif
			/* Realign the source */
			src = (const void *)i_src;
			src -= 1;
			break;
		}
		dst = (void *)i_dst;
	}

	/* Finish off any remaining bytes */
	/* simple fast copy, ... unless a cache boundary is crossed */
	switch (c) {
	case 3:
		*dst++ = *src++;
	case 2:
		*dst++ = *src++;
	case 1:
		*dst++ = *src++;
	}

	return v_dst;
}
#endif /* CONFIG_OPT_LIB_FUNCTION */
EXPORT_SYMBOL(memcpy);
#endif /* __HAVE_ARCH_MEMCPY */
