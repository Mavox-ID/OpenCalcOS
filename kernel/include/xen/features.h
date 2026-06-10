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
#ifndef __XEN_FEATURES_H__
#define __XEN_FEATURES_H__

#include <xen/interface/features.h>

void xen_setup_features(void);

extern u8 xen_features[XENFEAT_NR_SUBMAPS * 32];

static inline int xen_feature(int flag)
{
	return xen_features[flag];
}

#endif /* __ASM_XEN_FEATURES_H__ */
