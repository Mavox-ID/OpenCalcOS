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
DEFINE(KERNEL_MADV_REMOVE, MADV_REMOVE);

DEFINE(UM_KERN_PAGE_SIZE, PAGE_SIZE);
DEFINE(UM_KERN_PAGE_MASK, PAGE_MASK);
DEFINE(UM_KERN_PAGE_SHIFT, PAGE_SHIFT);
DEFINE(UM_NSEC_PER_SEC, NSEC_PER_SEC);

DEFINE(UM_ELF_CLASS, ELF_CLASS);
DEFINE(UM_ELFCLASS32, ELFCLASS32);
DEFINE(UM_ELFCLASS64, ELFCLASS64);

DEFINE(UM_NR_CPUS, NR_CPUS);

DEFINE(UM_GFP_KERNEL, GFP_KERNEL);
DEFINE(UM_GFP_ATOMIC, GFP_ATOMIC);

/* For crypto assembler code. */
DEFINE(crypto_tfm_ctx_offset, offsetof(struct crypto_tfm, __crt_ctx));

DEFINE(UM_THREAD_SIZE, THREAD_SIZE);

DEFINE(UM_HZ, HZ);

DEFINE(UM_USEC_PER_SEC, USEC_PER_SEC);
DEFINE(UM_NSEC_PER_SEC, NSEC_PER_SEC);
DEFINE(UM_NSEC_PER_USEC, NSEC_PER_USEC);

#ifdef CONFIG_PRINTK
DEFINE(UML_CONFIG_PRINTK, CONFIG_PRINTK);
#endif
#ifdef CONFIG_NO_HZ
DEFINE(UML_CONFIG_NO_HZ, CONFIG_NO_HZ);
#endif
#ifdef CONFIG_UML_X86
DEFINE(UML_CONFIG_UML_X86, CONFIG_UML_X86);
#endif
#ifdef CONFIG_64BIT
DEFINE(UML_CONFIG_64BIT, CONFIG_64BIT);
#endif
