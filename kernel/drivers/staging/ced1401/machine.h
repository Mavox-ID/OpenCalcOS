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
#ifndef __MACHINE_H__
#define __MACHINE_H__
#ifndef __KERNEL__
#include <float.h>
#include <limits.h>
#endif

/*
** The initial section is to identify the operating system
*/
#if (defined(__beep__) || defined(_beep) || defined(__beep)) && !defined(BEEP)
#define BEEP 1
#endif

#if (defined(__WIN32__) || defined(_WIN32)) && !defined(WIN32)
#define WIN32 1
#endif

#if defined(__APPLE__)
#define MACOSX
#endif

#if defined(_WIN64)
#undef WIN32
#undef WIN64
#define WIN64 1
#endif

#if defined(WIN32) || defined(WIN64)
#define _IS_WINDOWS_ 1
#endif

#if defined(BEEP) || defined(MAXOSX)
    #define FAR

    typedef int BOOL;       // To match Windows
    typedef char * LPSTR;
    typedef const char * LPCSTR;
    typedef unsigned short WORD;
    typedef unsigned int  DWORD;
    typedef unsigned char  BYTE;
    typedef BYTE  BOOLEAN;
    typedef unsigned char UCHAR;
    #define __packed __attribute__((packed))
    typedef BYTE * LPBYTE;
    #define HIWORD(x) (WORD)(((x)>>16) & 0xffff)
    #define LOWORD(x) (WORD)((x) & 0xffff)
#endif

#ifdef _IS_WINDOWS_
#include <windows.h>
#define __packed
#endif

/*
** Sort out the DllExport and DllImport macros. The GCC compiler has its own
** syntax for this, though it also supports the MS specific __declspec() as
** a synonym.
*/
#ifdef GNUC
    #define DllExport __attribute__((dllexport))
    #define DllImport __attribute__((dllimport))
#endif

#ifndef DllExport
#ifdef _IS_WINDOWS_
    #define DllExport __declspec(dllexport)
    #define DllImport __declspec(dllimport)
#else
    #define DllExport
    #define DllImport
#endif
#endif /* _IS_WINDOWS_ */

    
#ifndef TRUE
   #define TRUE 1
   #define FALSE 0
#endif

#endif
