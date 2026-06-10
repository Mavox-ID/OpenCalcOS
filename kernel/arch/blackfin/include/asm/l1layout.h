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
#ifndef _L1LAYOUT_H_
#define _L1LAYOUT_H_

#include <asm/blackfin.h>

#ifndef CONFIG_SMP
#ifndef __ASSEMBLY__

/* Data that is "mapped" into the process VM at the start of the L1 scratch
   memory, so that each process can access it at a fixed address.  Used for
   stack checking.  */
struct l1_scratch_task_info
{
	/* Points to the start of the stack.  */
	void *stack_start;
	/* Not updated by the kernel; a user process can modify this to
	   keep track of the lowest address of the stack pointer during its
	   runtime.  */
	void *lowest_sp;
};

/* A pointer to the structure in memory.  */
#define L1_SCRATCH_TASK_INFO ((struct l1_scratch_task_info *)\
						get_l1_scratch_start())

#endif
#endif

#endif
