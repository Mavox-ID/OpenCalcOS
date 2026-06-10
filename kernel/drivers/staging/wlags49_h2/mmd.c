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
#include "hcf.h"				// Needed as long as we do not really sort out the mess
#include "hcfdef.h"				// get CNV_LITTLE_TO_SHORT
#include "mmd.h"				// MoreModularDriver common include file

//to distinguish DHF from HCF asserts by means of line number
#undef	FILE_NAME_OFFSET
#define FILE_NAME_OFFSET DHF_FILE_NAME_OFFSET


/*************************************************************************************************************
*
*.MODULE		CFG_RANGE_SPEC_STRCT* mmd_check_comp( CFG_RANGES_STRCT *actp, CFG_SUP_RANGE_STRCT *supp )
*.PURPOSE		Checks compatibility between an actor and a supplier.
*
*.ARGUMENTS
*	actp
*	supp
*
*.RETURNS
*	NULL	incompatible
*	<>NULL	pointer to matching CFG_RANGE_SPEC_STRCT substructure in actor-structure matching the supplier
*
*.NARRATIVE
*
*  Parameters:
*	actp	address of the actor specification
*	supp	address of the supplier specification
*
*	Description: mmd_check_comp is a support routine to check the compatibility between an actor and a
*	supplier.  mmd_check_comp is independent of the endianness of the actp and supp structures. This is
*	achieved by checking the "bottom" or "role" fields of these structures. Since these fields are restricted
*	to a limited range, comparing the contents to a value with a known endian-ess gives a clue to their actual
*	endianness.
*
*.DIAGRAM
*1a: The role-field of the actor structure has a known non-zero, not "byte symmetric" value (namely
*	COMP_ROLE_ACT or 0x0001), so if and only the contents of this field matches COMP_ROLE_ACT (in Native
*	Endian format), the actor structure is Native Endian.
*2a: Since the role-field of the supplier structure is 0x0000, the test as used for the actor does not work
*	for a supplier. A supplier has always exactly 1 variant,top,bottom record with (officially, but see the
*	note below) each of these 3 values in the range 1 through 99, so one byte of the word value of variant,
*	top and bottom words is 0x00 and the other byte is non-zero. Whether the lowest address byte or the
*	highest address byte is non-zero depends on the Endianness of the LTV. If and only if the word value of
*	bottom is less than 0x0100, the supplier is Native Endian.
*	NOTE: the variant field of the supplier structure can not be used for the Endian Detection Algorithm,
*	because a a zero-valued variant has been used as Controlled Deployment indication in the past.
*	Note: An actor may have multiple sets of variant,top,bottom records, including dummy sets with variant,
*	top and bottom fields with a zero-value. As a consequence the endianness of the actor can not be determined
*	based on its variant,top,bottom values.
*
*	Note: the L and T field of the structures are always in Native Endian format, so you can not draw
*	conclusions concerning the Endianness of the structure based on these two fields.
*
*1b/2b
*	The only purpose of the CFG_RANGE_SPEC_BYTE_STRCT is to give easy access to the non-zero byte of the word
*	value of variant, top and bottom. The variables sup_endian and act_endian are used for the supplier and
*	actor structure respectively. These variables must be 0 when the structure has LE format and 1 if the
*	structure has BE format. This can be phrased as:
*	the variable is false (i.e 0x0000) if either
*		(the platform is LE and the LTV is the same as the platform)
*	or
*		(the platform is BE and the LTV differs from the platform).
*	the variable is true (i.e 0x0001) if either
*		(the platform is BE and the LTV is the same as the platform)
*	or
*		(the platform is LE and the LTV differs from the platform).
*
*	Alternatively this can be phrased as:
*	if the platform is LE
*		if the LTV is LE (i.e the same as the platform), then the variable = 0
*		else (the LTV is BE (i.e. different from the platform) ), then the variable = 1
*	if the platform is BE
*		if the LTV is BE (i.e the same as the platform), then the variable = 1
*		else (the LTV is LE (i.e. different from the platform) ), then the variable = 0
*
*	This is implemented as:
*	#if HCF_BIG_ENDIAN == 0	//platform is LE
*		sup/act_endian becomes reverse of structure-endianness as determined in 1a/1b
*	#endif
*6:	Each of the actor variant-bottom-top records is checked against the (single) supplier variant-bottom-top
*	range till either an acceptable match is found or all actor records are tried. As explained above, due to
*	the limited ranges of these values, checking a byte is acceptable and suitable.
*8:	depending on whether a match was found or not (as reflected by the value of the control variable of the
*	for loop), the NULL pointer or a pointer to the matching Number/Bottom/Top record of the Actor structure
*	is returned.
*	As an additional safety, checking the supplier length protects against invalid Supplier structures, which
*	may be caused by failing hcf_get_info (in which case the len-field is zero). Note that the contraption
*	"supp->len != sizeof(CFG_SUP_RANGE_STRCT)/sizeof(hcf_16) - 1"
*	did turn out not to work for a compiler which padded the structure definition.
*
* Note: when consulting references like DesignNotes and Architecture specifications there is a confusing use
*	of the notions number and variant. This resulted in an inconsistent use in the HCF nomenclature as well.
*	This makes the logic hard to follow and one has to be very much aware of the context when walking through
*	the code.
* NOTE: The Endian Detection Algorithm places limitations on future extensions of the fields, i.e. they should
*	stay within the currently defined boundaries of 1 through 99 (although 1 through 255) would work as well
*	and there should never be used a zero value for the bottom of a valid supplier.
* Note: relative to Asserts, the following can be observed:
*	1: Supplier variant 0x0000 has been used for Controlled Deployment
*	2: An actor may have one or more variant record specifications with a top of zero and a non-zero bottom
*	to override the HCF default support of a particular variant by the MSF programmer via hcfcfg.h
*	3:	An actor range can be specified as all zeros, e.g. as padding in the automatically generated firmware
*	image files.
*.ENDDOC				END DOCUMENTATION
*************************************************************************************************************/
CFG_RANGE_SPEC_STRCT*
mmd_check_comp( CFG_RANGES_STRCT *actp, CFG_SUP_RANGE_STRCT *supp )
{

CFG_RANGE_SPEC_BYTE_STRCT  *actq = (CFG_RANGE_SPEC_BYTE_STRCT*)actp->var_rec;
CFG_RANGE_SPEC_BYTE_STRCT  *supq = (CFG_RANGE_SPEC_BYTE_STRCT*)&(supp->variant);
hcf_16	i;
int		act_endian;					//actor endian flag
int		sup_endian;					//supplier endian flag

	act_endian = actp->role == COMP_ROLE_ACT;	//true if native endian				/* 1a */
	sup_endian = supp->bottom < 0x0100;		 	//true if native endian				/* 2a */

#if HCF_ASSERT
	MMDASSERT( supp->len == 6, 																supp->len )
	MMDASSERT( actp->len >= 6 && actp->len%3 == 0, 											actp->len )

	if ( act_endian ) {							//native endian
		MMDASSERT( actp->role == COMP_ROLE_ACT,												actp->role )
		MMDASSERT( 1 <= actp->id && actp->id <= 99,  										actp->id )
	} else {									//non-native endian
		MMDASSERT( actp->role == CNV_END_SHORT(COMP_ROLE_ACT),	 							actp->role )
		MMDASSERT( 1 <= CNV_END_SHORT(actp->id) && CNV_END_SHORT(actp->id) <= 99,				actp->id )
	}
	if ( sup_endian ) {							//native endian
		MMDASSERT( supp->role == COMP_ROLE_SUPL, 											supp->role )
		MMDASSERT( 1 <= supp->id      && supp->id <= 99,  									supp->id )
		MMDASSERT( 1 <= supp->variant && supp->variant <= 99,  								supp->variant )
		MMDASSERT( 1 <= supp->bottom  && supp->bottom <= 99, 								supp->bottom )
		MMDASSERT( 1 <= supp->top     && supp->top <= 99, 		 							supp->top )
		MMDASSERT( supp->bottom <= supp->top,							supp->bottom << 8 | supp->top )
	} else {									//non-native endian
		MMDASSERT( supp->role == CNV_END_SHORT(COMP_ROLE_SUPL), 								supp->role )
		MMDASSERT( 1 <= CNV_END_SHORT(supp->id) && CNV_END_SHORT(supp->id) <= 99,				supp->id )
		MMDASSERT( 1 <= CNV_END_SHORT(supp->variant) && CNV_END_SHORT(supp->variant) <= 99,		supp->variant )
		MMDASSERT( 1 <= CNV_END_SHORT(supp->bottom)  && CNV_END_SHORT(supp->bottom) <=99,		supp->bottom )
		MMDASSERT( 1 <= CNV_END_SHORT(supp->top)     && CNV_END_SHORT(supp->top) <=99,  		supp->top )
		MMDASSERT( CNV_END_SHORT(supp->bottom) <= CNV_END_SHORT(supp->top),	supp->bottom << 8 |	supp->top )
	}
#endif // HCF_ASSERT

#if HCF_BIG_ENDIAN == 0
	act_endian = !act_endian;																		/* 1b*/
	sup_endian = !sup_endian;																		/* 2b*/
#endif // HCF_BIG_ENDIAN

	for ( i = actp->len ; i > 3; actq++, i -= 3 ) {													/* 6 */
		MMDASSERT( actq->variant[act_endian] <= 99, i<<8 | actq->variant[act_endian] )
		MMDASSERT( actq->bottom[act_endian] <= 99 , i<<8 | actq->bottom[act_endian] )
		MMDASSERT( actq->top[act_endian] <= 99	  , i<<8 | actq->top[act_endian] )
		MMDASSERT( actq->bottom[act_endian] <= actq->top[act_endian], i<<8 | actq->bottom[act_endian] )
		if ( actq->variant[act_endian] == supq->variant[sup_endian] &&
			 actq->bottom[act_endian]  <= supq->top[sup_endian] &&
			 actq->top[act_endian]     >= supq->bottom[sup_endian]
		   ) break;
	}
	if ( i <= 3 || supp->len != 6 /*sizeof(CFG_SUP_RANGE_STRCT)/sizeof(hcf_16) - 1 */ ) {
	   actq = NULL;																					/* 8 */
	}
#if HCF_ASSERT
	if ( actq == NULL ) {
		for ( i = 0; i <= supp->len; i += 2 ) {
			MMDASSERT( DO_ASSERT, MERGE_2( ((hcf_16*)supp)[i], ((hcf_16*)supp)[i+1] ) );
		}
		for ( i = 0; i <= actp->len; i += 2 ) {
			MMDASSERT( DO_ASSERT, MERGE_2( ((hcf_16*)actp)[i], ((hcf_16*)actp)[i+1] ) );
		}
	}
#endif // HCF_ASSERT
	return (CFG_RANGE_SPEC_STRCT*)actq;
} // mmd_check_comp

