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
#include "ozconfig.h"
#include "oztrace.h"

#ifdef WANT_VERBOSE_TRACE
unsigned long trace_flags =
	0
#ifdef WANT_TRACE_STREAM
	| OZ_TRACE_STREAM
#endif /* WANT_TRACE_STREAM */
#ifdef WANT_TRACE_URB
	| OZ_TRACE_URB
#endif /* WANT_TRACE_URB */

#ifdef WANT_TRACE_CTRL_DETAIL
	| OZ_TRACE_CTRL_DETAIL
#endif /* WANT_TRACE_CTRL_DETAIL */

#ifdef WANT_TRACE_HUB
	| OZ_TRACE_HUB
#endif /* WANT_TRACE_HUB */

#ifdef WANT_TRACE_RX_FRAMES
	| OZ_TRACE_RX_FRAMES
#endif /* WANT_TRACE_RX_FRAMES */

#ifdef WANT_TRACE_TX_FRAMES
	| OZ_TRACE_TX_FRAMES
#endif /* WANT_TRACE_TX_FRAMES */
	;
#endif /* WANT_VERBOSE_TRACE */

