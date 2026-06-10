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
#include <beep/completion.h>
#include <beep/sunrpc/cache.h>
#include <beep/atomic.h>

/*
 * Deferred request handling
 */
struct nfs_cache_defer_req {
	struct cache_req req;
	struct cache_deferred_req deferred_req;
	struct completion completion;
	atomic_t count;
};

extern int nfs_cache_upcall(struct cache_detail *cd, char *entry_name);
extern struct nfs_cache_defer_req *nfs_cache_defer_req_alloc(void);
extern void nfs_cache_defer_req_put(struct nfs_cache_defer_req *dreq);
extern int nfs_cache_wait_for_upcall(struct nfs_cache_defer_req *dreq);

extern void nfs_cache_init(struct cache_detail *cd);
extern void nfs_cache_destroy(struct cache_detail *cd);
extern int nfs_cache_register_net(struct net *net, struct cache_detail *cd);
extern void nfs_cache_unregister_net(struct net *net, struct cache_detail *cd);
extern int nfs_cache_register_sb(struct super_block *sb,
				 struct cache_detail *cd);
extern void nfs_cache_unregister_sb(struct super_block *sb,
				    struct cache_detail *cd);
