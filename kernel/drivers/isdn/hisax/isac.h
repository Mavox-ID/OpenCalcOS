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
/* All Registers original Siemens Spec  */

#define ISAC_MASK 0x20
#define ISAC_ISTA 0x20
#define ISAC_STAR 0x21
#define ISAC_CMDR 0x21
#define ISAC_EXIR 0x24
#define ISAC_ADF2 0x39
#define ISAC_SPCR 0x30
#define ISAC_ADF1 0x38
#define ISAC_CIR0 0x31
#define ISAC_CIX0 0x31
#define ISAC_CIR1 0x33
#define ISAC_CIX1 0x33
#define ISAC_STCR 0x37
#define ISAC_MODE 0x22
#define ISAC_RSTA 0x27
#define ISAC_RBCL 0x25
#define ISAC_RBCH 0x2A
#define ISAC_TIMR 0x23
#define ISAC_SQXR 0x3b
#define ISAC_MOSR 0x3a
#define ISAC_MOCR 0x3a
#define ISAC_MOR0 0x32
#define ISAC_MOX0 0x32
#define ISAC_MOR1 0x34
#define ISAC_MOX1 0x34

#define ISAC_RBCH_XAC 0x80

#define ISAC_CMD_TIM	0x0
#define ISAC_CMD_RS	0x1
#define ISAC_CMD_SCZ	0x4
#define ISAC_CMD_SSZ	0x2
#define ISAC_CMD_AR8	0x8
#define ISAC_CMD_AR10	0x9
#define ISAC_CMD_ARL	0xA
#define ISAC_CMD_DUI	0xF

#define ISAC_IND_RS	0x1
#define ISAC_IND_PU	0x7
#define ISAC_IND_DR	0x0
#define ISAC_IND_SD	0x2
#define ISAC_IND_DIS	0x3
#define ISAC_IND_EI	0x6
#define ISAC_IND_RSY	0x4
#define ISAC_IND_ARD	0x8
#define ISAC_IND_TI	0xA
#define ISAC_IND_ATI	0xB
#define ISAC_IND_AI8	0xC
#define ISAC_IND_AI10	0xD
#define ISAC_IND_DID	0xF

extern void ISACVersion(struct IsdnCardState *, char *);
extern void setup_isac(struct IsdnCardState *);
extern void initisac(struct IsdnCardState *);
extern void isac_interrupt(struct IsdnCardState *, u_char);
extern void clear_pending_isac_ints(struct IsdnCardState *);
