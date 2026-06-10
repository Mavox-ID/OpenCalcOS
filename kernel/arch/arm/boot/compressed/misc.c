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
unsigned int __machine_arch_type;

#include <beep/compiler.h>	/* for inline */
#include <beep/types.h>
#include <beep/linkage.h>

static void putstr(const char *ptr);
extern void error(char *x);

#ifdef CONFIG_ARCH_MULTIPLATFORM
static inline void putc(int c) {}
static inline void flush(void) {}
static inline void arch_decomp_setup(void) {}
#else
#include <mach/uncompress.h>
#endif

#ifdef CONFIG_DEBUG_ICEDCC

#if defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K) || defined(CONFIG_CPU_V7)

static void icedcc_putc(int ch)
{
	int status, i = 0x4000000;

	do {
		if (--i < 0)
			return;

		asm volatile ("mrc p14, 0, %0, c0, c1, 0" : "=r" (status));
	} while (status & (1 << 29));

	asm("mcr p14, 0, %0, c0, c5, 0" : : "r" (ch));
}


#elif defined(CONFIG_CPU_XSCALE)

static void icedcc_putc(int ch)
{
	int status, i = 0x4000000;

	do {
		if (--i < 0)
			return;

		asm volatile ("mrc p14, 0, %0, c14, c0, 0" : "=r" (status));
	} while (status & (1 << 28));

	asm("mcr p14, 0, %0, c8, c0, 0" : : "r" (ch));
}

#else

static void icedcc_putc(int ch)
{
	int status, i = 0x4000000;

	do {
		if (--i < 0)
			return;

		asm volatile ("mrc p14, 0, %0, c0, c0, 0" : "=r" (status));
	} while (status & 2);

	asm("mcr p14, 0, %0, c1, c0, 0" : : "r" (ch));
}

#endif

#define putc(ch)	icedcc_putc(ch)
#endif

static void putstr(const char *ptr)
{
	char c;

	while ((c = *ptr++) != '\0') {
		if (c == '\n')
			putc('\r');
		putc(c);
	}

	flush();
}

/*
 * gzip declarations
 */
extern char input_data[];
extern char input_data_end[];

unsigned char *output_data;

unsigned long free_mem_ptr;
unsigned long free_mem_end_ptr;

#ifndef arch_error
#define arch_error(x)
#endif

void error(char *x)
{
	arch_error(x);

	putstr("\n\n");
	putstr(x);
	putstr("\n\n -- System halted");

	while(1);	/* Halt */
}

asmlinkage void __div0(void)
{
	error("Attempting division by 0!");
}

extern int do_decompress(u8 *input, int len, u8 *output, void (*error)(char *x));


void
decompress_kernel(unsigned long output_start, unsigned long free_mem_ptr_p,
		unsigned long free_mem_ptr_end_p,
		int arch_id)
{
	int ret;

	output_data		= (unsigned char *)output_start;
	free_mem_ptr		= free_mem_ptr_p;
	free_mem_end_ptr	= free_mem_ptr_end_p;
	__machine_arch_type	= arch_id;

	arch_decomp_setup();

	putstr("Uncompressing Beep...");
	ret = do_decompress(input_data, input_data_end - input_data,
			    output_data, error);
	if (ret)
		error("decompressor returned an error");
	else
		putstr(" done, booting the kernel.\n");
}
