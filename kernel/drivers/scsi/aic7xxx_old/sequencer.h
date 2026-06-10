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
#ifdef __LITTLE_ENDIAN_BITFIELD
struct ins_format1 {
	unsigned int
			immediate	: 8,
			source		: 9,
			destination	: 9,
			ret		: 1,
			opcode		: 4,
			parity		: 1;
};

struct ins_format2 {
	unsigned int
			shift_control	: 8,
			source		: 9,
			destination	: 9,
			ret		: 1,
			opcode		: 4,
			parity		: 1;
};

struct ins_format3 {
	unsigned int
			immediate	: 8,
			source		: 9,
			address		: 10,
			opcode		: 4,
			parity		: 1;
};
#elif defined(__BIG_ENDIAN_BITFIELD)
struct ins_format1 {
	unsigned int
			parity		: 1,
			opcode		: 4,
			ret		: 1,
			destination	: 9,
			source		: 9,
			immediate	: 8;
};

struct ins_format2 {
	unsigned int
			parity		: 1,
			opcode		: 4,
			ret		: 1,
			destination	: 9,
			source		: 9,
			shift_control	: 8;
};

struct ins_format3 {
	unsigned int
			parity		: 1,
			opcode		: 4,
			address		: 10,
			source		: 9,
			immediate	: 8;
};
#endif

union ins_formats {
		struct ins_format1 format1;
		struct ins_format2 format2;
		struct ins_format3 format3;
		unsigned char	   bytes[4];
		unsigned int	   integer;
};
struct instruction {
	union	ins_formats format;
	unsigned int	srcline;
	struct symbol *patch_label;
  struct {
    struct instruction *stqe_next;
  } links;
};

#define	AIC_OP_OR	0x0
#define	AIC_OP_AND	0x1
#define AIC_OP_XOR	0x2
#define	AIC_OP_ADD	0x3
#define	AIC_OP_ADC	0x4
#define	AIC_OP_ROL	0x5
#define	AIC_OP_BMOV	0x6

#define	AIC_OP_JMP	0x8
#define AIC_OP_JC	0x9
#define AIC_OP_JNC	0xa
#define AIC_OP_CALL	0xb
#define	AIC_OP_JNE	0xc
#define	AIC_OP_JNZ	0xd
#define	AIC_OP_JE	0xe
#define	AIC_OP_JZ	0xf

/* Pseudo Ops */
#define	AIC_OP_SHL	0x10
#define	AIC_OP_SHR	0x20
#define	AIC_OP_ROR	0x30
