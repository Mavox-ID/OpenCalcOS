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
#ifndef _ASM_S390_AIRQ_H
#define _ASM_S390_AIRQ_H

typedef void (*adapter_int_handler_t)(void *, void *);

void *s390_register_adapter_interrupt(adapter_int_handler_t, void *, u8);
void s390_unregister_adapter_interrupt(void *, u8);

#endif /* _ASM_S390_AIRQ_H */
