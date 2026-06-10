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
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/errno.h>

#include <asm/hwrpb.h>
#include <asm/gct.h>

int
gct6_find_nodes(gct6_node *node, gct6_search_struct *search)
{
	gct6_search_struct *wanted;
	int status = 0;

	/* First check the magic number.  */
	if (node->magic != GCT_NODE_MAGIC) {
		printk(KERN_ERR "GCT Node MAGIC incorrect - GCT invalid\n");
		return -EINVAL;
	}

	/* Check against the search struct.  */
	for (wanted = search; 
	     wanted && (wanted->type | wanted->subtype); 
	     wanted++) {
		if (node->type != wanted->type)
			continue;
		if (node->subtype != wanted->subtype)
			continue;

		/* Found it -- call out.  */
		if (wanted->callout)
			wanted->callout(node);
	}

	/* Now walk the tree, siblings first.  */
	if (node->next) 
		status |= gct6_find_nodes(GCT_NODE_PTR(node->next), search);

	/* Then the children.  */
	if (node->child) 
		status |= gct6_find_nodes(GCT_NODE_PTR(node->child), search);

	return status;
}
