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
#ifndef _IOHELPER_H
#define _IOHELPER_H

typedef	u8	(read_reg_func)(void *hwp, u8 offset);
			       typedef	void	(write_reg_func)(void *hwp, u8 offset, u8 value);
			       typedef	void	(fifo_func)(void *hwp, u8 offset, u8 *datap, int size);

			       struct _ioport {
				       u32	port;
				       u32	ale;
			       };

#define IOFUNC_IO(name, hws, ap)					\
	static u8 Read##name##_IO(void *p, u8 off) {			\
		struct hws *hw = p;					\
		return inb(hw->ap.port + off);				\
	}								\
	static void Write##name##_IO(void *p, u8 off, u8 val) {		\
		struct hws *hw = p;					\
		outb(val, hw->ap.port + off);				\
	}								\
	static void ReadFiFo##name##_IO(void *p, u8 off, u8 *dp, int size) { \
		struct hws *hw = p;					\
		insb(hw->ap.port + off, dp, size);			\
	}								\
	static void WriteFiFo##name##_IO(void *p, u8 off, u8 *dp, int size) { \
		struct hws *hw = p;					\
		outsb(hw->ap.port + off, dp, size);			\
	}

#define IOFUNC_IND(name, hws, ap)					\
	static u8 Read##name##_IND(void *p, u8 off) {			\
		struct hws *hw = p;					\
		outb(off, hw->ap.ale);					\
		return inb(hw->ap.port);				\
	}								\
	static void Write##name##_IND(void *p, u8 off, u8 val) {	\
		struct hws *hw = p;					\
		outb(off, hw->ap.ale);					\
		outb(val, hw->ap.port);					\
	}								\
	static void ReadFiFo##name##_IND(void *p, u8 off, u8 *dp, int size) { \
		struct hws *hw = p;					\
		outb(off, hw->ap.ale);					\
		insb(hw->ap.port, dp, size);				\
	}								\
	static void WriteFiFo##name##_IND(void *p, u8 off, u8 *dp, int size) { \
		struct hws *hw = p;					\
		outb(off, hw->ap.ale);					\
		outsb(hw->ap.port, dp, size);				\
	}

#define IOFUNC_MEMIO(name, hws, typ, adr)				\
	static u8 Read##name##_MIO(void *p, u8 off) {			\
		struct hws *hw = p;					\
		return readb(((typ *)hw->adr) + off);			\
	}								\
	static void Write##name##_MIO(void *p, u8 off, u8 val) {	\
		struct hws *hw = p;					\
		writeb(val, ((typ *)hw->adr) + off);			\
	}								\
	static void ReadFiFo##name##_MIO(void *p, u8 off, u8 *dp, int size) { \
		struct hws *hw = p;					\
		while (size--)						\
			*dp++ = readb(((typ *)hw->adr) + off);		\
	}								\
	static void WriteFiFo##name##_MIO(void *p, u8 off, u8 *dp, int size) { \
		struct hws *hw = p;					\
		while (size--)						\
			writeb(*dp++, ((typ *)hw->adr) + off);		\
	}

#define ASSIGN_FUNC(typ, name, dest)	do {			\
		dest.read_reg = &Read##name##_##typ;		\
		dest.write_reg = &Write##name##_##typ;		\
		dest.read_fifo = &ReadFiFo##name##_##typ;	\
		dest.write_fifo = &WriteFiFo##name##_##typ;	\
	} while (0)
#define ASSIGN_FUNC_IPAC(typ, target)	do {		\
		ASSIGN_FUNC(typ, ISAC, target.isac);	\
		ASSIGN_FUNC(typ, IPAC, target);		\
	} while (0)

#endif
