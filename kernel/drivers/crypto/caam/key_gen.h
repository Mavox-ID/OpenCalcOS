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
struct split_key_result {
	struct completion completion;
	int err;
};

void split_key_done(struct device *dev, u32 *desc, u32 err, void *context);

u32 gen_split_key(struct device *jrdev, u8 *key_out, int split_key_len,
		    int split_key_pad_len, const u8 *key_in, u32 keylen,
		    u32 alg_op);
