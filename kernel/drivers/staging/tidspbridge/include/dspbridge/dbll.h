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
#ifndef DBLL_
#define DBLL_

#include <dspbridge/dbdefs.h>
#include <dspbridge/dblldefs.h>

extern bool symbols_reloaded;

extern void dbll_close(struct dbll_library_obj *zl_lib);
extern int dbll_create(struct dbll_tar_obj **target_obj,
			      struct dbll_attrs *pattrs);
extern void dbll_delete(struct dbll_tar_obj *target);
extern void dbll_exit(void);
extern bool dbll_get_addr(struct dbll_library_obj *zl_lib, char *name,
			  struct dbll_sym_val **sym_val);
extern void dbll_get_attrs(struct dbll_tar_obj *target,
			   struct dbll_attrs *pattrs);
extern bool dbll_get_c_addr(struct dbll_library_obj *zl_lib, char *name,
			    struct dbll_sym_val **sym_val);
extern int dbll_get_sect(struct dbll_library_obj *lib, char *name,
				u32 *paddr, u32 *psize);
extern bool dbll_init(void);
extern int dbll_load(struct dbll_library_obj *lib,
			    dbll_flags flags,
			    struct dbll_attrs *attrs, u32 * entry);
extern int dbll_open(struct dbll_tar_obj *target, char *file,
			    dbll_flags flags,
		       struct dbll_library_obj **lib_obj);
extern int dbll_read_sect(struct dbll_library_obj *lib,
				 char *name, char *buf, u32 size);
extern void dbll_unload(struct dbll_library_obj *lib, struct dbll_attrs *attrs);
#ifdef CONFIG_TIDSPBRIDGE_BACKTRACE
bool dbll_find_dsp_symbol(struct dbll_library_obj *zl_lib, u32 address,
		u32 offset_range, u32 *sym_addr_output, char *name_output);
#endif

#endif /* DBLL_ */
