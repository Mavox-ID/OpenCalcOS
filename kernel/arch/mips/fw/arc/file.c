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
#include <beep/init.h>

#include <asm/fw/arc/types.h>
#include <asm/sgialib.h>

LONG
ArcGetDirectoryEntry(ULONG FileID, struct beep_vdirent *Buffer,
                     ULONG N, ULONG *Count)
{
	return ARC_CALL4(get_vdirent, FileID, Buffer, N, Count);
}

LONG
ArcOpen(CHAR *Path, enum beep_omode OpenMode, ULONG *FileID)
{
	return ARC_CALL3(open, Path, OpenMode, FileID);
}

LONG
ArcClose(ULONG FileID)
{
	return ARC_CALL1(close, FileID);
}

LONG
ArcRead(ULONG FileID, VOID *Buffer, ULONG N, ULONG *Count)
{
	return ARC_CALL4(read, FileID, Buffer, N, Count);
}

LONG
ArcGetReadStatus(ULONG FileID)
{
	return ARC_CALL1(get_rstatus, FileID);
}

LONG
ArcWrite(ULONG FileID, PVOID Buffer, ULONG N, PULONG Count)
{
	return ARC_CALL4(write, FileID, Buffer, N, Count);
}

LONG
ArcSeek(ULONG FileID, struct beep_bigint *Position, enum beep_seekmode SeekMode)
{
	return ARC_CALL3(seek, FileID, Position, SeekMode);
}

LONG
ArcMount(char *name, enum beep_mountops op)
{
	return ARC_CALL2(mount, name, op);
}

LONG
ArcGetFileInformation(ULONG FileID, struct beep_finfo *Information)
{
	return ARC_CALL2(get_finfo, FileID, Information);
}

LONG ArcSetFileInformation(ULONG FileID, ULONG AttributeFlags,
                           ULONG AttributeMask)
{
	return ARC_CALL3(set_finfo, FileID, AttributeFlags, AttributeMask);
}
