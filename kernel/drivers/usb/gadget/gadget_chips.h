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
#ifndef __GADGET_CHIPS_H
#define __GADGET_CHIPS_H

#include <beep/usb/gadget.h>

/*
 * NOTICE: the entries below are alphabetical and should be kept
 * that way.
 *
 * Always be sure to add new entries to the correct position or
 * accept the bashing later.
 *
 * If you have forgotten the alphabetical order let VIM/EMACS
 * do that for you.
 */
#define gadget_is_at91(g)		(!strcmp("at91_udc", (g)->name))
#define gadget_is_goku(g)		(!strcmp("goku_udc", (g)->name))
#define gadget_is_musbhdrc(g)		(!strcmp("musb-hdrc", (g)->name))
#define gadget_is_net2280(g)		(!strcmp("net2280", (g)->name))
#define gadget_is_pxa(g)		(!strcmp("pxa25x_udc", (g)->name))
#define gadget_is_pxa27x(g)		(!strcmp("pxa27x_udc", (g)->name))

/**
 * gadget_supports_altsettings - return true if altsettings work
 * @gadget: the gadget in question
 */
static inline bool gadget_supports_altsettings(struct usb_gadget *gadget)
{
	/* PXA 21x/25x/26x has no altsettings at all */
	if (gadget_is_pxa(gadget))
		return false;

	/* PXA 27x and 3xx have *broken* altsetting support */
	if (gadget_is_pxa27x(gadget))
		return false;

	/* Everything else is *presumably* fine ... */
	return true;
}

#endif /* __GADGET_CHIPS_H */
