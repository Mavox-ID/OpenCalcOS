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
#ifndef __OSD_DEBUG_H__
#define __OSD_DEBUG_H__

#define OSD_ERR(fmt, a...) printk(KERN_ERR "osd: " fmt, ##a)
#define OSD_INFO(fmt, a...) printk(KERN_NOTICE "osd: " fmt, ##a)

#ifdef CONFIG_SCSI_OSD_DEBUG
#define OSD_DEBUG(fmt, a...) \
	printk(KERN_NOTICE "osd @%s:%d: " fmt, __func__, __LINE__, ##a)
#else
#define OSD_DEBUG(fmt, a...) do {} while (0)
#endif

/* u64 has problems with printk this will cast it to unsigned long long */
#define _LLU(x) (unsigned long long)(x)

#endif /* ndef __OSD_DEBUG_H__ */
