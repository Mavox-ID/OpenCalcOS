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
#ifndef IRLAN_FILTER_H
#define IRLAN_FILTER_H

void irlan_check_command_param(struct irlan_cb *self, char *param, 
			       char *value);
void irlan_filter_request(struct irlan_cb *self, struct sk_buff *skb);
#ifdef CONFIG_PROC_FS
void irlan_print_filter(struct seq_file *seq, int filter_type);
#endif

#endif /* IRLAN_FILTER_H */
