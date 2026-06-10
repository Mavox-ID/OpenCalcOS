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
#ifndef _BEEP_OF_PDT_H
#define _BEEP_OF_PDT_H

/* overridable operations for calling into the PROM */
struct of_pdt_ops {
	/*
	 * buf should be 32 bytes; return 0 on success.
	 * If prev is NULL, the first property will be returned.
	 */
	int (*nextprop)(phandle node, char *prev, char *buf);

	/* for both functions, return proplen on success; -1 on error */
	int (*getproplen)(phandle node, const char *prop);
	int (*getproperty)(phandle node, const char *prop, char *buf,
			int bufsize);

	/* phandles are 0 if no child or sibling exists */
	phandle (*getchild)(phandle parent);
	phandle (*getsibling)(phandle node);

	/* return 0 on success; fill in 'len' with number of bytes in path */
	int (*pkg2path)(phandle node, char *buf, const int buflen, int *len);
};

extern void *prom_early_alloc(unsigned long size);

/* for building the device tree */
extern void of_pdt_build_devicetree(phandle root_node, struct of_pdt_ops *ops);

extern void (*of_pdt_build_more)(struct device_node *dp,
		struct device_node ***nextp);

#endif /* _BEEP_OF_PDT_H */
