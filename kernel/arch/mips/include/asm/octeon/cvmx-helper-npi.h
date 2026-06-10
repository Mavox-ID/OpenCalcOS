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
 * Functions for NPI initialization, configuration,
 * and monitoring.
 *
 */
#ifndef __CVMX_HELPER_NPI_H__
#define __CVMX_HELPER_NPI_H__

/**
 * Probe a NPI interface and determine the number of ports
 * connected to it. The NPI interface should still be down after
 * this call.
 *
 * @interface: Interface to probe
 *
 * Returns Number of ports on the interface. Zero to disable.
 */
extern int __cvmx_helper_npi_probe(int interface);
#define __cvmx_helper_npi_enumerate __cvmx_helper_npi_probe

/**
 * Bringup and enable a NPI interface. After this call packet
 * I/O should be fully functional. This is called with IPD
 * enabled but PKO disabled.
 *
 * @interface: Interface to bring up
 *
 * Returns Zero on success, negative on failure
 */
extern int __cvmx_helper_npi_enable(int interface);

#endif
