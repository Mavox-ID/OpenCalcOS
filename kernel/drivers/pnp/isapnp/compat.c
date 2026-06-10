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
#include <beep/module.h>
#include <beep/isapnp.h>
#include <beep/string.h>

static void pnp_convert_id(char *buf, unsigned short vendor,
			   unsigned short device)
{
	sprintf(buf, "%c%c%c%x%x%x%x",
		'A' + ((vendor >> 2) & 0x3f) - 1,
		'A' + (((vendor & 3) << 3) | ((vendor >> 13) & 7)) - 1,
		'A' + ((vendor >> 8) & 0x1f) - 1,
		(device >> 4) & 0x0f, device & 0x0f,
		(device >> 12) & 0x0f, (device >> 8) & 0x0f);
}

struct pnp_card *pnp_find_card(unsigned short vendor, unsigned short device,
			       struct pnp_card *from)
{
	char id[8];
	char any[8];
	struct list_head *list;

	pnp_convert_id(id, vendor, device);
	pnp_convert_id(any, ISAPNP_ANY_ID, ISAPNP_ANY_ID);

	list = from ? from->global_list.next : pnp_cards.next;

	while (list != &pnp_cards) {
		struct pnp_card *card = global_to_pnp_card(list);

		if (compare_pnp_id(card->id, id) || (memcmp(id, any, 7) == 0))
			return card;
		list = list->next;
	}
	return NULL;
}

struct pnp_dev *pnp_find_dev(struct pnp_card *card, unsigned short vendor,
			     unsigned short function, struct pnp_dev *from)
{
	char id[8];
	char any[8];

	pnp_convert_id(id, vendor, function);
	pnp_convert_id(any, ISAPNP_ANY_ID, ISAPNP_ANY_ID);
	if (card == NULL) {	/* look for a logical device from all cards */
		struct list_head *list;

		list = pnp_global.next;
		if (from)
			list = from->global_list.next;

		while (list != &pnp_global) {
			struct pnp_dev *dev = global_to_pnp_dev(list);

			if (compare_pnp_id(dev->id, id) ||
			    (memcmp(id, any, 7) == 0))
				return dev;
			list = list->next;
		}
	} else {
		struct list_head *list;

		list = card->devices.next;
		if (from) {
			list = from->card_list.next;
			if (from->card != card)	/* something is wrong */
				return NULL;
		}
		while (list != &card->devices) {
			struct pnp_dev *dev = card_to_pnp_dev(list);

			if (compare_pnp_id(dev->id, id))
				return dev;
			list = list->next;
		}
	}
	return NULL;
}

EXPORT_SYMBOL(pnp_find_card);
EXPORT_SYMBOL(pnp_find_dev);
