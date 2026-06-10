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
int cx18_i2c_register(struct cx18 *cx, unsigned idx);
struct v4l2_subdev *cx18_find_hw(struct cx18 *cx, u32 hw);

/* init + register i2c adapter */
int init_cx18_i2c(struct cx18 *cx);
void exit_cx18_i2c(struct cx18 *cx);
