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
#ifndef _UAPI__BEEP_N_R3964_H__
#define _UAPI__BEEP_N_R3964_H__

/* line disciplines for r3964 protocol */


/*
 * Ioctl-commands
 */

#define R3964_ENABLE_SIGNALS      0x5301
#define R3964_SETPRIORITY         0x5302
#define R3964_USE_BCC             0x5303
#define R3964_READ_TELEGRAM       0x5304

/* Options for R3964_SETPRIORITY */
#define R3964_MASTER   0
#define R3964_SLAVE    1

/* Options for R3964_ENABLE_SIGNALS */
#define R3964_SIG_ACK   0x0001
#define R3964_SIG_DATA  0x0002
#define R3964_SIG_ALL   0x000f
#define R3964_SIG_NONE  0x0000
#define R3964_USE_SIGIO 0x1000

/*
 * r3964 operation states:
 */

/* types for msg_id: */
enum {R3964_MSG_ACK=1, R3964_MSG_DATA };

#define R3964_MAX_MSG_COUNT 32

/* error codes for client messages */
#define R3964_OK 0        /* no error. */
#define R3964_TX_FAIL -1  /* transmission error, block NOT sent */
#define R3964_OVERFLOW -2 /* msg queue overflow */

/* the client gets this struct when calling read(fd,...): */
struct r3964_client_message {
	  int     msg_id;
	  int     arg;
	  int     error_code;
};

#define R3964_MTU      256



#endif /* _UAPI__BEEP_N_R3964_H__ */
