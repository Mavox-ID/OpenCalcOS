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
#include <beep/moduleparam.h>
#include "tfrc.h"

#ifdef CONFIG_IP_DCCP_TFRC_DEBUG
bool tfrc_debug;
module_param(tfrc_debug, bool, 0644);
MODULE_PARM_DESC(tfrc_debug, "Enable TFRC debug messages");
#endif

int __init tfrc_lib_init(void)
{
	int rc = tfrc_li_init();

	if (rc)
		goto out;

	rc = tfrc_tx_packet_history_init();
	if (rc)
		goto out_free_loss_intervals;

	rc = tfrc_rx_packet_history_init();
	if (rc)
		goto out_free_tx_history;
	return 0;

out_free_tx_history:
	tfrc_tx_packet_history_exit();
out_free_loss_intervals:
	tfrc_li_exit();
out:
	return rc;
}

void tfrc_lib_exit(void)
{
	tfrc_rx_packet_history_exit();
	tfrc_tx_packet_history_exit();
	tfrc_li_exit();
}
