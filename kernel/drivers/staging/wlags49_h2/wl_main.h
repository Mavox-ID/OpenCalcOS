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
#ifndef __WL_MAIN_H__
#define __WL_MAIN_H__




/*******************************************************************************
 *  function prototypes
 ******************************************************************************/
int wl_insert( struct net_device *dev );

void wl_set_wep_keys( struct wl_private *lp );

int wl_put_ltv_init( struct wl_private *lp );

int wl_put_ltv( struct wl_private *lp );

p_u16 wl_get_irq_mask( void );

p_s8 * wl_get_irq_list( void );

int wl_reset( struct net_device *dev );

int wl_go( struct wl_private *lp );

int wl_apply( struct wl_private *lp );

irqreturn_t wl_isr( int irq, void *dev_id, struct pt_regs *regs );

void wl_remove( struct net_device *dev );

void wl_suspend( struct net_device *dev );

void wl_resume( struct net_device *dev );

void wl_release( struct net_device *dev );

int wl_enable( struct wl_private *lp );

int wl_connect( struct wl_private *lp );

int wl_disable( struct wl_private *lp );

int wl_disconnect( struct wl_private *lp );

void wl_enable_wds_ports( struct wl_private * lp );

void wl_disable_wds_ports( struct wl_private * lp );

#ifndef USE_MBOX_SYNC

int wl_mbx( struct wl_private *lp );
void wl_endian_translate_mailbox( ltv_t *ltv );
void wl_process_mailbox( struct wl_private *lp );

#endif  /* USE_MBOX_SYNC */


#ifdef USE_WDS

void wl_wds_netdev_register( struct wl_private *lp );
void wl_wds_netdev_deregister( struct wl_private *lp );

#endif  /* USE_WDS */


#ifdef USE_WDS

#define WL_WDS_NETDEV_REGISTER( ARG )   wl_wds_netdev_register( ARG )
#define WL_WDS_NETDEV_DEREGISTER( ARG ) wl_wds_netdev_deregister( ARG )

#else

#define WL_WDS_NETDEV_REGISTER( ARG )
#define WL_WDS_NETDEV_DEREGISTER( ARG )

#endif  /* USE_WDS */
#endif  // __WL_MAIN_H__
