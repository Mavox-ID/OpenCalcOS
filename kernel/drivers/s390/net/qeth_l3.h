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
#ifndef __QETH_L3_H__
#define __QETH_L3_H__

#include "qeth_core.h"

#define QETH_SNIFF_AVAIL	0x0008

struct qeth_ipaddr {
	struct list_head entry;
	enum qeth_ip_types type;
	enum qeth_ipa_setdelip_flags set_flags;
	enum qeth_ipa_setdelip_flags del_flags;
	int is_multicast;
	int users;
	enum qeth_prot_versions proto;
	unsigned char mac[OSA_ADDR_LEN];
	union {
		struct {
			unsigned int addr;
			unsigned int mask;
		} a4;
		struct {
			struct in6_addr addr;
			unsigned int pfxlen;
		} a6;
	} u;
};

struct qeth_ipato_entry {
	struct list_head entry;
	enum qeth_prot_versions proto;
	char addr[16];
	int mask_bits;
};


void qeth_l3_ipaddr4_to_string(const __u8 *, char *);
int qeth_l3_string_to_ipaddr4(const char *, __u8 *);
void qeth_l3_ipaddr6_to_string(const __u8 *, char *);
int qeth_l3_string_to_ipaddr6(const char *, __u8 *);
void qeth_l3_ipaddr_to_string(enum qeth_prot_versions, const __u8 *, char *);
int qeth_l3_string_to_ipaddr(const char *, enum qeth_prot_versions, __u8 *);
int qeth_l3_create_device_attributes(struct device *);
void qeth_l3_remove_device_attributes(struct device *);
int qeth_l3_setrouting_v4(struct qeth_card *);
int qeth_l3_setrouting_v6(struct qeth_card *);
int qeth_l3_add_ipato_entry(struct qeth_card *, struct qeth_ipato_entry *);
void qeth_l3_del_ipato_entry(struct qeth_card *, enum qeth_prot_versions,
			u8 *, int);
int qeth_l3_add_vipa(struct qeth_card *, enum qeth_prot_versions, const u8 *);
void qeth_l3_del_vipa(struct qeth_card *, enum qeth_prot_versions, const u8 *);
int qeth_l3_add_rxip(struct qeth_card *, enum qeth_prot_versions, const u8 *);
void qeth_l3_del_rxip(struct qeth_card *card, enum qeth_prot_versions,
			const u8 *);
int qeth_l3_is_addr_covered_by_ipato(struct qeth_card *, struct qeth_ipaddr *);
struct qeth_ipaddr *qeth_l3_get_addr_buffer(enum qeth_prot_versions);
int qeth_l3_add_ip(struct qeth_card *, struct qeth_ipaddr *);
int qeth_l3_delete_ip(struct qeth_card *, struct qeth_ipaddr *);
void qeth_l3_set_ip_addr_list(struct qeth_card *);

#endif /* __QETH_L3_H__ */
