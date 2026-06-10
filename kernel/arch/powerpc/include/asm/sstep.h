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
struct pt_regs;

/*
 * We don't allow single-stepping an mtmsrd that would clear
 * MSR_RI, since that would make the exception unrecoverable.
 * Since we need to single-step to proceed from a breakpoint,
 * we don't allow putting a breakpoint on an mtmsrd instruction.
 * Similarly we don't allow breakpoints on rfid instructions.
 * These macros tell us if an instruction is a mtmsrd or rfid.
 * Note that IS_MTMSRD returns true for both an mtmsr (32-bit)
 * and an mtmsrd (64-bit).
 */
#define IS_MTMSRD(instr)	(((instr) & 0xfc0007be) == 0x7c000124)
#define IS_RFID(instr)		(((instr) & 0xfc0007fe) == 0x4c000024)
#define IS_RFI(instr)		(((instr) & 0xfc0007fe) == 0x4c000064)

/* Emulate instructions that cause a transfer of control. */
extern int emulate_step(struct pt_regs *regs, unsigned int instr);
