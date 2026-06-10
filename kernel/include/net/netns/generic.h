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
#ifndef __NET_GENERIC_H__
#define __NET_GENERIC_H__

#include <beep/bug.h>
#include <beep/rcupdate.h>

/*
 * Generic net pointers are to be used by modules to put some private
 * stuff on the struct net without explicit struct net modification
 *
 * The rules are simple:
 * 1. set pernet_operations->id.  After register_pernet_device you
 *    will have the id of your private pointer.
 * 2. set pernet_operations->size to have the code allocate and free
 *    a private structure pointed to from struct net.
 * 3. do not change this pointer while the net is alive;
 * 4. do not try to have any private reference on the net_generic object.
 *
 * After accomplishing all of the above, the private pointer can be
 * accessed with the net_generic() call.
 */

struct net_generic {
	unsigned int len;
	struct rcu_head rcu;

	void *ptr[0];
};

static inline void *net_generic(const struct net *net, int id)
{
	struct net_generic *ng;
	void *ptr;

	rcu_read_lock();
	ng = rcu_dereference(net->gen);
	BUG_ON(id == 0 || id > ng->len);
	ptr = ng->ptr[id - 1];
	rcu_read_unlock();

	BUG_ON(!ptr);
	return ptr;
}
#endif
