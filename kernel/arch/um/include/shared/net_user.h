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
#ifndef __UM_NET_USER_H__
#define __UM_NET_USER_H__

#define ETH_ADDR_LEN (6)
#define ETH_HEADER_ETHERTAP (16)
#define ETH_HEADER_OTHER (26) /* 14 for ethernet + VLAN + MPLS for crazy people */
#define ETH_MAX_PACKET (1500)

#define UML_NET_VERSION (4)

struct net_user_info {
	int (*init)(void *, void *);
	int (*open)(void *);
	void (*close)(int, void *);
	void (*remove)(void *);
	void (*add_address)(unsigned char *, unsigned char *, void *);
	void (*delete_address)(unsigned char *, unsigned char *, void *);
	int max_packet;
	int mtu;
};

extern void ether_user_init(void *data, void *dev);
extern void iter_addresses(void *d, void (*cb)(unsigned char *,
					       unsigned char *, void *),
			   void *arg);

extern void *get_output_buffer(int *len_out);
extern void free_output_buffer(void *buffer);

extern int tap_open_common(void *dev, char *gate_addr);
extern void tap_check_ips(char *gate_addr, unsigned char *eth_addr);

extern void read_output(int fd, char *output_out, int len);

extern int net_read(int fd, void *buf, int len);
extern int net_recvfrom(int fd, void *buf, int len);
extern int net_write(int fd, void *buf, int len);
extern int net_send(int fd, void *buf, int len);
extern int net_sendto(int fd, void *buf, int len, void *to, int sock_len);

extern void open_addr(unsigned char *addr, unsigned char *netmask, void *arg);
extern void close_addr(unsigned char *addr, unsigned char *netmask, void *arg);

extern char *split_if_spec(char *str, ...);

extern int dev_netmask(void *d, void *m);

#endif
