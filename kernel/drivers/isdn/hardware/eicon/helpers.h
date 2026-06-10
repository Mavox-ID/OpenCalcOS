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
#ifndef __DIVA_XDI_CARD_CONFIG_HELPERS_INC__
#define __DIVA_XDI_CARD_CONFIG_HELPERS_INC__
dword diva_get_protocol_file_features(byte *File,
				      int offset,
				      char *IdStringBuffer,
				      dword IdBufferSize);
void diva_configure_protocol(PISDN_ADAPTER IoAdapter);
/*
  Low level file access system abstraction
*/
/* -------------------------------------------------------------------------
   Access to single file
   Return pointer to the image of the requested file,
   write image length to 'FileLength'
   ------------------------------------------------------------------------- */
void *xdiLoadFile(char *FileName, dword *FileLength, unsigned long MaxLoadSize);
/* -------------------------------------------------------------------------
   Dependent on the protocol settings does read return pointer
   to the image of appropriate protocol file
   ------------------------------------------------------------------------- */
void *xdiLoadArchive(PISDN_ADAPTER IoAdapter, dword *FileLength, unsigned long MaxLoadSize);
/* --------------------------------------------------------------------------
   Free all system resources accessed by xdiLoadFile and xdiLoadArchive
   -------------------------------------------------------------------------- */
void xdiFreeFile(void *handle);
#endif
