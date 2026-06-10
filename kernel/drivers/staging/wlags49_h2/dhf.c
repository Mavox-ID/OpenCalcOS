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
#include "hcf.h"
#include "hcfdef.h"
#include "dhf.h"
#include "mmd.h"

/* to distinguish MMD from HCF asserts by means of line number */
#undef	FILE_NAME_OFFSET
#define FILE_NAME_OFFSET MMD_FILE_NAME_OFFSET
/*-----------------------------------------------------------------------------
 *
 * Defines, data structures, and global variables
 *
 *---------------------------------------------------------------------------*/

/*                    12345678901234 */
char signature[14] = "FUPU7D37dhfwci";

/*-----------------------------------------------------------------------------
 *
 * LTV-records retrieved from the NIC to:
 *	- determine compatibility between NIC and image
 *	- ((setup the buffer size dynamically for non-volatile download (see note below) ))
 *	- supply plugging information contained in the PDA (H-I only)
 *
 *---------------------------------------------------------------------------*/

/* for USB/H1 we needed a smaller value than the CFG_DL_BUF_STRCT reported 8192
	for the time being it seems simpler to always use 2000 for USB/H1 as well as all other cases rather than
	using the "fixed anyway" CFG_DL_BUF_STRCT. */
#define DL_SIZE 2000

/* CFG_IDENTITY_STRCT   	pri_identity	= { LOF(CFG_IDENTITY_STRCT), CFG_PRI_IDENTITY }; */
CFG_SUP_RANGE_STRCT 	mfi_sup        	= { LOF(CFG_SUP_RANGE_STRCT), CFG_NIC_MFI_SUP_RANGE };
CFG_SUP_RANGE_STRCT 	cfi_sup        	= { LOF(CFG_SUP_RANGE_STRCT), CFG_NIC_CFI_SUP_RANGE };
/* Note: could be used rather than the above explained and defined DL_SIZE if need arises
 * CFG_DL_BUF_STRCT    	dl_buf         	= { LOF(CFG_DL_BUF_STRCT), CFG_DL_BUF };
*/

/*-----------------------------------------------------------------------------
 * Array ltv_info stores NIC information (in the form of LTV-records)
 * needed for download. A NULL record indicates the end of the array.
 *---------------------------------------------------------------------------*/

/* The LTV_INFO_STRUCT is needed to save the sizes of the structs, because after a GET_INFO()
 * the len field is changed to the real len of the RID by the called routine.
 * This is only relevant if the DHF used without reloading the driver/utility.
 */

LTV_INFO_STRUCT ltv_info[] = {
	{ (LTVP)&mfi_sup,			LOF(CFG_SUP_RANGE_STRCT) } ,
	{ (LTVP)&cfi_sup,			LOF(CFG_SUP_RANGE_STRCT) } ,
	{ (LTVP) NULL, 				0 }
};


/***********************************************************************************************************/
/***************************************  PROTOTYPES  ******************************************************/
/***********************************************************************************************************/
static int				check_comp_fw(memimage *fw);


