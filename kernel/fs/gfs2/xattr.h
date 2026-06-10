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
#ifndef __EATTR_DOT_H__
#define __EATTR_DOT_H__

struct gfs2_inode;
struct iattr;

#define GFS2_EA_REC_LEN(ea) be32_to_cpu((ea)->ea_rec_len)
#define GFS2_EA_DATA_LEN(ea) be32_to_cpu((ea)->ea_data_len)

#define GFS2_EA_SIZE(ea) \
ALIGN(sizeof(struct gfs2_ea_header) + (ea)->ea_name_len + \
      ((GFS2_EA_IS_STUFFED(ea)) ? GFS2_EA_DATA_LEN(ea) : \
				  (sizeof(__be64) * (ea)->ea_num_ptrs)), 8)

#define GFS2_EA_IS_STUFFED(ea) (!(ea)->ea_num_ptrs)
#define GFS2_EA_IS_LAST(ea) ((ea)->ea_flags & GFS2_EAFLAG_LAST)

#define GFS2_EAREQ_SIZE_STUFFED(er) \
ALIGN(sizeof(struct gfs2_ea_header) + (er)->er_name_len + (er)->er_data_len, 8)

#define GFS2_EA2NAME(ea) ((char *)((struct gfs2_ea_header *)(ea) + 1))
#define GFS2_EA2DATA(ea) (GFS2_EA2NAME(ea) + (ea)->ea_name_len)

#define GFS2_EA2DATAPTRS(ea) \
((__be64 *)(GFS2_EA2NAME(ea) + ALIGN((ea)->ea_name_len, 8)))

#define GFS2_EA2NEXT(ea) \
((struct gfs2_ea_header *)((char *)(ea) + GFS2_EA_REC_LEN(ea)))

#define GFS2_EA_BH2FIRST(bh) \
((struct gfs2_ea_header *)((bh)->b_data + sizeof(struct gfs2_meta_header)))

struct gfs2_ea_request {
	const char *er_name;
	char *er_data;
	unsigned int er_name_len;
	unsigned int er_data_len;
	unsigned int er_type; /* GFS2_EATYPE_... */
};

struct gfs2_ea_location {
	struct buffer_head *el_bh;
	struct gfs2_ea_header *el_ea;
	struct gfs2_ea_header *el_prev;
};

extern int __gfs2_xattr_set(struct inode *inode, const char *name,
			    const void *value, size_t size,
			    int flags, int type);
extern ssize_t gfs2_listxattr(struct dentry *dentry, char *buffer, size_t size);
extern int gfs2_ea_dealloc(struct gfs2_inode *ip);

/* Exported to acl.c */

extern int gfs2_xattr_acl_get(struct gfs2_inode *ip, const char *name, char **data);
extern int gfs2_xattr_acl_chmod(struct gfs2_inode *ip, struct iattr *attr, char *data);

#endif /* __EATTR_DOT_H__ */
