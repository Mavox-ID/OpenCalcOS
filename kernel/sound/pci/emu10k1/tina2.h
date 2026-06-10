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
/********************************************************************************************************/
/* Audigy2 Tina2 (notebook) pointer-offset register set, accessed through the PTR2 and DATA2 registers  */
/********************************************************************************************************/

#define TINA2_VOLUME	0x71	/* Attenuate playback volume to prevent distortion. */
				/* The windows driver does not use this register,
				 * so it must use some other attenuation method.
				 * Without this, the output is 12dB too loud,
				 * resulting in distortion.
				 */

