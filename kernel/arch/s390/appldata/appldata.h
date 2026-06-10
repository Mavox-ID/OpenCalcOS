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
#define APPLDATA_MAX_REC_SIZE	  4024	/* Maximum size of the */
					/* data buffer */
#define APPLDATA_MAX_PROCS 100

#define APPLDATA_PROC_NAME_LENGTH 16	/* Max. length of /proc name */

#define APPLDATA_RECORD_MEM_ID		0x01	/* IDs to identify the */
#define APPLDATA_RECORD_OS_ID		0x02	/* individual records, */
#define APPLDATA_RECORD_NET_SUM_ID	0x03	/* must be < 256 !     */
#define APPLDATA_RECORD_PROC_ID		0x04

#define CTL_APPLDATA_TIMER 	2121	/* sysctl IDs, must be unique */
#define CTL_APPLDATA_INTERVAL 	2122
#define CTL_APPLDATA_MEM	2123
#define CTL_APPLDATA_OS		2124
#define CTL_APPLDATA_NET_SUM	2125
#define CTL_APPLDATA_PROC	2126

struct appldata_ops {
	struct list_head list;
	struct ctl_table_header *sysctl_header;
	struct ctl_table *ctl_table;
	int    active;				/* monitoring status */

	/* fill in from here */
	char name[APPLDATA_PROC_NAME_LENGTH];	/* name of /proc fs node */
	unsigned char record_nr;		/* Record Nr. for Product ID */
	void (*callback)(void *data);		/* callback function */
	void *data;				/* record data */
	unsigned int size;			/* size of record */
	struct module *owner;			/* THIS_MODULE */
	char mod_lvl[2];			/* modification level, EBCDIC */
};

extern int appldata_register_ops(struct appldata_ops *ops);
extern void appldata_unregister_ops(struct appldata_ops *ops);
extern int appldata_diag(char record_nr, u16 function, unsigned long buffer,
			 u16 length, char *mod_lvl);

