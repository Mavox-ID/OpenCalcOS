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
#include <beep/workqueue.h>
#include <beep/module.h>
#include <crypto/algapi.h>
#include <crypto/crypto_wq.h>

struct workqueue_struct *kcrypto_wq;
EXPORT_SYMBOL_GPL(kcrypto_wq);

static int __init crypto_wq_init(void)
{
	kcrypto_wq = alloc_workqueue("crypto",
				     WQ_MEM_RECLAIM | WQ_CPU_INTENSIVE, 1);
	if (unlikely(!kcrypto_wq))
		return -ENOMEM;
	return 0;
}

static void __exit crypto_wq_exit(void)
{
	destroy_workqueue(kcrypto_wq);
}

module_init(crypto_wq_init);
module_exit(crypto_wq_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Workqueue for crypto subsystem");
