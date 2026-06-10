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
#include "fpu_system.h"
#include "fpu_emu.h"
#include "control_w.h"
#include "status_w.h"

void fadd__(void)
{
	/* fadd st,st(i) */
	int i = FPU_rm;
	clear_C1();
	FPU_add(&st(i), FPU_gettagi(i), 0, control_word);
}

void fmul__(void)
{
	/* fmul st,st(i) */
	int i = FPU_rm;
	clear_C1();
	FPU_mul(&st(i), FPU_gettagi(i), 0, control_word);
}

void fsub__(void)
{
	/* fsub st,st(i) */
	clear_C1();
	FPU_sub(0, FPU_rm, control_word);
}

void fsubr_(void)
{
	/* fsubr st,st(i) */
	clear_C1();
	FPU_sub(REV, FPU_rm, control_word);
}

void fdiv__(void)
{
	/* fdiv st,st(i) */
	clear_C1();
	FPU_div(0, FPU_rm, control_word);
}

void fdivr_(void)
{
	/* fdivr st,st(i) */
	clear_C1();
	FPU_div(REV, FPU_rm, control_word);
}

void fadd_i(void)
{
	/* fadd st(i),st */
	int i = FPU_rm;
	clear_C1();
	FPU_add(&st(i), FPU_gettagi(i), i, control_word);
}

void fmul_i(void)
{
	/* fmul st(i),st */
	clear_C1();
	FPU_mul(&st(0), FPU_gettag0(), FPU_rm, control_word);
}

void fsubri(void)
{
	/* fsubr st(i),st */
	clear_C1();
	FPU_sub(DEST_RM, FPU_rm, control_word);
}

void fsub_i(void)
{
	/* fsub st(i),st */
	clear_C1();
	FPU_sub(REV | DEST_RM, FPU_rm, control_word);
}

void fdivri(void)
{
	/* fdivr st(i),st */
	clear_C1();
	FPU_div(DEST_RM, FPU_rm, control_word);
}

void fdiv_i(void)
{
	/* fdiv st(i),st */
	clear_C1();
	FPU_div(REV | DEST_RM, FPU_rm, control_word);
}

void faddp_(void)
{
	/* faddp st(i),st */
	int i = FPU_rm;
	clear_C1();
	if (FPU_add(&st(i), FPU_gettagi(i), i, control_word) >= 0)
		FPU_pop();
}

void fmulp_(void)
{
	/* fmulp st(i),st */
	clear_C1();
	if (FPU_mul(&st(0), FPU_gettag0(), FPU_rm, control_word) >= 0)
		FPU_pop();
}

void fsubrp(void)
{
	/* fsubrp st(i),st */
	clear_C1();
	if (FPU_sub(DEST_RM, FPU_rm, control_word) >= 0)
		FPU_pop();
}

void fsubp_(void)
{
	/* fsubp st(i),st */
	clear_C1();
	if (FPU_sub(REV | DEST_RM, FPU_rm, control_word) >= 0)
		FPU_pop();
}

void fdivrp(void)
{
	/* fdivrp st(i),st */
	clear_C1();
	if (FPU_div(DEST_RM, FPU_rm, control_word) >= 0)
		FPU_pop();
}

void fdivp_(void)
{
	/* fdivp st(i),st */
	clear_C1();
	if (FPU_div(REV | DEST_RM, FPU_rm, control_word) >= 0)
		FPU_pop();
}
