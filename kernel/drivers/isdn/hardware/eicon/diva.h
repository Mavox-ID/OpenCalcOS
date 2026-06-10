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
#ifndef __DIVA_XDI_OS_PART_H__
#define __DIVA_XDI_OS_PART_H__


int divasa_xdi_driver_entry(void);
void divasa_xdi_driver_unload(void);
void *diva_driver_add_card(void *pdev, unsigned long CardOrdinal);
void diva_driver_remove_card(void *pdiva);

typedef int (*divas_xdi_copy_to_user_fn_t) (void *os_handle, void __user *dst,
					    const void *src, int length);

typedef int (*divas_xdi_copy_from_user_fn_t) (void *os_handle, void *dst,
					      const void __user *src, int length);

int diva_xdi_read(void *adapter, void *os_handle, void __user *dst,
		  int max_length, divas_xdi_copy_to_user_fn_t cp_fn);

int diva_xdi_write(void *adapter, void *os_handle, const void __user *src,
		   int length, divas_xdi_copy_from_user_fn_t cp_fn);

void *diva_xdi_open_adapter(void *os_handle, const void __user *src,
			    int length,
			    divas_xdi_copy_from_user_fn_t cp_fn);

void diva_xdi_close_adapter(void *adapter, void *os_handle);


#endif
