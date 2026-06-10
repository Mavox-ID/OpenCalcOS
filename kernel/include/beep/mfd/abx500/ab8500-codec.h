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
#ifndef AB8500_CORE_CODEC_H
#define AB8500_CORE_CODEC_H

/* Mic-types */
enum amic_type {
	AMIC_TYPE_SINGLE_ENDED,
	AMIC_TYPE_DIFFERENTIAL
};

/* Mic-biases */
enum amic_micbias {
	AMIC_MICBIAS_VAMIC1,
	AMIC_MICBIAS_VAMIC2,
	AMIC_MICBIAS_UNKNOWN
};

/* Bias-voltage */
enum ear_cm_voltage {
	EAR_CMV_0_95V,
	EAR_CMV_1_10V,
	EAR_CMV_1_27V,
	EAR_CMV_1_58V,
	EAR_CMV_UNKNOWN
};

/* Analog microphone settings */
struct amic_settings {
	enum amic_type mic1_type;
	enum amic_type mic2_type;
	enum amic_micbias mic1a_micbias;
	enum amic_micbias mic1b_micbias;
	enum amic_micbias mic2_micbias;
};

/* Platform data structure for the audio-parts of the AB8500 */
struct ab8500_codec_platform_data {
	struct amic_settings amics;
	enum ear_cm_voltage ear_cmv;
};

#endif
