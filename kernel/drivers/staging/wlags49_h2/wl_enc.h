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
#ifndef __WAVELAN2_ENCRYPTION_H__
#define __WAVELAN2_ENCRYPTION_H__




/*******************************************************************************
 * constant definitions
 ******************************************************************************/
#define CRYPT_CODE					"57617665A5D6"
#define ENCRYPTION_LEN				102
#define ENCRYPTION_MAGIC			0x48576877L	// HWhw
#define DEF_CRYPT_STR				"G?TIUEA]d5MAdZV'eUb&&6.)'&:,'VF/(FR2)6^5*'*8*W6;+GB>,7NA-'ZD-X&G.H2J/8>M0(JP0XVS1HbV29.Y3):\\3YF_4IRb56"

#define DEFAULT_CRYPT_MAC			"W\x01\x6B\x66\xA5\x5A"
#define CH_START					'&'
#define MACADDRESS_STR_LEN			12

#define KEY_LEN                     14
#define NUM_KEYS                    4

#define KEY_LENGTH_NONE_ASCII       0
#define KEY_LENGTH_64_BIT_ASCII     5
#define KEY_LENGTH_128_BIT_ASCII    13

#define KEY_LENGTH_NONE_HEX         ( KEY_LENGTH_NONE_ASCII    * sizeof( unsigned short ))
#define KEY_LENGTH_64_BIT_HEX       ( KEY_LENGTH_64_BIT_ASCII  * sizeof( unsigned short ))
#define KEY_LENGTH_128_BIT_HEX      ( KEY_LENGTH_128_BIT_ASCII * sizeof( unsigned short ))




/*******************************************************************************
 * type definitions
 ******************************************************************************/
typedef struct _encstct
{
	hcf_32	                   dwMagic;
	hcf_16	                   wTxKeyID;
	hcf_16	                   wEnabled;
	CFG_DEFAULT_KEYS_STRCT     EncStr;
}
ENCSTRCT, *PENCSTRCT;




/*******************************************************************************
 * function prototypes
 ******************************************************************************/
int wl_wep_code( char *szCrypt, char *szDest, void *Data, int nLen );

int wl_wep_decode( char *szCrypt, void *Dest, char *szData );




#endif  // __WAVELAN2_ENCRYPTION_H__
