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
 * Functions for XAUI initialization, configuration,
 * and monitoring.
 *
 */
#ifndef __CVMX_HELPER_XAUI_H__
#define __CVMX_HELPER_XAUI_H__

/**
 * Probe a XAUI interface and determine the number of ports
 * connected to it. The XAUI interface should still be down
 * after this call.
 *
 * @interface: Interface to probe
 *
 * Returns Number of ports on the interface. Zero to disable.
 */
extern int __cvmx_helper_xaui_probe(int interface);
extern int __cvmx_helper_xaui_enumerate(int interface);

/**
 * Bringup and enable a XAUI interface. After this call packet
 * I/O should be fully functional. This is called with IPD
 * enabled but PKO disabled.
 *
 * @interface: Interface to bring up
 *
 * Returns Zero on success, negative on failure
 */
extern int __cvmx_helper_xaui_enable(int interface);

/**
 * Return the link state of an IPD/PKO port as returned by
 * auto negotiation. The result of this function may not match
 * Octeon's link config if auto negotiation has changed since
 * the last call to cvmx_helper_link_set().
 *
 * @ipd_port: IPD/PKO port to query
 *
 * Returns Link state
 */
extern cvmx_helper_link_info_t __cvmx_helper_xaui_link_get(int ipd_port);

/**
 * Configure an IPD/PKO port for the specified link state. This
 * function does not influence auto negotiation at the PHY level.
 * The passed link state must always match the link state returned
 * by cvmx_helper_link_get(). It is normally best to use
 * cvmx_helper_link_autoconf() instead.
 *
 * @ipd_port:  IPD/PKO port to configure
 * @link_info: The new link state
 *
 * Returns Zero on success, negative on failure
 */
extern int __cvmx_helper_xaui_link_set(int ipd_port,
				       cvmx_helper_link_info_t link_info);

/**
 * Configure a port for internal and/or external loopback. Internal loopback
 * causes packets sent by the port to be received by Octeon. External loopback
 * causes packets received from the wire to sent out again.
 *
 * @ipd_port: IPD/PKO port to loopback.
 * @enable_internal:
 *                 Non zero if you want internal loopback
 * @enable_external:
 *                 Non zero if you want external loopback
 *
 * Returns Zero on success, negative on failure.
 */
extern int __cvmx_helper_xaui_configure_loopback(int ipd_port,
						 int enable_internal,
						 int enable_external);
#endif
