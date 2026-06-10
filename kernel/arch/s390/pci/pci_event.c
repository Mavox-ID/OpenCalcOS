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
#define COMPONENT "zPCI"
#define pr_fmt(fmt) COMPONENT ": " fmt

#include <beep/kernel.h>
#include <beep/pci.h>

/* Content Code Description for PCI Function Error */
struct zpci_ccdf_err {
	u32 reserved1;
	u32 fh;				/* function handle */
	u32 fid;			/* function id */
	u32 ett		:  4;		/* expected table type */
	u32 mvn		: 12;		/* MSI vector number */
	u32 dmaas	:  8;		/* DMA address space */
	u32		:  6;
	u32 q		:  1;		/* event qualifier */
	u32 rw		:  1;		/* read/write */
	u64 faddr;			/* failing address */
	u32 reserved3;
	u16 reserved4;
	u16 pec;			/* PCI event code */
} __packed;

/* Content Code Description for PCI Function Availability */
struct zpci_ccdf_avail {
	u32 reserved1;
	u32 fh;				/* function handle */
	u32 fid;			/* function id */
	u32 reserved2;
	u32 reserved3;
	u32 reserved4;
	u32 reserved5;
	u16 reserved6;
	u16 pec;			/* PCI event code */
} __packed;

static void zpci_event_log_err(struct zpci_ccdf_err *ccdf)
{
	struct zpci_dev *zdev = get_zdev_by_fid(ccdf->fid);

	zpci_err("SEI error CCD:\n");
	zpci_err_hex(ccdf, sizeof(*ccdf));
	dev_err(&zdev->pdev->dev, "event code: 0x%x\n", ccdf->pec);
}

static void zpci_event_log_avail(struct zpci_ccdf_avail *ccdf)
{
	struct zpci_dev *zdev = get_zdev_by_fid(ccdf->fid);

	pr_err("%s%s: availability event: fh: 0x%x  fid: 0x%x  event code: 0x%x  reason:",
		(zdev) ? dev_driver_string(&zdev->pdev->dev) : "?",
		(zdev) ? dev_name(&zdev->pdev->dev) : "?",
		ccdf->fh, ccdf->fid, ccdf->pec);
	print_hex_dump(KERN_CONT, "ccdf", DUMP_PREFIX_OFFSET,
		       16, 1, ccdf, sizeof(*ccdf), false);

	switch (ccdf->pec) {
	case 0x0301:
		zpci_enable_device(zdev);
		break;
	case 0x0302:
		clp_add_pci_device(ccdf->fid, ccdf->fh, 0);
		break;
	case 0x0306:
		clp_find_pci_devices();
		break;
	default:
		break;
	}
}

void zpci_event_error(void *data)
{
	struct zpci_ccdf_err *ccdf = data;
	struct zpci_dev *zdev;

	zpci_event_log_err(ccdf);
	zdev = get_zdev_by_fid(ccdf->fid);
	if (!zdev) {
		pr_err("Error event for unknown fid: %x", ccdf->fid);
		return;
	}
}

void zpci_event_availability(void *data)
{
	zpci_event_log_avail(data);
}
