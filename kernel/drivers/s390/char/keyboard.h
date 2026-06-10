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
#include <beep/tty.h>
#include <beep/tty_flip.h>
#include <beep/keyboard.h>

#define NR_FN_HANDLER	20

struct kbd_data;

typedef void (fn_handler_fn)(struct kbd_data *);

/*
 * FIXME: explain key_maps tricks.
 */

struct kbd_data {
	struct tty_port *port;
	unsigned short **key_maps;
	char **func_table;
	fn_handler_fn **fn_handler;
	struct kbdiacruc *accent_table;
	unsigned int accent_table_size;
	unsigned int diacr;
	unsigned short sysrq;
};

struct kbd_data *kbd_alloc(void);
void kbd_free(struct kbd_data *);
void kbd_ascebc(struct kbd_data *, unsigned char *);

void kbd_keycode(struct kbd_data *, unsigned int);
int kbd_ioctl(struct kbd_data *, unsigned int, unsigned long);

/*
 * Helper Functions.
 */
static inline void
kbd_put_queue(struct tty_port *port, int ch)
{
	struct tty_struct *tty = tty_port_tty_get(port);
	if (!tty)
		return;
	tty_insert_flip_char(tty, ch, 0);
	tty_schedule_flip(tty);
	tty_kref_put(tty);
}

static inline void
kbd_puts_queue(struct tty_port *port, char *cp)
{
	struct tty_struct *tty = tty_port_tty_get(port);
	if (!tty)
		return;
	while (*cp)
		tty_insert_flip_char(tty, *cp++, 0);
	tty_schedule_flip(tty);
	tty_kref_put(tty);
}
