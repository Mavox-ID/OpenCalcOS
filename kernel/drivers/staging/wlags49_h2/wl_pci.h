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
#ifndef __WL_PCI_H__
#define __WL_PCI_H__




/*******************************************************************************
 *  constant definitions
 ******************************************************************************/
#define PCI_VENDOR_IDWL_LKM     0x11C1  /* Lucent Microelectronics */
#define PCI_DEVICE_ID_WL_LKM_0  0xAB30  /* Mini PCI */
#define PCI_DEVICE_ID_WL_LKM_1  0xAB34  /* Mini PCI */
#define PCI_DEVICE_ID_WL_LKM_2  0xAB11  /* WARP CardBus */




/*******************************************************************************
 *  function prototypes
 ******************************************************************************/
int wl_adapter_init_module( void );

void wl_adapter_cleanup_module( void );

int wl_adapter_insert( struct net_device *dev );

int wl_adapter_open( struct net_device *dev );

int wl_adapter_close( struct net_device *dev );

int wl_adapter_is_open( struct net_device *dev );


#ifdef ENABLE_DMA

void wl_pci_dma_hcf_supply( struct wl_private *lp );

void wl_pci_dma_hcf_reclaim( struct wl_private *lp );

DESC_STRCT * wl_pci_dma_get_tx_packet( struct wl_private *lp );

void wl_pci_dma_put_tx_packet( struct wl_private *lp, DESC_STRCT *desc );

void wl_pci_dma_hcf_reclaim_tx( struct wl_private *lp );

#endif  // ENABLE_DMA


#endif  // __WL_PCI_H__
