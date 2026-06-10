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
#ifndef DHFCFG_H
#define DHFCFG_H
/*-----------------------------------------------------------------------------
 * File DHFCFG.H
 *
 * Contents: #defines for the DHF module
 *
 * Comments:
 *   Some combinations of the #defines in this file are illegal (as noted below).
 *   If an illegal combinations of #defines is specified a compile error is
 *   generated. See document DHFUG.DOC for more information.
 *
 * Author: John Meertens
 * Date:   11-01-2000
 *
 * Change history:
 *---------------------------------------------------------------------------*/


/* Define DHF_WCI if you want to use the WCI to access the ORiNOCO card.
   Define DHF_UIL if you want to use the UIL to access the ORiNOCO card.
   You must define either DHF_WCI or DHF_UIL. If neither of the two is defined
   or both a compile error is generated. */
#define DHF_WCI
/* !!!#define DHF_UIL */

/* Define DHF_BIG_ENDIAN if you are working on a big endian platform.
   Define DHF_LITTLE_ENDIAN if you are working on a little endian platform.
   You must define either DHF_BIG_ENDIAN or DHF_LITTLE_ENDIAN. If neither of
   the two is defined or both a compile error is generated. */
#ifdef USE_BIG_ENDIAN
#define DHF_BIG_ENDIAN
#else
#define DHF_LITTLE_ENDIAN
#endif  /* USE_BIG_ENDIAN */

/* Define DHF_WIN if you are working on Windows platform.
   Define DHF_DOS if you are working on DOS.
   You must define either DHF_WIN or DHF_DOS. If neither of
   the two is defined or both a compile error is generated.
  !!!#define DHF_WIN
  !!!#define DHF_DOS */

/* Define if you want the DHF to users. Not defining DHF_GET_RES_MSG
   leads to a decrease in code size as message strings are not included.
  !!!#define DHF_GET_RES_MSG */

/* Beep driver specific
   Prevent inclusion of stdlib.h and string.h */
#define _INC_STDLIB
#define _INC_STRING

/*-----------------------------------------------------------------------------
   Define one or more of the following DSF #defines if you want to implement
   the related DSF-function. Function dsf_callback must allways be implemented.
   See file DHF.H for prototypes of the functions. */

/* Define DSF_ALLOC if you want to manage memory allocation and de-allocation
   for the DHF. If DSF_ALLOC is defined you must implement dsf_alloc and dsf_free.
  !!!#define DSF_ALLOC */

/* Define DSF_CONFIRM if you want the DHF to ask the user for confirmation in a
   number of situations. If DSF_CONFIRM is defined you must implement dsf_confirm.
   Not defining DSF_CONFIRM leads to a decrease in code size as confirmation
   strings are not included.
  !!!#define DSF_CONFIRM */

/* Define DSF_DEBUG_MESSAGE if you want debug messages added to your output.
   If you define DSF_DEBUG_MESSAGE then you must implement function
   dsf_debug_message.
  #define DSF_DEBUG_MESSAGE */

/* Define DSF_ASSERT if you want asserts to be activated.
   If you define DSF_ASSERT then you must implement function dsf_assert.
  #define DBG 1
  #define DSF_ASSERT */

/* Define DSF_DBWIN if you want asserts and debug messages to be send to a debug
   window like SOFTICE or DebugView from SysInternals.
  !!!#define DSF_DBWIN
  !!! Not implemented yet! */

/* Define DSF_VOLATILE_ONLY if you only wants to use valatile functions
   This is a typical setting for a AP and a driver. */
#define DSF_VOLATILE_ONLY

/* Define DSF_HERMESII if you want to use the DHF for the Hermes-II */
#ifdef HERMES2
#define DSF_HERMESII
#else
#undef DSF_HERMESII
#endif /* HERMES2 */

/* Define DSF_BINARY_FILE if you want to use the DHF in combination with
   reading the Firmware from a separate binary file.
  !!!#define DSF_BINARY_FILE */

#endif /* DHFCFG_H */
