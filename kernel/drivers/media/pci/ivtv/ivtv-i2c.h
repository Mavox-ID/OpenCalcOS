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
#ifndef IVTV_I2C_H
#define IVTV_I2C_H

struct i2c_client *ivtv_i2c_new_ir_legacy(struct ivtv *itv);
int ivtv_i2c_register(struct ivtv *itv, unsigned idx);
struct v4l2_subdev *ivtv_find_hw(struct ivtv *itv, u32 hw);

/* init + register i2c adapter */
int init_ivtv_i2c(struct ivtv *itv);
void exit_ivtv_i2c(struct ivtv *itv);

#endif
