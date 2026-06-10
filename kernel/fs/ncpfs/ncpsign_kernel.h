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
#ifndef _NCPSIGN_KERNEL_H
#define _NCPSIGN_KERNEL_H

#ifdef CONFIG_NCPFS_PACKET_SIGNING
void __sign_packet(struct ncp_server *server, const char *data, size_t size, __u32 totalsize, void *sign_buff);
int sign_verify_reply(struct ncp_server *server, const char *data, size_t size, __u32 totalsize, const void *sign_buff);
#endif

static inline size_t sign_packet(struct ncp_server *server, const char *data, size_t size, __u32 totalsize, void *sign_buff) {
#ifdef CONFIG_NCPFS_PACKET_SIGNING
	if (server->sign_active) {
		__sign_packet(server, data, size, totalsize, sign_buff);
		return 8;
	}
#endif
	return 0;
}

#endif
