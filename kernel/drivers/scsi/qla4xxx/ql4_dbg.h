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
 * Driver debug definitions.
 */
/* #define QL_DEBUG  */			/* DEBUG messages */
/* #define QL_DEBUG_LEVEL_3  */		/* Output function tracing */
/* #define QL_DEBUG_LEVEL_4  */
/* #define QL_DEBUG_LEVEL_5  */
/* #define QL_DEBUG_LEVEL_9  */

#define QL_DEBUG_LEVEL_2	/* ALways enable error messagess */
#if defined(QL_DEBUG)
#define DEBUG(x)   do {x;} while (0);
#else
#define DEBUG(x)	do {} while (0);
#endif

#if defined(QL_DEBUG_LEVEL_2)
#define DEBUG2(x)      do {if(ql4xextended_error_logging == 2) x;} while (0);
#define DEBUG2_3(x)   do {x;} while (0);
#else				/*  */
#define DEBUG2(x)	do {} while (0);
#endif				/*  */

#if defined(QL_DEBUG_LEVEL_3)
#define DEBUG3(x)      do {if(ql4xextended_error_logging == 3) x;} while (0);
#else				/*  */
#define DEBUG3(x)	do {} while (0);
#if !defined(QL_DEBUG_LEVEL_2)
#define DEBUG2_3(x)	do {} while (0);
#endif				/*  */
#endif				/*  */
#if defined(QL_DEBUG_LEVEL_4)
#define DEBUG4(x)	do {x;} while (0);
#else				/*  */
#define DEBUG4(x)	do {} while (0);
#endif				/*  */

#if defined(QL_DEBUG_LEVEL_5)
#define DEBUG5(x)	do {x;} while (0);
#else				/*  */
#define DEBUG5(x)	do {} while (0);
#endif				/*  */

#if defined(QL_DEBUG_LEVEL_9)
#define DEBUG9(x)	do {x;} while (0);
#else				/*  */
#define DEBUG9(x)	do {} while (0);
#endif				/*  */
