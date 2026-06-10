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
#include <sysdep/stub.h>
#include <sysdep/faultinfo.h>
#include <sysdep/mcontext.h>

void __attribute__ ((__section__ (".__syscall_stub")))
stub_segv_handler(int sig, siginfo_t *info, void *p)
{
	struct ucontext *uc = p;

	GET_FAULTINFO_FROM_MC(*((struct faultinfo *) STUB_DATA),
			      &uc->uc_mcontext);
	trap_myself();
}

