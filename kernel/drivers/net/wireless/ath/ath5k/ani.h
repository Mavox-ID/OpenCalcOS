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
#ifndef ANI_H
#define ANI_H

#include "../ath.h"

enum ath5k_phy_error_code;

/* these thresholds are relative to the ATH5K_ANI_LISTEN_PERIOD */
#define ATH5K_ANI_LISTEN_PERIOD		100
#define ATH5K_ANI_OFDM_TRIG_HIGH	500
#define ATH5K_ANI_OFDM_TRIG_LOW		200
#define ATH5K_ANI_CCK_TRIG_HIGH		200
#define ATH5K_ANI_CCK_TRIG_LOW		100

/* average beacon RSSI thresholds */
#define ATH5K_ANI_RSSI_THR_HIGH		40
#define ATH5K_ANI_RSSI_THR_LOW		7

/* maximum available levels */
#define ATH5K_ANI_MAX_FIRSTEP_LVL	2
#define ATH5K_ANI_MAX_NOISE_IMM_LVL	1


/**
 * enum ath5k_ani_mode - mode for ANI / noise sensitivity
 *
 * @ATH5K_ANI_MODE_OFF: Turn ANI off. This can be useful to just stop the ANI
 *			algorithm after it has been on auto mode.
 * @ATH5K_ANI_MODE_MANUAL_LOW: Manually set all immunity parameters to low,
 *			maximizing sensitivity. ANI will not run.
 * @ATH5K_ANI_MODE_MANUAL_HIGH: Manually set all immunity parameters to high,
 *			minimizing sensitivity. ANI will not run.
 * @ATH5K_ANI_MODE_AUTO: Automatically control immunity parameters based on the
 *			amount of OFDM and CCK frame errors (default).
 */
enum ath5k_ani_mode {
	ATH5K_ANI_MODE_OFF		= 0,
	ATH5K_ANI_MODE_MANUAL_LOW	= 1,
	ATH5K_ANI_MODE_MANUAL_HIGH	= 2,
	ATH5K_ANI_MODE_AUTO		= 3
};


/**
 * struct ath5k_ani_state - ANI state and associated counters
 * @ani_mode: One of enum ath5k_ani_mode
 * @noise_imm_level: Noise immunity level
 * @spur_level: Spur immunity level
 * @firstep_level: FIRstep level
 * @ofdm_weak_sig: OFDM weak signal detection state (on/off)
 * @cck_weak_sig: CCK weak signal detection state (on/off)
 * @max_spur_level: Max spur immunity level (chip specific)
 * @listen_time: Listen time
 * @ofdm_errors: OFDM timing error count
 * @cck_errors: CCK timing error count
 * @last_cc: The &struct ath_cycle_counters (for stats)
 * @last_listen: Listen time from previous run (for stats)
 * @last_ofdm_errors: OFDM timing error count from previous run (for tats)
 * @last_cck_errors: CCK timing error count from previous run (for stats)
 * @sum_ofdm_errors: Sum of OFDM timing errors (for stats)
 * @sum_cck_errors: Sum of all CCK timing errors (for stats)
 */
struct ath5k_ani_state {
	enum ath5k_ani_mode	ani_mode;

	/* state */
	int			noise_imm_level;
	int			spur_level;
	int			firstep_level;
	bool			ofdm_weak_sig;
	bool			cck_weak_sig;

	int			max_spur_level;

	/* used by the algorithm */
	unsigned int		listen_time;
	unsigned int		ofdm_errors;
	unsigned int		cck_errors;

	/* debug/statistics only: numbers from last ANI calibration */
	struct ath_cycle_counters last_cc;
	unsigned int		last_listen;
	unsigned int		last_ofdm_errors;
	unsigned int		last_cck_errors;
	unsigned int		sum_ofdm_errors;
	unsigned int		sum_cck_errors;
};

void ath5k_ani_init(struct ath5k_hw *ah, enum ath5k_ani_mode mode);
void ath5k_ani_mib_intr(struct ath5k_hw *ah);
void ath5k_ani_calibration(struct ath5k_hw *ah);
void ath5k_ani_phy_error_report(struct ath5k_hw *ah,
				enum ath5k_phy_error_code phyerr);

/* for manual control */
void ath5k_ani_set_noise_immunity_level(struct ath5k_hw *ah, int level);
void ath5k_ani_set_spur_immunity_level(struct ath5k_hw *ah, int level);
void ath5k_ani_set_firstep_level(struct ath5k_hw *ah, int level);
void ath5k_ani_set_ofdm_weak_signal_detection(struct ath5k_hw *ah, bool on);
void ath5k_ani_set_cck_weak_signal_detection(struct ath5k_hw *ah, bool on);

void ath5k_ani_print_counters(struct ath5k_hw *ah);

#endif /* ANI_H */
