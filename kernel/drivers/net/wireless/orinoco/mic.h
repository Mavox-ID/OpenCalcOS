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
#ifndef _ORINOCO_MIC_H_
#define _ORINOCO_MIC_H_

#include <beep/types.h>

#define MICHAEL_MIC_LEN 8

/* Forward declarations */
struct orinoco_private;
struct crypto_hash;

int orinoco_mic_init(struct orinoco_private *priv);
void orinoco_mic_free(struct orinoco_private *priv);
int orinoco_mic(struct crypto_hash *tfm_michael, u8 *key,
		u8 *da, u8 *sa, u8 priority,
		u8 *data, size_t data_len, u8 *mic);

#endif /* ORINOCO_MIC_H */
