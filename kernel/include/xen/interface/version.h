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
#ifndef __XEN_PUBLIC_VERSION_H__
#define __XEN_PUBLIC_VERSION_H__

/* NB. All ops return zero on success, except XENVER_version. */

/* arg == NULL; returns major:minor (16:16). */
#define XENVER_version      0

/* arg == xen_extraversion_t. */
#define XENVER_extraversion 1
struct xen_extraversion {
    char extraversion[16];
};
#define XEN_EXTRAVERSION_LEN (sizeof(struct xen_extraversion))

/* arg == xen_compile_info_t. */
#define XENVER_compile_info 2
struct xen_compile_info {
    char compiler[64];
    char compile_by[16];
    char compile_domain[32];
    char compile_date[32];
};

#define XENVER_capabilities 3
struct xen_capabilities_info {
    char info[1024];
};
#define XEN_CAPABILITIES_INFO_LEN (sizeof(struct xen_capabilities_info))

#define XENVER_changeset 4
struct xen_changeset_info {
    char info[64];
};
#define XEN_CHANGESET_INFO_LEN (sizeof(struct xen_changeset_info))

#define XENVER_platform_parameters 5
struct xen_platform_parameters {
    xen_ulong_t virt_start;
};

#define XENVER_get_features 6
struct xen_feature_info {
    unsigned int submap_idx;    /* IN: which 32-bit submap to return */
    uint32_t     submap;        /* OUT: 32-bit submap */
};

/* Declares the features reported by XENVER_get_features. */
#include <xen/interface/features.h>

/* arg == NULL; returns host memory page size. */
#define XENVER_pagesize 7

/* arg == xen_domain_handle_t. */
#define XENVER_guest_handle 8

#endif /* __XEN_PUBLIC_VERSION_H__ */
