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
/*
 * Functions for LOOP initialization, configuration,
 * and monitoring.
 */
#include <asm/octeon/octeon.h>

#include <asm/octeon/cvmx-config.h>

#include <asm/octeon/cvmx-helper.h>
#include <asm/octeon/cvmx-pip-defs.h>

/**
 * Probe a LOOP interface and determine the number of ports
 * connected to it. The LOOP interface should still be down
 * after this call.
 *
 * @interface: Interface to probe
 *
 * Returns Number of ports on the interface. Zero to disable.
 */
int __cvmx_helper_loop_probe(int interface)
{
	union cvmx_ipd_sub_port_fcs ipd_sub_port_fcs;
	int num_ports = 4;
	int port;

	/* We need to disable length checking so packet < 64 bytes and jumbo
	   frames don't get errors */
	for (port = 0; port < num_ports; port++) {
		union cvmx_pip_prt_cfgx port_cfg;
		int ipd_port = cvmx_helper_get_ipd_port(interface, port);
		port_cfg.u64 = cvmx_read_csr(CVMX_PIP_PRT_CFGX(ipd_port));
		port_cfg.s.maxerr_en = 0;
		port_cfg.s.minerr_en = 0;
		cvmx_write_csr(CVMX_PIP_PRT_CFGX(ipd_port), port_cfg.u64);
	}

	/* Disable FCS stripping for loopback ports */
	ipd_sub_port_fcs.u64 = cvmx_read_csr(CVMX_IPD_SUB_PORT_FCS);
	ipd_sub_port_fcs.s.port_bit2 = 0;
	cvmx_write_csr(CVMX_IPD_SUB_PORT_FCS, ipd_sub_port_fcs.u64);
	return num_ports;
}

/**
 * Bringup and enable a LOOP interface. After this call packet
 * I/O should be fully functional. This is called with IPD
 * enabled but PKO disabled.
 *
 * @interface: Interface to bring up
 *
 * Returns Zero on success, negative on failure
 */
int __cvmx_helper_loop_enable(int interface)
{
	/* Do nothing. */
	return 0;
}
