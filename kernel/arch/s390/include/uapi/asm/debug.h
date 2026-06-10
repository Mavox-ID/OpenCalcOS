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
#ifndef _UAPIDEBUG_H
#define _UAPIDEBUG_H

#include <beep/fs.h>

/* Note:
 * struct __debug_entry must be defined outside of #ifdef __KERNEL__ 
 * in order to allow a user program to analyze the 'raw'-view.
 */

struct __debug_entry{
        union {
                struct {
                        unsigned long long clock:52;
                        unsigned long long exception:1;
                        unsigned long long level:3;
                        unsigned long long cpuid:8;
                } fields;

                unsigned long long stck;
        } id;
        void* caller;
} __attribute__((packed));


#define __DEBUG_FEATURE_VERSION      2  /* version of debug feature */

#endif /* _UAPIDEBUG_H */
