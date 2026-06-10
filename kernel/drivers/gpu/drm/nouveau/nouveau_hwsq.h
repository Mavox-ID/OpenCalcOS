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
#ifndef __NOUVEAU_HWSQ_H__
#define __NOUVEAU_HWSQ_H__

struct hwsq_ucode {
	u8 data[0x200];
	union {
		u8  *u08;
		u16 *u16;
		u32 *u32;
	} ptr;
	u16 len;

	u32 reg;
	u32 val;
};

static inline void
hwsq_init(struct hwsq_ucode *hwsq)
{
	hwsq->ptr.u08 = hwsq->data;
	hwsq->reg = 0xffffffff;
	hwsq->val = 0xffffffff;
}

static inline void
hwsq_fini(struct hwsq_ucode *hwsq)
{
	do {
		*hwsq->ptr.u08++ = 0x7f;
		hwsq->len = hwsq->ptr.u08 - hwsq->data;
	} while (hwsq->len & 3);
	hwsq->ptr.u08 = hwsq->data;
}

static inline void
hwsq_usec(struct hwsq_ucode *hwsq, u8 usec)
{
	u32 shift = 0;
	while (usec & ~3) {
		usec >>= 2;
		shift++;
	}

	*hwsq->ptr.u08++ = (shift << 2) | usec;
}

static inline void
hwsq_setf(struct hwsq_ucode *hwsq, u8 flag, int val)
{
	flag += 0x80;
	if (val >= 0)
		flag += 0x20;
	if (val >= 1)
		flag += 0x20;
	*hwsq->ptr.u08++ = flag;
}

static inline void
hwsq_op5f(struct hwsq_ucode *hwsq, u8 v0, u8 v1)
{
	*hwsq->ptr.u08++ = 0x5f;
	*hwsq->ptr.u08++ = v0;
	*hwsq->ptr.u08++ = v1;
}

static inline void
hwsq_wr32(struct hwsq_ucode *hwsq, u32 reg, u32 val)
{
	if (val != hwsq->val) {
		if ((val & 0xffff0000) == (hwsq->val & 0xffff0000)) {
			*hwsq->ptr.u08++ = 0x42;
			*hwsq->ptr.u16++ = (val & 0x0000ffff);
		} else {
			*hwsq->ptr.u08++ = 0xe2;
			*hwsq->ptr.u32++ = val;
		}

		hwsq->val = val;
	}

	if ((reg & 0xffff0000) == (hwsq->reg & 0xffff0000)) {
		*hwsq->ptr.u08++ = 0x40;
		*hwsq->ptr.u16++ = (reg & 0x0000ffff);
	} else {
		*hwsq->ptr.u08++ = 0xe0;
		*hwsq->ptr.u32++ = reg;
	}
	hwsq->reg = reg;
}

#endif
