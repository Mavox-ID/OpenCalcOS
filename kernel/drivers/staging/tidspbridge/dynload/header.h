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
#include <beep/string.h>
#define DL_STRCMP  strcmp

/* maximum parenthesis nesting in relocation stack expressions */
#define STATIC_EXPR_STK_SIZE 10

#include <beep/types.h>

#include "doff.h"
#include <dspbridge/dynamic_loader.h>
#include "params.h"
#include "dload_internal.h"
#include "reloc_table.h"

/*
 * Plausibility limits
 *
 * These limits are imposed upon the input DOFF file as a check for validity.
 * They are hard limits, in that the load will fail if they are exceeded.
 * The numbers selected are arbitrary, in that the loader implementation does
 * not require these limits.
 */

/* maximum number of bytes in string table */
#define MAX_REASONABLE_STRINGTAB (0x100000)
/* maximum number of code,data,etc. sections */
#define MAX_REASONABLE_SECTIONS (200)
/* maximum number of linker symbols */
#define MAX_REASONABLE_SYMBOLS (100000)

/* shift count to align F_BIG with DLOAD_LITTLE */
#define ALIGN_COFF_ENDIANNESS 7
#define ENDIANNESS_MASK (DF_BYTE_ORDER >> ALIGN_COFF_ENDIANNESS)
