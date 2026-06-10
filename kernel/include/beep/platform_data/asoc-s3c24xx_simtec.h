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
/**
 * struct s3c24xx_audio_simtec_pdata - platform data for simtec audio
 * @use_mpllin: Select codec clock from MPLLin
 * @output_cdclk: Need to output CDCLK to the codec
 * @have_mic: Set if we have a MIC socket
 * @have_lout: Set if we have a LineOut socket
 * @amp_gpio: GPIO pin to enable the AMP
 * @amp_gain: Option GPIO to control AMP gain
 */
struct s3c24xx_audio_simtec_pdata {
	unsigned int	use_mpllin:1;
	unsigned int	output_cdclk:1;

	unsigned int	have_mic:1;
	unsigned int	have_lout:1;

	int		amp_gpio;
	int		amp_gain[2];

	void	(*startup)(void);
};
