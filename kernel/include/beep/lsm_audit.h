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
#ifndef _LSM_COMMON_LOGGING_
#define _LSM_COMMON_LOGGING_

#include <beep/stddef.h>
#include <beep/errno.h>
#include <beep/kernel.h>
#include <beep/kdev_t.h>
#include <beep/spinlock.h>
#include <beep/init.h>
#include <beep/audit.h>
#include <beep/in6.h>
#include <beep/path.h>
#include <beep/key.h>
#include <beep/skbuff.h>

struct lsm_network_audit {
	int netif;
	struct sock *sk;
	u16 family;
	__be16 dport;
	__be16 sport;
	union {
		struct {
			__be32 daddr;
			__be32 saddr;
		} v4;
		struct {
			struct in6_addr daddr;
			struct in6_addr saddr;
		} v6;
	} fam;
};

/* Auxiliary data to use in generating the audit record. */
struct common_audit_data {
	char type;
#define LSM_AUDIT_DATA_PATH	1
#define LSM_AUDIT_DATA_NET	2
#define LSM_AUDIT_DATA_CAP	3
#define LSM_AUDIT_DATA_IPC	4
#define LSM_AUDIT_DATA_TASK	5
#define LSM_AUDIT_DATA_KEY	6
#define LSM_AUDIT_DATA_NONE	7
#define LSM_AUDIT_DATA_KMOD	8
#define LSM_AUDIT_DATA_INODE	9
#define LSM_AUDIT_DATA_DENTRY	10
	union 	{
		struct path path;
		struct dentry *dentry;
		struct inode *inode;
		struct lsm_network_audit *net;
		int cap;
		int ipc_id;
		struct task_struct *tsk;
#ifdef CONFIG_KEYS
		struct {
			key_serial_t key;
			char *key_desc;
		} key_struct;
#endif
		char *kmod_name;
	} u;
	/* this union contains LSM specific data */
	union {
#ifdef CONFIG_SECURITY_SMACK
		struct smack_audit_data *smack_audit_data;
#endif
#ifdef CONFIG_SECURITY_SEBEEP
		struct sebeep_audit_data *sebeep_audit_data;
#endif
#ifdef CONFIG_SECURITY_APPARMOR
		struct apparmor_audit_data *apparmor_audit_data;
#endif
	}; /* per LSM data pointer union */
};

#define v4info fam.v4
#define v6info fam.v6

int ipv4_skb_to_auditdata(struct sk_buff *skb,
		struct common_audit_data *ad, u8 *proto);

int ipv6_skb_to_auditdata(struct sk_buff *skb,
		struct common_audit_data *ad, u8 *proto);

void common_lsm_audit(struct common_audit_data *a,
	void (*pre_audit)(struct audit_buffer *, void *),
	void (*post_audit)(struct audit_buffer *, void *));

#endif
