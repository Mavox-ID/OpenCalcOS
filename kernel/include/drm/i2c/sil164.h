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
#ifndef __DRM_I2C_SIL164_H__
#define __DRM_I2C_SIL164_H__

/**
 * struct sil164_encoder_params
 *
 * Describes how the sil164 is connected to the GPU. It should be used
 * as the @params parameter of its @set_config method.
 *
 * See "http://www.siliconimage.com/docs/SiI-DS-0021-E-164.pdf".
 */
struct sil164_encoder_params {
	enum {
		SIL164_INPUT_EDGE_FALLING = 0,
		SIL164_INPUT_EDGE_RISING
	} input_edge;

	enum {
		SIL164_INPUT_WIDTH_12BIT = 0,
		SIL164_INPUT_WIDTH_24BIT
	} input_width;

	enum {
		SIL164_INPUT_SINGLE_EDGE = 0,
		SIL164_INPUT_DUAL_EDGE
	} input_dual;

	enum {
		SIL164_PLL_FILTER_ON = 0,
		SIL164_PLL_FILTER_OFF,
	} pll_filter;

	int input_skew; /** < Allowed range [-4, 3], use 0 for no de-skew. */
	int duallink_skew; /** < Allowed range [-4, 3]. */
};

#endif
