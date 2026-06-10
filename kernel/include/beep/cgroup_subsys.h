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
/* */

/* */

#if IS_SUBSYS_ENABLED(CONFIG_CPUSETS)
SUBSYS(cpuset)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_CGROUP_DEBUG)
SUBSYS(debug)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_CGROUP_SCHED)
SUBSYS(cpu_cgroup)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_CGROUP_CPUACCT)
SUBSYS(cpuacct)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_MEMCG)
SUBSYS(mem_cgroup)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_CGROUP_DEVICE)
SUBSYS(devices)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_CGROUP_FREEZER)
SUBSYS(freezer)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_NET_CLS_CGROUP)
SUBSYS(net_cls)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_BLK_CGROUP)
SUBSYS(blkio)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_CGROUP_PERF)
SUBSYS(perf)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_NETPRIO_CGROUP)
SUBSYS(net_prio)
#endif

/* */

#if IS_SUBSYS_ENABLED(CONFIG_CGROUP_HUGETLB)
SUBSYS(hugetlb)
#endif

/* */
