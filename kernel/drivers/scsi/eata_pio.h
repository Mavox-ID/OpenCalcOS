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
#ifndef _EATA_PIO_H
#define _EATA_PIO_H

#define VER_MAJOR 0
#define VER_MINOR 0
#define VER_SUB	  "1b"

/************************************************************************
 * Here you can switch parts of the code on and of			*
 ************************************************************************/

#define VERBOSE_SETUP		/* show startup screen of 2001 */
#define ALLOW_DMA_BOARDS 1

/************************************************************************
 * Debug options.							* 
 * Enable DEBUG and whichever options you require.			*
 ************************************************************************/
#define DEBUG_EATA	1	/* Enable debug code.                       */
#define DPT_DEBUG	0	/* Bobs special                             */
#define DBG_DELAY	0	/* Build in delays so debug messages can be
				 * be read before they vanish of the top of
				 * the screen!
				 */
#define DBG_PROBE	0	/* Debug probe routines.                    */
#define DBG_ISA		0	/* Trace ISA routines                       */
#define DBG_EISA	0	/* Trace EISA routines                      */
#define DBG_PCI		0	/* Trace PCI routines                       */
#define DBG_PIO		0	/* Trace get_config_PIO                     */
#define DBG_COM		0	/* Trace command call                       */
#define DBG_QUEUE	0	/* Trace command queueing.                  */
#define DBG_INTR	0	/* Trace interrupt service routine.         */
#define DBG_INTR2	0	/* Trace interrupt service routine.         */
#define DBG_PROC	0	/* Debug proc-fs related statistics         */
#define DBG_PROC_WRITE	0
#define DBG_REGISTER	0	/* */
#define DBG_ABNORM	1	/* Debug abnormal actions (reset, abort)    */

#if DEBUG_EATA
#define DBG(x, y)   if ((x)) {y;}
#else
#define DBG(x, y)
#endif

#endif				/* _EATA_PIO_H */
