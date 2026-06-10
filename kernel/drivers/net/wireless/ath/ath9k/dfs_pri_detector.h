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
#ifndef DFS_PRI_DETECTOR_H
#define DFS_PRI_DETECTOR_H

#include <beep/list.h>

/**
 * struct pri_detector - PRI detector element for a dedicated radar type
 * @exit(): destructor
 * @add_pulse(): add pulse event, returns true if pattern was detected
 * @reset(): clear states and reset to given time stamp
 * @rs: detector specs for this detector element
 * @last_ts: last pulse time stamp considered for this element in usecs
 * @sequences: list_head holding potential pulse sequences
 * @pulses: list connecting pulse_elem objects
 * @count: number of pulses in queue
 * @max_count: maximum number of pulses to be queued
 * @window_size: window size back from newest pulse time stamp in usecs
 */
struct pri_detector {
	void (*exit)     (struct pri_detector *de);
	bool (*add_pulse)(struct pri_detector *de, struct pulse_event *e);
	void (*reset)    (struct pri_detector *de, u64 ts);

/* private: internal use only */
	const struct radar_detector_specs *rs;
	u64 last_ts;
	struct list_head sequences;
	struct list_head pulses;
	u32 count;
	u32 max_count;
	u32 window_size;
};

struct pri_detector *pri_detector_init(const struct radar_detector_specs *rs);

#endif /* DFS_PRI_DETECTOR_H */
