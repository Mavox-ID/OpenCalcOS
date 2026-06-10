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
#ifndef _COMEDI_COMPAT32_H
#define _COMEDI_COMPAT32_H

#ifdef CONFIG_COMPAT

struct file;
extern long comedi_compat_ioctl(struct file *file, unsigned int cmd,
				unsigned long arg);

#else /* CONFIG_COMPAT */

#define comedi_compat_ioctl	NULL

#endif /* CONFIG_COMPAT */

#endif /* _COMEDI_COMPAT32_H */
