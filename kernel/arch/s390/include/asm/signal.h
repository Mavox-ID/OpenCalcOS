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
#ifndef _ASMS390_SIGNAL_H
#define _ASMS390_SIGNAL_H

#include <uapi/asm/signal.h>

/* Most things should be clean enough to redefine this at will, if care
   is taken to make libc match.  */
#include <asm/sigcontext.h>
#define _NSIG           _SIGCONTEXT_NSIG
#define _NSIG_BPW       _SIGCONTEXT_NSIG_BPW
#define _NSIG_WORDS     _SIGCONTEXT_NSIG_WORDS

typedef unsigned long old_sigset_t;             /* at least 32 bits */

typedef struct {
        unsigned long sig[_NSIG_WORDS];
} sigset_t;

struct old_sigaction {
        __sighandler_t sa_handler;
        old_sigset_t sa_mask;
        unsigned long sa_flags;
        void (*sa_restorer)(void);
};

struct sigaction {
        __sighandler_t sa_handler;
        unsigned long sa_flags;
        void (*sa_restorer)(void);
        sigset_t sa_mask;               /* mask last for extensibility */
};

struct k_sigaction {
        struct sigaction sa;
};

#endif
