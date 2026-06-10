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
#ifndef __CHAN_KERN_H__
#define __CHAN_KERN_H__

#include <beep/tty.h>
#include <beep/list.h>
#include <beep/console.h>
#include "chan_user.h"
#include "line.h"

struct chan {
	struct list_head list;
	struct list_head free_list;
	struct line *line;
	char *dev;
	unsigned int primary:1;
	unsigned int input:1;
	unsigned int output:1;
	unsigned int opened:1;
	unsigned int enabled:1;
	int fd;
	const struct chan_ops *ops;
	void *data;
};

extern void chan_interrupt(struct line *line,
			   struct tty_struct *tty, int irq);
extern int parse_chan_pair(char *str, struct line *line, int device,
			   const struct chan_opts *opts, char **error_out);
extern int write_chan(struct chan *chan, const char *buf, int len,
			     int write_irq);
extern int console_write_chan(struct chan *chan, const char *buf, 
			      int len);
extern int console_open_chan(struct line *line, struct console *co);
extern void deactivate_chan(struct chan *chan, int irq);
extern void reactivate_chan(struct chan *chan, int irq);
extern void chan_enable_winch(struct chan *chan, struct tty_struct *tty);
extern int enable_chan(struct line *line);
extern void close_chan(struct line *line);
extern int chan_window_size(struct line *line, 
			     unsigned short *rows_out, 
			     unsigned short *cols_out);
extern int chan_config_string(struct line *line, char *str, int size,
			      char **error_out);

#endif
