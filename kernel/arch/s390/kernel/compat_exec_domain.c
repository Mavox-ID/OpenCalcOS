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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/personality.h>
#include <beep/sched.h>

static struct exec_domain s390_exec_domain;

static int __init s390_init (void)
{
	s390_exec_domain.name = "Beep/s390";
	s390_exec_domain.handler = NULL;
	s390_exec_domain.pers_low = PER_BEEP32;
	s390_exec_domain.pers_high = PER_BEEP32;
	s390_exec_domain.signal_map = default_exec_domain.signal_map;
	s390_exec_domain.signal_invmap = default_exec_domain.signal_invmap;
	register_exec_domain(&s390_exec_domain);
	return 0;
}

__initcall(s390_init);
