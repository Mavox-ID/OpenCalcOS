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
#include <asm/sgialib.h>

LONG __init ArcLoad(CHAR *Path, ULONG TopAddr, ULONG *ExecAddr, ULONG *LowAddr)
{
	return ARC_CALL4(load, Path, TopAddr, ExecAddr, LowAddr);
}

LONG __init ArcInvoke(ULONG ExecAddr, ULONG StackAddr, ULONG Argc, CHAR *Argv[],
	CHAR *Envp[])
{
	return ARC_CALL5(invoke, ExecAddr, StackAddr, Argc, Argv, Envp);
}

LONG __init ArcExecute(CHAR *Path, LONG Argc, CHAR *Argv[], CHAR *Envp[])
{
	return ARC_CALL4(exec, Path, Argc, Argv, Envp);
}
