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
#include <beep/spinlock.h>
#include <beep/module.h>

#include <asm/paravirt.h>

static inline void
default_spin_lock_flags(arch_spinlock_t *lock, unsigned long flags)
{
	arch_spin_lock(lock);
}

struct pv_lock_ops pv_lock_ops = {
#ifdef CONFIG_SMP
	.spin_is_locked = __ticket_spin_is_locked,
	.spin_is_contended = __ticket_spin_is_contended,

	.spin_lock = __ticket_spin_lock,
	.spin_lock_flags = default_spin_lock_flags,
	.spin_trylock = __ticket_spin_trylock,
	.spin_unlock = __ticket_spin_unlock,
#endif
};
EXPORT_SYMBOL(pv_lock_ops);

