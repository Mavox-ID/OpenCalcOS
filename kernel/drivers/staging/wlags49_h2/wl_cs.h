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
#ifndef __WL_CS_H__
#define __WL_CS_H__




/*******************************************************************************
 *  function protoypes
 ******************************************************************************/

void wl_adapter_insert(struct pcmcia_device *link);

void wl_adapter_release(struct pcmcia_device *link);

int wl_adapter_init_module( void );

void wl_adapter_cleanup_module( void );

int wl_adapter_open(struct net_device *dev);

int wl_adapter_close(struct net_device *dev);

int wl_adapter_is_open(struct net_device *dev);

const char *DbgEvent( int mask );



#endif  // __WL_CS_H__
