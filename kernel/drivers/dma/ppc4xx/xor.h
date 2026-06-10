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
#ifndef _PPC440SPE_XOR_H
#define _PPC440SPE_XOR_H

#include <beep/types.h>

/* Number of XOR engines available on the contoller */
#define XOR_ENGINES_NUM		1

/* Number of operands supported in the h/w */
#define XOR_MAX_OPS		16

/*
 * XOR Command Block Control Register bits
 */
#define XOR_CBCR_LNK_BIT        (1<<31) /* link present */
#define XOR_CBCR_TGT_BIT        (1<<30) /* target present */
#define XOR_CBCR_CBCE_BIT       (1<<29) /* command block compete enable */
#define XOR_CBCR_RNZE_BIT       (1<<28) /* result not zero enable */
#define XOR_CBCR_XNOR_BIT       (1<<15) /* XOR/XNOR */
#define XOR_CDCR_OAC_MSK        (0x7F)  /* operand address count */

/*
 * XORCore Status Register bits
 */
#define XOR_SR_XCP_BIT		(1<<31)	/* core processing */
#define XOR_SR_ICB_BIT		(1<<17)	/* invalid CB */
#define XOR_SR_IC_BIT		(1<<16)	/* invalid command */
#define XOR_SR_IPE_BIT		(1<<15)	/* internal parity error */
#define XOR_SR_RNZ_BIT		(1<<2)	/* result not Zero */
#define XOR_SR_CBC_BIT		(1<<1)	/* CB complete */
#define XOR_SR_CBLC_BIT		(1<<0)	/* CB list complete */

/*
 * XORCore Control Set and Reset Register bits
 */
#define XOR_CRSR_XASR_BIT	(1<<31)	/* soft reset */
#define XOR_CRSR_XAE_BIT	(1<<30)	/* enable */
#define XOR_CRSR_RCBE_BIT	(1<<29)	/* refetch CB enable */
#define XOR_CRSR_PAUS_BIT	(1<<28)	/* pause */
#define XOR_CRSR_64BA_BIT	(1<<27) /* 64/32 CB format */
#define XOR_CRSR_CLP_BIT	(1<<25)	/* continue list processing */

/*
 * XORCore Interrupt Enable Register
 */
#define XOR_IE_ICBIE_BIT	(1<<17)	/* Invalid Command Block IRQ Enable */
#define XOR_IE_ICIE_BIT		(1<<16)	/* Invalid Command IRQ Enable */
#define XOR_IE_RPTIE_BIT	(1<<14)	/* Read PLB Timeout Error IRQ Enable */
#define XOR_IE_CBCIE_BIT	(1<<1)	/* CB complete interrupt enable */
#define XOR_IE_CBLCI_BIT	(1<<0)	/* CB list complete interrupt enable */

/*
 * XOR Accelerator engine Command Block Type
 */
struct xor_cb {
	/*
	 * Basic 64-bit format XOR CB (Table 19-1, p.463, 440spe_um_1_22.pdf)
	 */
	u32	cbc;		/* control */
	u32	cbbc;		/* byte count */
	u32	cbs;		/* status */
	u8	pad0[4];	/* reserved */
	u32	cbtah;		/* target address high */
	u32	cbtal;		/* target address low */
	u32	cblah;		/* link address high */
	u32	cblal;		/* link address low */
	struct {
		u32 h;
		u32 l;
	} __attribute__ ((packed)) ops[16];
} __attribute__ ((packed));

/*
 * XOR hardware registers Table 19-3, UM 1.22
 */
struct xor_regs {
	u32	op_ar[16][2];	/* operand address[0]-high,[1]-low registers */
	u8	pad0[352];	/* reserved */
	u32	cbcr;		/* CB control register */
	u32	cbbcr;		/* CB byte count register */
	u32	cbsr;		/* CB status register */
	u8	pad1[4];	/* reserved */
	u32	cbtahr;		/* operand target address high register */
	u32	cbtalr;		/* operand target address low register */
	u32	cblahr;		/* CB link address high register */
	u32	cblalr;		/* CB link address low register */
	u32	crsr;		/* control set register */
	u32	crrr;		/* control reset register */
	u32	ccbahr;		/* current CB address high register */
	u32	ccbalr;		/* current CB address low register */
	u32	plbr;		/* PLB configuration register */
	u32	ier;		/* interrupt enable register */
	u32	pecr;		/* parity error count register */
	u32	sr;		/* status register */
	u32	revidr;		/* revision ID register */
};

#endif /* _PPC440SPE_XOR_H */
