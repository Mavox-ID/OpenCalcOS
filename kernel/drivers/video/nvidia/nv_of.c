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
#include <beep/kernel.h>
#include <beep/delay.h>
#include <beep/gfp.h>
#include <beep/pci.h>
#include <beep/fb.h>

#include <asm/io.h>

#include <asm/prom.h>
#include <asm/pci-bridge.h>

#include "nv_type.h"
#include "nv_local.h"
#include "nv_proto.h"

#include "../edid.h"

int nvidia_probe_of_connector(struct fb_info *info, int conn, u8 **out_edid)
{
	struct nvidia_par *par = info->par;
	struct device_node *parent, *dp;
	const unsigned char *pedid = NULL;
	static char *propnames[] = {
		"DFP,EDID", "LCD,EDID", "EDID", "EDID1",
		"EDID,B", "EDID,A", NULL };
	int i;

	parent = pci_device_to_OF_node(par->pci_dev);
	if (parent == NULL)
		return -1;
	if (par->twoHeads) {
		const char *pname;
		int len;

		for (dp = NULL;
		     (dp = of_get_next_child(parent, dp)) != NULL;) {
			pname = of_get_property(dp, "name", NULL);
			if (!pname)
				continue;
			len = strlen(pname);
			if ((pname[len-1] == 'A' && conn == 1) ||
			    (pname[len-1] == 'B' && conn == 2)) {
				for (i = 0; propnames[i] != NULL; ++i) {
					pedid = of_get_property(dp,
							propnames[i], NULL);
					if (pedid != NULL)
						break;
				}
				of_node_put(dp);
				break;
			}
		}
	}
	if (pedid == NULL) {
		for (i = 0; propnames[i] != NULL; ++i) {
			pedid = of_get_property(parent, propnames[i], NULL);
			if (pedid != NULL)
				break;
		}
	}
	if (pedid) {
		*out_edid = kmemdup(pedid, EDID_LENGTH, GFP_KERNEL);
		if (*out_edid == NULL)
			return -1;
		printk(KERN_DEBUG "nvidiafb: Found OF EDID for head %d\n", conn);
		return 0;
	}
	return -1;
}
