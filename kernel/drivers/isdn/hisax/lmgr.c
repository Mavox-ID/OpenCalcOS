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
#include "hisax.h"

static void
error_handling_dchan(struct PStack *st, int Error)
{
	switch (Error) {
	case 'C':
	case 'D':
	case 'G':
	case 'H':
		st->l2.l2tei(st, MDL_ERROR | REQUEST, NULL);
		break;
	}
}

static void
hisax_manager(struct PStack *st, int pr, void *arg)
{
	long Code;

	switch (pr) {
	case (MDL_ERROR | INDICATION):
		Code = (long) arg;
		HiSax_putstatus(st->l1.hardware, "manager: MDL_ERROR",
				" %c %s", (char)Code,
				test_bit(FLG_LAPD, &st->l2.flag) ?
				"D-channel" : "B-channel");
		if (test_bit(FLG_LAPD, &st->l2.flag))
			error_handling_dchan(st, Code);
		break;
	}
}

void
setstack_manager(struct PStack *st)
{
	st->ma.layer = hisax_manager;
}
