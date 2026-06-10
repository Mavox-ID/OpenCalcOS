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
#ifndef _OZCONFIG_H
#define _OZCONFIG_H

/* #define WANT_TRACE */
#ifdef WANT_TRACE
#define WANT_VERBOSE_TRACE
#endif /* #ifdef WANT_TRACE */
/* #define WANT_URB_PARANOIA */

/* #define WANT_PRE_2_6_39 */
#define WANT_EVENT_TRACE

/* These defines determine what verbose trace is displayed. */
#ifdef WANT_VERBOSE_TRACE
/* #define WANT_TRACE_STREAM */
/* #define WANT_TRACE_URB */
/* #define WANT_TRACE_CTRL_DETAIL */
#define WANT_TRACE_HUB
/* #define WANT_TRACE_RX_FRAMES */
/* #define WANT_TRACE_TX_FRAMES */
#endif /* WANT_VERBOSE_TRACE */

#endif /* _OZCONFIG_H */
