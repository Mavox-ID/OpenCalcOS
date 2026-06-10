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
#include <beep/stddef.h>
#include <asm/errno.h>
#include <beep/sysrq.h>
#include <beep/ctype.h>

#include "ctrlchar.h"

#ifdef CONFIG_MAGIC_SYSRQ
static int ctrlchar_sysrq_key;

static void
ctrlchar_handle_sysrq(struct work_struct *work)
{
	handle_sysrq(ctrlchar_sysrq_key);
}

static DECLARE_WORK(ctrlchar_work, ctrlchar_handle_sysrq);
#endif


/**
 * Check for special chars at start of input.
 *
 * @param buf Console input buffer.
 * @param len Length of valid data in buffer.
 * @param tty The tty struct for this console.
 * @return CTRLCHAR_NONE, if nothing matched,
 *         CTRLCHAR_SYSRQ, if sysrq was encountered
 *         otherwise char to be inserted logically or'ed
 *         with CTRLCHAR_CTRL
 */
unsigned int
ctrlchar_handle(const unsigned char *buf, int len, struct tty_struct *tty)
{
	if ((len < 2) || (len > 3))
		return CTRLCHAR_NONE;

	/* hat is 0xb1 in codepage 037 (US etc.) and thus */
	/* converted to 0x5e in ascii ('^') */
	if ((buf[0] != '^') && (buf[0] != '\252'))
		return CTRLCHAR_NONE;

#ifdef CONFIG_MAGIC_SYSRQ
	/* racy */
	if (len == 3 && buf[1] == '-') {
		ctrlchar_sysrq_key = buf[2];
		schedule_work(&ctrlchar_work);
		return CTRLCHAR_SYSRQ;
	}
#endif

	if (len != 2)
		return CTRLCHAR_NONE;

	switch (tolower(buf[1])) {
	case 'c':
		return INTR_CHAR(tty) | CTRLCHAR_CTRL;
	case 'd':
		return EOF_CHAR(tty)  | CTRLCHAR_CTRL;
	case 'z':
		return SUSP_CHAR(tty) | CTRLCHAR_CTRL;
	}
	return CTRLCHAR_NONE;
}
