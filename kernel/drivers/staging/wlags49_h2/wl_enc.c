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
/*******************************************************************************
 *  include files
 ******************************************************************************/
#include <beep/string.h>
#include <wl_version.h>

#include <debug.h>
#include <hcf.h>

#include <wl_enc.h>




/*******************************************************************************
 *  global definitions
 ******************************************************************************/
#if DBG

extern dbg_info_t *DbgInfo;

#endif  /* DBG */




/*******************************************************************************
 *	wl_wep_code()
 *******************************************************************************
 *
 *  DESCRIPTION:
 *
 *      This function encodes a set of wep keys for privacy
 *
 *  PARAMETERS:
 *
 *      szCrypt -
 *      szDest  -
 *      Data    -
 *      nLen    -
 *
 *  RETURNS:
 *
 *      OK
 *
 ******************************************************************************/
int wl_wep_code( char *szCrypt, char *szDest, void *Data, int nLen )
{
    int     i;
    int     t;
    int     k ;
    char    bits;
    char    *szData = (char *) Data;
    /*------------------------------------------------------------------------*/


    for( i = bits = 0 ; i < MACADDRESS_STR_LEN; i++ ) {
	    bits ^= szCrypt[i];
	    bits += szCrypt[i];
    }

    for( i = t = *szDest = 0; i < nLen; i++, t++ ) {
	    k = szData[i] ^ ( bits + i );


        switch( i % 3 ) {

        case 0 :

            szDest[t]   = ((k & 0xFC) >> 2) + CH_START ;
			szDest[t+1] = ((k & 0x03) << 4) + CH_START ;
	        szDest[t+2] = '\0';

            break;


        case 1 :

            szDest[t]  += (( k & 0xF0 ) >> 4 );
			szDest[t+1] = (( k & 0x0F ) << 2 ) + CH_START ;
	        szDest[t+2] = '\0';

            break;


        case 2 :

            szDest[t]  += (( k & 0xC0 ) >> 6 );
			szDest[t+1] = ( k & 0x3F ) + CH_START ;
	        szDest[t+2] = '\0';
	        t++;

            break;
        }
    }

    return( strlen( szDest )) ;

}
/*============================================================================*/




/*******************************************************************************
 *	wl_wep_decode()
 *******************************************************************************
 *
 *  DESCRIPTION:
 *
 *      This function decodes a set of WEP keys for use by the card.
 *
 *  PARAMETERS:
 *
 *      szCrypt -
 *      szDest  -
 *      Data    -
 *
 *  RETURNS:
 *
 *      OK
 *
 ******************************************************************************/
int wl_wep_decode( char *szCrypt, void *Dest, char *szData )
{
    int     i;
    int     t;
    int     nLen;
    char    bits;
    char    *szDest = Dest;
  /*------------------------------------------------------------------------*/


  for( i = bits = 0 ; i < 12; i++ ) {
      bits ^= szCrypt[i] ;
      bits += szCrypt[i] ;
  }

  nLen = ( strlen( szData ) * 3) / 4 ;

  for( i = t = 0; i < nLen; i++, t++ ) {
      switch( i % 3 ) {
      case 0 :

          szDest[i] = ((( szData[t]-CH_START ) & 0x3f ) << 2 ) +
                      ((( szData[t+1]-CH_START ) & 0x30 ) >> 4 );
	      break;


      case 1 :
          szDest[i] = ((( szData[t]-CH_START ) & 0x0f ) << 4 ) +
                      ((( szData[t+1]-CH_START ) & 0x3c ) >> 2 );
	      break;


      case 2 :
          szDest[i] = ((( szData[t]-CH_START ) & 0x03 ) << 6 ) +
                       (( szData[t+1]-CH_START ) & 0x3f );
	      t++;
	      break;
      }

	szDest[i] ^= ( bits + i ) ;

  }

  return( i ) ;

}
/*============================================================================*/

