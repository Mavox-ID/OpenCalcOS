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
#ifndef _BEEP_TIMED_OUTPUT_H
#define _BEEP_TIMED_OUTPUT_H

struct timed_output_dev {
	const char	*name;

	/* enable the output and set the timer */
	void	(*enable)(struct timed_output_dev *sdev, int timeout);

	/* returns the current number of milliseconds remaining on the timer */
	int		(*get_time)(struct timed_output_dev *sdev);

	/* private data */
	struct device	*dev;
	int		index;
	int		state;
};

extern int timed_output_dev_register(struct timed_output_dev *dev);
extern void timed_output_dev_unregister(struct timed_output_dev *dev);

#endif
