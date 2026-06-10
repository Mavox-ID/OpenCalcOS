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
#ifndef IVTV_CONTROLS_H
#define IVTV_CONTROLS_H

extern struct cx2341x_handler_ops ivtv_cxhdl_ops;
extern const struct v4l2_ctrl_ops ivtv_hdl_out_ops;
int ivtv_g_pts_frame(struct ivtv *itv, s64 *pts, s64 *frame);

#endif
