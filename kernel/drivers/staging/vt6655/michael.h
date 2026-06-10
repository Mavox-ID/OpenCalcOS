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
#ifndef __MICHAEL_H__
#define __MICHAEL_H__

/*---------------------  Export Definitions -------------------------*/

/*---------------------  Export Types  ------------------------------*/

void MIC_vInit(unsigned long dwK0, unsigned long dwK1);

void MIC_vUnInit(void);

// Append bytes to the message to be MICed
void MIC_vAppend(unsigned char *src, unsigned int nBytes);

// Get the MIC result. Destination should accept 8 bytes of result.
// This also resets the message to empty.
void MIC_vGetMIC(unsigned long *pdwL, unsigned long *pdwR);

/*---------------------  Export Macros ------------------------------*/

// Rotation functions on 32 bit values
#define ROL32( A, n ) \
 ( ((A) << (n)) | ( ((A)>>(32-(n)))  & ( (1UL << (n)) - 1 ) ) )
#define ROR32( A, n ) ROL32( (A), 32-(n) )

#endif //__MICHAEL_H__


