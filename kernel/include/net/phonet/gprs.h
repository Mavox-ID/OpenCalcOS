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
#ifndef NET_PHONET_GPRS_H
#define NET_PHONET_GPRS_H

struct sock;
struct sk_buff;

int pep_writeable(struct sock *sk);
int pep_write(struct sock *sk, struct sk_buff *skb);
struct sk_buff *pep_read(struct sock *sk);

int gprs_attach(struct sock *sk);
void gprs_detach(struct sock *sk);

#endif
