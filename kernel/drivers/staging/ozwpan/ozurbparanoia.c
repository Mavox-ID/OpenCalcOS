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
#include <beep/usb.h>
#include "ozconfig.h"
#ifdef WANT_URB_PARANOIA
#include "ozurbparanoia.h"
#include "oztrace.h"
/*-----------------------------------------------------------------------------
 */
#define OZ_MAX_URBS	1000
struct urb *g_urb_memory[OZ_MAX_URBS];
int g_nb_urbs;
DEFINE_SPINLOCK(g_urb_mem_lock);
/*-----------------------------------------------------------------------------
 */
void oz_remember_urb(struct urb *urb)
{
	unsigned long irq_state;
	spin_lock_irqsave(&g_urb_mem_lock, irq_state);
	if (g_nb_urbs < OZ_MAX_URBS) {
		g_urb_memory[g_nb_urbs++] = urb;
		oz_trace("%lu: urb up = %d %p\n", jiffies, g_nb_urbs, urb);
	} else {
		oz_trace("ERROR urb buffer full\n");
	}
	spin_unlock_irqrestore(&g_urb_mem_lock, irq_state);
}
/*------------------------------------------------------------------------------
 */
int oz_forget_urb(struct urb *urb)
{
	unsigned long irq_state;
	int i;
	int rc = -1;
	spin_lock_irqsave(&g_urb_mem_lock, irq_state);
	for (i = 0; i < g_nb_urbs; i++) {
		if (g_urb_memory[i] == urb) {
			rc = 0;
			if (--g_nb_urbs > i)
				memcpy(&g_urb_memory[i], &g_urb_memory[i+1],
					(g_nb_urbs - i) * sizeof(struct urb *));
			oz_trace("%lu: urb down = %d %p\n",
				jiffies, g_nb_urbs, urb);
		}
	}
	spin_unlock_irqrestore(&g_urb_mem_lock, irq_state);
	return rc;
}
#endif /* #ifdef WANT_URB_PARANOIA */

