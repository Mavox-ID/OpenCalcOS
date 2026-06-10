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
#ifndef __ASM_ARCH_USBCONTROL_H
#define __ASM_ARCH_USBCONTROL_H

#define S3C_HCDFLG_USED	(1)

struct s3c2410_hcd_port {
	unsigned char	flags;
	unsigned char	power;
	unsigned char	oc_status;
	unsigned char	oc_changed;
};

struct s3c2410_hcd_info {
	struct usb_hcd		*hcd;
	struct s3c2410_hcd_port	port[2];

	void		(*power_control)(int port, int to);
	void		(*enable_oc)(struct s3c2410_hcd_info *, int on);
	void		(*report_oc)(struct s3c2410_hcd_info *, int ports);
};

static void inline s3c2410_usb_report_oc(struct s3c2410_hcd_info *info, int ports)
{
	if (info->report_oc != NULL) {
		(info->report_oc)(info, ports);
	}
}

extern void s3c_ohci_set_platdata(struct s3c2410_hcd_info *info);

#endif /*__ASM_ARCH_USBCONTROL_H */