/************************************************************************************************************
*.SUBMODULE		int check_comp_fw( memimage *fw )
*.PURPOSE		Checks compatibility of CFI and MFI, NIC as supplier, station/AP firmware image as supplier.
*
*.ARGUMENTS
*   fw         	F/W image to be downloaded
*
*.RETURNS
*   HFC_SUCCESS      	- firmware OK
*   DHF_ERR_INCOMP_FW
*
*.DESCRIPTION
*   This function uses compatibility and identity information that has been
*   retrieved from the card which is currently inserted to check whether the
*   station firmware image to be downloaded is compatible.
*.ENDDOC				END DOCUMENTATION
*************************************************************************************************************/
int
check_comp_fw(memimage *fw)
{
CFG_RANGE20_STRCT  		*p;
int   					rc = HCF_SUCCESS;
CFG_RANGE_SPEC_STRCT *i;

	switch (fw->identity->typ) {
	case CFG_FW_IDENTITY:				/* Station F/W */
	case COMP_ID_FW_AP_FAKE:			/* ;?is this useful (used to be:  CFG_AP_IDENTITY) */
		break;
	default:
		MMDASSERT(DO_ASSERT, fw->identity->typ) 	/* unknown/unsupported firmware_type: */
		rc = DHF_ERR_INCOMP_FW;
		return rc; /* ;? how useful is this anyway,
					*  till that is sorted out might as well violate my own single exit principle
					*/
	}
	p = fw->compat;
	i = NULL;
	while (p->len && i == NULL) {					/* check the MFI ranges */
		if (p->typ  == CFG_MFI_ACT_RANGES_STA) {
			i = mmd_check_comp((void *)p, &mfi_sup);
		}
		p++;
	}
	MMDASSERT(i, 0)	/* MFI: NIC Supplier not compatible with F/W image Actor */
	if (i) {
		p = fw->compat;
		i = NULL;
		while (p->len && i == NULL) {			/* check the CFI ranges */
			if (p->typ  == CFG_CFI_ACT_RANGES_STA) {
				 i = mmd_check_comp((void *)p, &cfi_sup);
			}
			p++;
		}
		MMDASSERT(i, 0)	/* CFI: NIC Supplier not compatible with F/W image Actor */
	}
	if (i == NULL) {
		rc = DHF_ERR_INCOMP_FW;
	}
	return rc;
} /* check_comp_fw */





/*-----------------------------------------------------------------------------
 *
 * Exported functions
 *
 *---------------------------------------------------------------------------*/



/*************************************************************************************************************
*
*.MODULE 		int dhf_download_binary( void *ifbp, memimage *fw )
*.PURPOSE		Downloads a complete (primary, station, or access point) firmware image to the NIC.
*
*.ARGUMENTS
*	ifbp		address of the Interface Block
*   fw         	F/W image to be downloaded
*
*.RETURNS
*   HCF_SUCCESS         	- download completed successfully.
*   DHF_ERR_INCOMP_FW		- firmware not compatible
*
*.DESCRIPTION
*   Initialize global variables
*   Connect to the DHF
*   Check the compatibility of the image (For primary firmware images it is checked first
* 	whether download is necessary).
*   If everything's download the firmware.
*   Disconnect from the DHF.
*
*
*.DIAGRAM
*
*.NOTICE:
	MMDASSERT is unacceptable because some drivers call dhf_download_binary before hcf_connect

* The old comment was:
*.ENDDOC				END DOCUMENTATION
*************************************************************************************************************/
int
dhf_download_binary(memimage *fw)
{
int 			rc = HCF_SUCCESS;
CFG_PROG_STRCT 	*p;
int				i;

	/* validate the image */
	for (i = 0; i < sizeof(signature) && fw->signature[i] == signature[i]; i++)
		; /* NOP */
	if (i != sizeof(signature) 		||
		 fw->signature[i] != 0x01   	||
		 /* test for Little/Big Endian Binary flag */
		 fw->signature[i+1] != (/* HCF_BIG_ENDIAN ? 'B' : */ 'L'))
		rc = DHF_ERR_INCOMP_FW;
	else {					/* Little Endian Binary format */
		fw->codep    = (CFG_PROG_STRCT FAR*)((char *)fw->codep + (hcf_32)fw);
		fw->identity = (CFG_IDENTITY_STRCT FAR*)((char *)fw->identity + (hcf_32)fw);
		fw->compat   = (CFG_RANGE20_STRCT FAR*)((char *)fw->compat + (hcf_32)fw);
		for (i = 0; fw->p[i]; i++)
			fw->p[i] = ((char *)fw->p[i] + (hcf_32)fw);
		p = fw->codep;
		while (p->len) {
			p->host_addr = (char *)p->host_addr + (hcf_32)fw;
			p++;
		}
	}
	return rc;
}   /* dhf_download_binary */


