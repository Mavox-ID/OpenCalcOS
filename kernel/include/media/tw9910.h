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
#ifndef __TW9910_H__
#define __TW9910_H__

#include <media/soc_camera.h>

enum tw9910_mpout_pin {
	TW9910_MPO_VLOSS,
	TW9910_MPO_HLOCK,
	TW9910_MPO_SLOCK,
	TW9910_MPO_VLOCK,
	TW9910_MPO_MONO,
	TW9910_MPO_DET50,
	TW9910_MPO_FIELD,
	TW9910_MPO_RTCO,
};

struct tw9910_video_info {
	unsigned long		buswidth;
	enum tw9910_mpout_pin	mpout;
};


#endif /* __TW9910_H__ */
