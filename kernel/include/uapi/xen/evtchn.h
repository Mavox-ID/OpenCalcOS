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
#ifndef __BEEP_PUBLIC_EVTCHN_H__
#define __BEEP_PUBLIC_EVTCHN_H__

/*
 * Bind a fresh port to VIRQ @virq.
 * Return allocated port.
 */
#define IOCTL_EVTCHN_BIND_VIRQ				\
	_IOC(_IOC_NONE, 'E', 0, sizeof(struct ioctl_evtchn_bind_virq))
struct ioctl_evtchn_bind_virq {
	unsigned int virq;
};

/*
 * Bind a fresh port to remote <@remote_domain, @remote_port>.
 * Return allocated port.
 */
#define IOCTL_EVTCHN_BIND_INTERDOMAIN			\
	_IOC(_IOC_NONE, 'E', 1, sizeof(struct ioctl_evtchn_bind_interdomain))
struct ioctl_evtchn_bind_interdomain {
	unsigned int remote_domain, remote_port;
};

/*
 * Allocate a fresh port for binding to @remote_domain.
 * Return allocated port.
 */
#define IOCTL_EVTCHN_BIND_UNBOUND_PORT			\
	_IOC(_IOC_NONE, 'E', 2, sizeof(struct ioctl_evtchn_bind_unbound_port))
struct ioctl_evtchn_bind_unbound_port {
	unsigned int remote_domain;
};

/*
 * Unbind previously allocated @port.
 */
#define IOCTL_EVTCHN_UNBIND				\
	_IOC(_IOC_NONE, 'E', 3, sizeof(struct ioctl_evtchn_unbind))
struct ioctl_evtchn_unbind {
	unsigned int port;
};

/*
 * Unbind previously allocated @port.
 */
#define IOCTL_EVTCHN_NOTIFY				\
	_IOC(_IOC_NONE, 'E', 4, sizeof(struct ioctl_evtchn_notify))
struct ioctl_evtchn_notify {
	unsigned int port;
};

/* Clear and reinitialise the event buffer. Clear error condition. */
#define IOCTL_EVTCHN_RESET				\
	_IOC(_IOC_NONE, 'E', 5, 0)

#endif /* __BEEP_PUBLIC_EVTCHN_H__ */
