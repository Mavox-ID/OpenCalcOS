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
#include "cx18-driver.h"
#include "cx18-video.h"
#include "cx18-cards.h"

void cx18_video_set_io(struct cx18 *cx)
{
	int inp = cx->active_input;

	v4l2_subdev_call(cx->sd_av, video, s_routing,
			cx->card->video_inputs[inp].video_input, 0, 0);
}
