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
#ifndef ATH9K_DFS_DEBUG_H
#define ATH9K_DFS_DEBUG_H

#include "hw.h"

/**
 * struct ath_dfs_stats - DFS Statistics per wiphy
 * @pulses_total:     pulses reported by HW
 * @pulses_no_dfs:    pulses wrongly reported as DFS
 * @pulses_detected:  pulses detected so far
 * @datalen_discards: pulses discarded due to invalid datalen
 * @rssi_discards:    pulses discarded due to invalid RSSI
 * @bwinfo_discards:  pulses discarded due to invalid BW info
 * @pri_phy_errors:   pulses reported for primary channel
 * @ext_phy_errors:   pulses reported for extension channel
 * @dc_phy_errors:    pulses reported for primary + extension channel
 * @pulses_processed: pulses forwarded to detector
 * @radar_detected:   radars detected
 */
struct ath_dfs_stats {
	/* pulse stats */
	u32 pulses_total;
	u32 pulses_no_dfs;
	u32 pulses_detected;
	u32 datalen_discards;
	u32 rssi_discards;
	u32 bwinfo_discards;
	u32 pri_phy_errors;
	u32 ext_phy_errors;
	u32 dc_phy_errors;
	/* pattern detection stats */
	u32 pulses_processed;
	u32 radar_detected;
};

/**
 * struct ath_dfs_pool_stats - DFS Statistics for global pools
 */
struct ath_dfs_pool_stats {
	u32 pool_reference;
	u32 pulse_allocated;
	u32 pulse_alloc_error;
	u32 pulse_used;
	u32 pseq_allocated;
	u32 pseq_alloc_error;
	u32 pseq_used;
};
#if defined(CONFIG_ATH9K_DFS_DEBUGFS)

#define DFS_STAT_INC(sc, c) (sc->debug.stats.dfs_stats.c++)
void ath9k_dfs_init_debug(struct ath_softc *sc);

#define DFS_POOL_STAT_INC(c) (global_dfs_pool_stats.c++)
#define DFS_POOL_STAT_DEC(c) (global_dfs_pool_stats.c--)
extern struct ath_dfs_pool_stats global_dfs_pool_stats;

#else

#define DFS_STAT_INC(sc, c) do { } while (0)
static inline void ath9k_dfs_init_debug(struct ath_softc *sc) { }

#define DFS_POOL_STAT_INC(c) do { } while (0)
#define DFS_POOL_STAT_DEC(c) do { } while (0)
#endif /* CONFIG_ATH9K_DFS_DEBUGFS */

#endif /* ATH9K_DFS_DEBUG_H */