/*************************************************************************************************************
*
*.MODULE 		int dhf_download_fw( void *ifbp, memimage *fw )
*.PURPOSE		Downloads a complete (primary or tertiary) firmware image to the NIC.
*
*.ARGUMENTS
*	ifbp		address of the Interface Block
*   fw     		F/W image to be downloaded
*
*.RETURNS
*	HCF_SUCCESS        	- download completed successfully.
*	HCF_ERR_NO_NIC     	- no NIC present
*	DHF_ERR_INCOMP_FW 	- firmware not compatible
*
*.DESCRIPTION
* - check the signature of the image
* - get the compatibility information from the components on the NIC
*	  - Primary Firmware Identity
*	  -	Modem - Firmware I/F
*	  -	Controller - Firmware I/F
*!! - if necessary ( i.e. H-I) get the PDA contents from the NIC
* - check the compatibility of the MFI and CFI of the NIC with the F/W image
*	Note: the Primary F/W compatibility is only relevant for the "running" HCF and is already verified in
*	hcf_connect
*!! -	if necessary ( i.e. H-I)
*!!	  -	verify the sumcheck of the PDA
*!!	  -	plug the image (based on the PDA and the default plug records)
* - loop over all the download LTVs in the image which consists of a sequence of
*	  - CFG_PROG_VOLATILE/CFG_PROG_NON_VOLATILE
*	  - 1 or more sequences of CFG_PROG_ADDR, CFG_PROG_DATA,....,CFG_PROG_DATA
*	  -	CFG_PROG_STOP
*
*.DIAGRAM
*
*.NOTICE
* The old comment was:
*	// Download primary firmware if necessary and allowed. This is done silently (without telling
*	// the user) and only if the firmware in the download image is newer than the firmware in the
*	// card.  In Major version 4 of the primary firmware functions of Hermes and Shark were
*	// combined. Prior to that two separate versions existed. We only have to download primary
*	// firmware if major version of primary firmware in the NIC < 4.
*	//		download = pri_identity.version_major < 4;
*	//		if ( download ) {
*	//			rc = check_comp_primary( fw );
*	//		}
* It is my understanding that Pri Variant 1 must be updated by Pri Variant 2. The test on
* major version < 4 should amount to the same result but be "principally" less correct
* In deliberation with the Architecture team, it was decided that this upgrade for old H-I
* NICs, is an aspect which belongs on the WSU level not on the DHF level
*
*.ENDDOC				END DOCUMENTATION
*************************************************************************************************************/
int
dhf_download_fw(void *ifbp, memimage *fw)
{
int 				rc = HCF_SUCCESS;
LTV_INFO_STRUCT_PTR pp = ltv_info;
CFG_PROG_STRCT 		*p = fw->codep;
LTVP 				ltvp;
int					i;

	MMDASSERT(fw != NULL, 0)
	/* validate the image */
	for (i = 0; i < sizeof(signature) && fw->signature[i] == signature[i]; i++)
		; /* NOP */
	if (i != sizeof(signature) 		||
		 fw->signature[i] != 0x01		||
		 /* check for binary image */
		 (fw->signature[i+1] != 'C' && fw->signature[i+1] != (/*HCF_BIG_ENDIAN ? 'B' : */ 'L')))
		 rc = DHF_ERR_INCOMP_FW;

/*	Retrieve all information needed for download from the NIC */
	while ((rc == HCF_SUCCESS) && ((ltvp = pp->ltvp) != NULL)) {
		ltvp->len = pp++->len;	/* Set len to original len. This len is changed to real len by GET_INFO() */
		rc = GET_INFO(ltvp);
		MMDASSERT(rc == HCF_SUCCESS, rc)
		MMDASSERT(rc == HCF_SUCCESS, ltvp->typ)
		MMDASSERT(rc == HCF_SUCCESS, ltvp->len)
	}
	if (rc == HCF_SUCCESS)
		rc = check_comp_fw(fw);
	if (rc == HCF_SUCCESS) {
		while (rc == HCF_SUCCESS && p->len) {
			rc = PUT_INFO(p);
			p++;
		}
	}
	MMDASSERT(rc == HCF_SUCCESS, rc)
	return rc;
}   /* dhf_download_fw */


