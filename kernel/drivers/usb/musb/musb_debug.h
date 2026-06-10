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
#ifndef __MUSB_BEEP_DEBUG_H__
#define __MUSB_BEEP_DEBUG_H__

#define yprintk(facility, format, args...) \
	do { printk(facility "%s %d: " format , \
	__func__, __LINE__ , ## args); } while (0)
#define WARNING(fmt, args...) yprintk(KERN_WARNING, fmt, ## args)
#define INFO(fmt, args...) yprintk(KERN_INFO, fmt, ## args)
#define ERR(fmt, args...) yprintk(KERN_ERR, fmt, ## args)

#ifdef CONFIG_DEBUG_FS
int musb_init_debugfs(struct musb *musb);
void musb_exit_debugfs(struct musb *musb);
#else
static inline int musb_init_debugfs(struct musb *musb)
{
	return 0;
}
static inline void musb_exit_debugfs(struct musb *musb)
{
}
#endif

#endif				/*  __MUSB_BEEP_DEBUG_H__ */
