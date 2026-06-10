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
#ifndef _NETLOGIC_MULTI_NODE_H_
#define _NETLOGIC_MULTI_NODE_H_

#ifndef CONFIG_NLM_MULTINODE
#define NLM_NR_NODES		1
#else
#if defined(CONFIG_NLM_MULTINODE_2)
#define NLM_NR_NODES		2
#elif defined(CONFIG_NLM_MULTINODE_4)
#define NLM_NR_NODES		4
#else
#define NLM_NR_NODES		1
#endif
#endif

#define NLM_CORES_PER_NODE	8
#define NLM_THREADS_PER_CORE	4
#define NLM_CPUS_PER_NODE	(NLM_CORES_PER_NODE * NLM_THREADS_PER_CORE)

#endif
