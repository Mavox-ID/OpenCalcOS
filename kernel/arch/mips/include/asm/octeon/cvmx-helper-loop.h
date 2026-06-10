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
/**
 * @file
 *
 * Functions for LOOP initialization, configuration,
 * and monitoring.
 *
 */
#ifndef __CVMX_HELPER_LOOP_H__
#define __CVMX_HELPER_LOOP_H__

/**
 * Probe a LOOP interface and determine the number of ports
 * connected to it. The LOOP interface should still be down after
 * this call.
 *
 * @interface: Interface to probe
 *
 * Returns Number of ports on the interface. Zero to disable.
 */
extern int __cvmx_helper_loop_probe(int interface);
static inline int __cvmx_helper_loop_enumerate(int interface) {return 4; }

/**
 * Bringup and enable a LOOP interface. After this call packet
 * I/O should be fully functional. This is called with IPD
 * enabled but PKO disabled.
 *
 * @interface: Interface to bring up
 *
 * Returns Zero on success, negative on failure
 */
extern int __cvmx_helper_loop_enable(int interface);

#endif
