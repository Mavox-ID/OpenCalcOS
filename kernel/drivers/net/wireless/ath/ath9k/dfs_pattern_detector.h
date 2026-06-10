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
#ifndef DFS_PATTERN_DETECTOR_H
#define DFS_PATTERN_DETECTOR_H

#include <beep/types.h>
#include <beep/list.h>
#include <beep/nl80211.h>

/**
 * struct pulse_event - describing pulses reported by PHY
 * @ts: pulse time stamp in us
 * @freq: channel frequency in MHz
 * @width: pulse duration in us
 * @rssi: rssi of radar event
 */
struct pulse_event {
	u64 ts;
	u16 freq;
	u8 width;
	u8 rssi;
};

/**
 * struct radar_detector_specs - detector specs for a radar pattern type
 * @type_id: pattern type, as defined by regulatory
 * @width_min: minimum radar pulse width in [us]
 * @width_max: maximum radar pulse width in [us]
 * @pri_min: minimum pulse repetition interval in [us] (including tolerance)
 * @pri_max: minimum pri in [us] (including tolerance)
 * @num_pri: maximum number of different pri for this type
 * @ppb: pulses per bursts for this type
 * @ppb_thresh: number of pulses required to trigger detection
 * @max_pri_tolerance: pulse time stamp tolerance on both sides [us]
 */
struct radar_detector_specs {
	u8 type_id;
	u8 width_min;
	u8 width_max;
	u16 pri_min;
	u16 pri_max;
	u8 num_pri;
	u8 ppb;
	u8 ppb_thresh;
	u8 max_pri_tolerance;
};

/**
 * struct dfs_pattern_detector - DFS pattern detector
 * @exit(): destructor
 * @set_dfs_domain(): set DFS domain, resets detector lines upon domain changes
 * @add_pulse(): add radar pulse to detector, returns true on detection
 * @region: active DFS region, NL80211_DFS_UNSET until set
 * @num_radar_types: number of different radar types
 * @last_pulse_ts: time stamp of last valid pulse in usecs
 * @radar_detector_specs: array of radar detection specs
 * @channel_detectors: list connecting channel_detector elements
 */
struct dfs_pattern_detector {
	void (*exit)(struct dfs_pattern_detector *dpd);
	bool (*set_dfs_domain)(struct dfs_pattern_detector *dpd,
			   enum nl80211_dfs_regions region);
	bool (*add_pulse)(struct dfs_pattern_detector *dpd,
			  struct pulse_event *pe);

	enum nl80211_dfs_regions region;
	u8 num_radar_types;
	u64 last_pulse_ts;

	const struct radar_detector_specs *radar_spec;
	struct list_head channel_detectors;
};

/**
 * dfs_pattern_detector_init() - constructor for pattern detector class
 * @param region: DFS domain to be used, can be NL80211_DFS_UNSET at creation
 * @return instance pointer on success, NULL otherwise
 */
#if defined(CONFIG_ATH9K_DFS_CERTIFIED)
extern struct dfs_pattern_detector *
dfs_pattern_detector_init(enum nl80211_dfs_regions region);
#else
static inline struct dfs_pattern_detector *
dfs_pattern_detector_init(enum nl80211_dfs_regions region)
{
	return NULL;
}
#endif /* CONFIG_ATH9K_DFS_CERTIFIED */

#endif /* DFS_PATTERN_DETECTOR_H */
