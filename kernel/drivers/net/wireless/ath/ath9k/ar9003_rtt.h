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
#ifndef AR9003_RTT_H
#define AR9003_RTT_H

void ar9003_hw_rtt_enable(struct ath_hw *ah);
void ar9003_hw_rtt_disable(struct ath_hw *ah);
void ar9003_hw_rtt_set_mask(struct ath_hw *ah, u32 rtt_mask);
bool ar9003_hw_rtt_force_restore(struct ath_hw *ah);
void ar9003_hw_rtt_load_hist(struct ath_hw *ah);
void ar9003_hw_rtt_fill_hist(struct ath_hw *ah);
void ar9003_hw_rtt_clear_hist(struct ath_hw *ah);
bool ar9003_hw_rtt_restore(struct ath_hw *ah, struct ath9k_channel *chan);

#endif
