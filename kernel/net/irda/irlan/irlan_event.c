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
#include <net/irda/irlan_event.h>

const char * const irlan_state[] = {
	"IRLAN_IDLE",
	"IRLAN_QUERY",
	"IRLAN_CONN",
	"IRLAN_INFO",
	"IRLAN_MEDIA",
	"IRLAN_OPEN",
	"IRLAN_WAIT",
	"IRLAN_ARB",
	"IRLAN_DATA",
	"IRLAN_CLOSE",
	"IRLAN_SYNC",
};

void irlan_next_client_state(struct irlan_cb *self, IRLAN_STATE state)
{
	IRDA_DEBUG(2, "%s(), %s\n", __func__ , irlan_state[state]);

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == IRLAN_MAGIC, return;);

	self->client.state = state;
}

void irlan_next_provider_state(struct irlan_cb *self, IRLAN_STATE state)
{
	IRDA_DEBUG(2, "%s(), %s\n", __func__ , irlan_state[state]);

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == IRLAN_MAGIC, return;);

	self->provider.state = state;
}

