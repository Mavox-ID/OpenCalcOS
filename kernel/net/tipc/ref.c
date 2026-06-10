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
#include "ref.h"

/**
 * struct reference - TIPC object reference entry
 * @object: pointer to object associated with reference entry
 * @lock: spinlock controlling access to object
 * @ref: reference value for object (combines instance & array index info)
 */
struct reference {
	void *object;
	spinlock_t lock;
	u32 ref;
};

/**
 * struct tipc_ref_table - table of TIPC object reference entries
 * @entries: pointer to array of reference entries
 * @capacity: array index of first unusable entry
 * @init_point: array index of first uninitialized entry
 * @first_free: array index of first unused object reference entry
 * @last_free: array index of last unused object reference entry
 * @index_mask: bitmask for array index portion of reference values
 * @start_mask: initial value for instance value portion of reference values
 */
struct ref_table {
	struct reference *entries;
	u32 capacity;
	u32 init_point;
	u32 first_free;
	u32 last_free;
	u32 index_mask;
	u32 start_mask;
};

/*
 * Object reference table consists of 2**N entries.
 *
 * State	Object ptr	Reference
 * -----        ----------      ---------
 * In use        non-NULL       XXXX|own index
 *				(XXXX changes each time entry is acquired)
 * Free            NULL         YYYY|next free index
 *				(YYYY is one more than last used XXXX)
 * Uninitialized   NULL         0
 *
 * Entry 0 is not used; this allows index 0 to denote the end of the free list.
 *
 * Note that a reference value of 0 does not necessarily indicate that an
 * entry is uninitialized, since the last entry in the free list could also
 * have a reference value of 0 (although this is unlikely).
 */

static struct ref_table tipc_ref_table;

static DEFINE_RWLOCK(ref_table_lock);

/**
 * tipc_ref_table_init - create reference table for objects
 */
int tipc_ref_table_init(u32 requested_size, u32 start)
{
	struct reference *table;
	u32 actual_size;

	/* account for unused entry, then round up size to a power of 2 */

	requested_size++;
	for (actual_size = 16; actual_size < requested_size; actual_size <<= 1)
		/* do nothing */ ;

	/* allocate table & mark all entries as uninitialized */
	table = vzalloc(actual_size * sizeof(struct reference));
	if (table == NULL)
		return -ENOMEM;

	tipc_ref_table.entries = table;
	tipc_ref_table.capacity = requested_size;
	tipc_ref_table.init_point = 1;
	tipc_ref_table.first_free = 0;
	tipc_ref_table.last_free = 0;
	tipc_ref_table.index_mask = actual_size - 1;
	tipc_ref_table.start_mask = start & ~tipc_ref_table.index_mask;

	return 0;
}

/**
 * tipc_ref_table_stop - destroy reference table for objects
 */
void tipc_ref_table_stop(void)
{
	if (!tipc_ref_table.entries)
		return;

	vfree(tipc_ref_table.entries);
	tipc_ref_table.entries = NULL;
}

/**
 * tipc_ref_acquire - create reference to an object
 *
 * Register an object pointer in reference table and lock the object.
 * Returns a unique reference value that is used from then on to retrieve the
 * object pointer, or to determine that the object has been deregistered.
 *
 * Note: The object is returned in the locked state so that the caller can
 * register a partially initialized object, without running the risk that
 * the object will be accessed before initialization is complete.
 */
u32 tipc_ref_acquire(void *object, spinlock_t **lock)
{
	u32 index;
	u32 index_mask;
	u32 next_plus_upper;
	u32 ref;
	struct reference *entry = NULL;

	if (!object) {
		pr_err("Attempt to acquire ref. to non-existent obj\n");
		return 0;
	}
	if (!tipc_ref_table.entries) {
		pr_err("Ref. table not found in acquisition attempt\n");
		return 0;
	}

	/* take a free entry, if available; otherwise initialize a new entry */
	write_lock_bh(&ref_table_lock);
	if (tipc_ref_table.first_free) {
		index = tipc_ref_table.first_free;
		entry = &(tipc_ref_table.entries[index]);
		index_mask = tipc_ref_table.index_mask;
		next_plus_upper = entry->ref;
		tipc_ref_table.first_free = next_plus_upper & index_mask;
		ref = (next_plus_upper & ~index_mask) + index;
	} else if (tipc_ref_table.init_point < tipc_ref_table.capacity) {
		index = tipc_ref_table.init_point++;
		entry = &(tipc_ref_table.entries[index]);
		spin_lock_init(&entry->lock);
		ref = tipc_ref_table.start_mask + index;
	} else {
		ref = 0;
	}
	write_unlock_bh(&ref_table_lock);

	/*
	 * Grab the lock so no one else can modify this entry
	 * While we assign its ref value & object pointer
	 */
	if (entry) {
		spin_lock_bh(&entry->lock);
		entry->ref = ref;
		entry->object = object;
		*lock = &entry->lock;
		/*
		 * keep it locked, the caller is responsible
		 * for unlocking this when they're done with it
		 */
	}

	return ref;
}

/**
 * tipc_ref_discard - invalidate references to an object
 *
 * Disallow future references to an object and free up the entry for re-use.
 * Note: The entry's spin_lock may still be busy after discard
 */
void tipc_ref_discard(u32 ref)
{
	struct reference *entry;
	u32 index;
	u32 index_mask;

	if (!tipc_ref_table.entries) {
		pr_err("Ref. table not found during discard attempt\n");
		return;
	}

	index_mask = tipc_ref_table.index_mask;
	index = ref & index_mask;
	entry = &(tipc_ref_table.entries[index]);

	write_lock_bh(&ref_table_lock);

	if (!entry->object) {
		pr_err("Attempt to discard ref. to non-existent obj\n");
		goto exit;
	}
	if (entry->ref != ref) {
		pr_err("Attempt to discard non-existent reference\n");
		goto exit;
	}

	/*
	 * mark entry as unused; increment instance part of entry's reference
	 * to invalidate any subsequent references
	 */
	entry->object = NULL;
	entry->ref = (ref & ~index_mask) + (index_mask + 1);

	/* append entry to free entry list */
	if (tipc_ref_table.first_free == 0)
		tipc_ref_table.first_free = index;
	else
		tipc_ref_table.entries[tipc_ref_table.last_free].ref |= index;
	tipc_ref_table.last_free = index;

exit:
	write_unlock_bh(&ref_table_lock);
}

/**
 * tipc_ref_lock - lock referenced object and return pointer to it
 */
void *tipc_ref_lock(u32 ref)
{
	if (likely(tipc_ref_table.entries)) {
		struct reference *entry;

		entry = &tipc_ref_table.entries[ref &
						tipc_ref_table.index_mask];
		if (likely(entry->ref != 0)) {
			spin_lock_bh(&entry->lock);
			if (likely((entry->ref == ref) && (entry->object)))
				return entry->object;
			spin_unlock_bh(&entry->lock);
		}
	}
	return NULL;
}


/**
 * tipc_ref_deref - return pointer referenced object (without locking it)
 */
void *tipc_ref_deref(u32 ref)
{
	if (likely(tipc_ref_table.entries)) {
		struct reference *entry;

		entry = &tipc_ref_table.entries[ref &
						tipc_ref_table.index_mask];
		if (likely(entry->ref == ref))
			return entry->object;
	}
	return NULL;
}
