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
#ifndef ATH9K_DFS_H
#define ATH9K_DFS_H
#include "dfs_pattern_detector.h"

#if defined(CONFIG_ATH9K_DFS_CERTIFIED)
/**
 * ath9k_dfs_process_phyerr - process radar PHY error
 * @sc: ath_softc
 * @data: RX payload data
 * @rs: RX status after processing descriptor
 * @mactime: receive time
 *
 * This function is called whenever the HW DFS module detects a radar
 * pulse and reports it as a PHY error.
 *
 * The radar information provided as raw payload data is validated and
 * filtered for false pulses. Events passing all tests are forwarded to
 * the DFS detector for pattern detection.
 */
void ath9k_dfs_process_phyerr(struct ath_softc *sc, void *data,
			      struct ath_rx_status *rs, u64 mactime);
#else
static inline void
ath9k_dfs_process_phyerr(struct ath_softc *sc, void *data,
			 struct ath_rx_status *rs, u64 mactime) { }
#endif

#endif /* ATH9K_DFS_H */
