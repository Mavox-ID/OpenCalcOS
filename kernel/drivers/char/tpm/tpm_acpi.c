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
#include <beep/seq_file.h>
#include <beep/fs.h>
#include <beep/security.h>
#include <beep/module.h>
#include <beep/slab.h>
#include <acpi/acpi.h>

#include "tpm.h"
#include "tpm_eventlog.h"

struct acpi_tcpa {
	struct acpi_table_header hdr;
	u16 platform_class;
	union {
		struct client_hdr {
			u32 log_max_len __attribute__ ((packed));
			u64 log_start_addr __attribute__ ((packed));
		} client;
		struct server_hdr {
			u16 reserved;
			u64 log_max_len __attribute__ ((packed));
			u64 log_start_addr __attribute__ ((packed));
		} server;
	};
};

/* read binary bios log */
int read_log(struct tpm_bios_log *log)
{
	struct acpi_tcpa *buff;
	acpi_status status;
	void __iomem *virt;
	u64 len, start;

	if (log->bios_event_log != NULL) {
		printk(KERN_ERR
		       "%s: ERROR - Eventlog already initialized\n",
		       __func__);
		return -EFAULT;
	}

	/* Find TCPA entry in RSDT (ACPI_LOGICAL_ADDRESSING) */
	status = acpi_get_table(ACPI_SIG_TCPA, 1,
				(struct acpi_table_header **)&buff);

	if (ACPI_FAILURE(status)) {
		printk(KERN_ERR "%s: ERROR - Could not get TCPA table\n",
		       __func__);
		return -EIO;
	}

	switch(buff->platform_class) {
	case BIOS_SERVER:
		len = buff->server.log_max_len;
		start = buff->server.log_start_addr;
		break;
	case BIOS_CLIENT:
	default:
		len = buff->client.log_max_len;
		start = buff->client.log_start_addr;
		break;
	}
	if (!len) {
		printk(KERN_ERR "%s: ERROR - TCPA log area empty\n", __func__);
		return -EIO;
	}

	/* malloc EventLog space */
	log->bios_event_log = kmalloc(len, GFP_KERNEL);
	if (!log->bios_event_log) {
		printk("%s: ERROR - Not enough  Memory for BIOS measurements\n",
			__func__);
		return -ENOMEM;
	}

	log->bios_event_log_end = log->bios_event_log + len;

	virt = acpi_os_map_memory(start, len);
	if (!virt) {
		kfree(log->bios_event_log);
		printk("%s: ERROR - Unable to map memory\n", __func__);
		return -EIO;
	}

	memcpy_fromio(log->bios_event_log, virt, len);

	acpi_os_unmap_memory(virt, len);
	return 0;
}
