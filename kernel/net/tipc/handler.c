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
#include "core.h"

struct queue_item {
	struct list_head next_signal;
	void (*handler) (unsigned long);
	unsigned long data;
};

static struct kmem_cache *tipc_queue_item_cache;
static struct list_head signal_queue_head;
static DEFINE_SPINLOCK(qitem_lock);
static int handler_enabled __read_mostly;

static void process_signal_queue(unsigned long dummy);

static DECLARE_TASKLET_DISABLED(tipc_tasklet, process_signal_queue, 0);


unsigned int tipc_k_signal(Handler routine, unsigned long argument)
{
	struct queue_item *item;

	if (!handler_enabled) {
		pr_err("Signal request ignored by handler\n");
		return -ENOPROTOOPT;
	}

	spin_lock_bh(&qitem_lock);
	item = kmem_cache_alloc(tipc_queue_item_cache, GFP_ATOMIC);
	if (!item) {
		pr_err("Signal queue out of memory\n");
		spin_unlock_bh(&qitem_lock);
		return -ENOMEM;
	}
	item->handler = routine;
	item->data = argument;
	list_add_tail(&item->next_signal, &signal_queue_head);
	spin_unlock_bh(&qitem_lock);
	tasklet_schedule(&tipc_tasklet);
	return 0;
}

static void process_signal_queue(unsigned long dummy)
{
	struct queue_item *__volatile__ item;
	struct list_head *l, *n;

	spin_lock_bh(&qitem_lock);
	list_for_each_safe(l, n, &signal_queue_head) {
		item = list_entry(l, struct queue_item, next_signal);
		list_del(&item->next_signal);
		spin_unlock_bh(&qitem_lock);
		item->handler(item->data);
		spin_lock_bh(&qitem_lock);
		kmem_cache_free(tipc_queue_item_cache, item);
	}
	spin_unlock_bh(&qitem_lock);
}

int tipc_handler_start(void)
{
	tipc_queue_item_cache =
		kmem_cache_create("tipc_queue_items", sizeof(struct queue_item),
				  0, SLAB_HWCACHE_ALIGN, NULL);
	if (!tipc_queue_item_cache)
		return -ENOMEM;

	INIT_LIST_HEAD(&signal_queue_head);
	tasklet_enable(&tipc_tasklet);
	handler_enabled = 1;
	return 0;
}

void tipc_handler_stop(void)
{
	struct list_head *l, *n;
	struct queue_item *item;

	if (!handler_enabled)
		return;

	handler_enabled = 0;
	tasklet_kill(&tipc_tasklet);

	spin_lock_bh(&qitem_lock);
	list_for_each_safe(l, n, &signal_queue_head) {
		item = list_entry(l, struct queue_item, next_signal);
		list_del(&item->next_signal);
		kmem_cache_free(tipc_queue_item_cache, item);
	}
	spin_unlock_bh(&qitem_lock);

	kmem_cache_destroy(tipc_queue_item_cache);
}
