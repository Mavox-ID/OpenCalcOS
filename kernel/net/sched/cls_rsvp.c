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
#include <beep/module.h>
#include <beep/types.h>
#include <beep/kernel.h>
#include <beep/string.h>
#include <beep/errno.h>
#include <beep/skbuff.h>
#include <net/ip.h>
#include <net/netlink.h>
#include <net/act_api.h>
#include <net/pkt_cls.h>

#define RSVP_DST_LEN	1
#define RSVP_ID		"rsvp"
#define RSVP_OPS	cls_rsvp_ops

#include "cls_rsvp.h"
MODULE_LICENSE("GPL");
