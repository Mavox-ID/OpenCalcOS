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
#ifndef __MG_DISK_H__
#define __MG_DISK_H__

/* name for platform device */
#define MG_DEV_NAME "mg_disk"

/* names of GPIO resource */
#define MG_RST_PIN	"mg_rst"
/* except MG_BOOT_DEV, reset-out pin should be assigned */
#define MG_RSTOUT_PIN	"mg_rstout"

/* device attribution */
/* use mflash as boot device */
#define MG_BOOT_DEV		(1 << 0)
/* use mflash as storage device */
#define MG_STORAGE_DEV		(1 << 1)
/* same as MG_STORAGE_DEV, but bootloader already done reset sequence */
#define MG_STORAGE_DEV_SKIP_RST	(1 << 2)

/* private driver data */
struct mg_drv_data {
	/* disk resource */
	u32 use_polling;

	/* device attribution */
	u32 dev_attr;

	/* internally used */
	void *host;
};

#endif
