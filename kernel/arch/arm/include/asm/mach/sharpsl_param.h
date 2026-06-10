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
struct sharpsl_param_info {
  unsigned int comadj_keyword;
  unsigned int comadj;

  unsigned int uuid_keyword;
  unsigned char uuid[16];

  unsigned int touch_keyword;
  unsigned int touch_xp;
  unsigned int touch_yp;
  unsigned int touch_xd;
  unsigned int touch_yd;

  unsigned int adadj_keyword;
  unsigned int adadj;

  unsigned int phad_keyword;
  unsigned int phadadj;
} __attribute__((packed));


extern struct sharpsl_param_info sharpsl_param;
extern void sharpsl_save_param(void);

