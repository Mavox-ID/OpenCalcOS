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
#ifndef __UNIFI_CONFIG_H__
#define __UNIFI_CONFIG_H__ 1

/*
 * Override for the SDIO function block size on this host. When byte mode CMD53s
 * are not used/supported by the SD host controller, transfers are padded up to
 * the next block boundary. The 512-byte default on UF6xxx wastes too much space
 * on the chip, so the block size is reduced to support this configuration.
 */
#define CSR_WIFI_HIP_SDIO_BLOCK_SIZE  64

/* Define the number of mini-coredump buffers to allocate at startup. These are
 * used to record chip status for the last n unexpected resets.
 */
#define CSR_WIFI_HIP_NUM_COREDUMP_BUFFERS  5


#endif /* __UNIFI_CONFIG_H__ */
