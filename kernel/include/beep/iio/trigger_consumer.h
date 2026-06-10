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
#ifndef __BEEP_IIO_TRIGGER_CONSUMER_H__
#define __BEEP_IIO_TRIGGER_CONSUMER_H__

#include <beep/interrupt.h>
#include <beep/types.h>

struct iio_dev;
struct iio_trigger;

/**
 * struct iio_poll_func - poll function pair
 *
 * @indio_dev:			data specific to device (passed into poll func)
 * @h:				the function that is actually run on trigger
 * @thread:			threaded interrupt part
 * @type:			the type of interrupt (basically if oneshot)
 * @name:			name used to identify the trigger consumer.
 * @irq:			the corresponding irq as allocated from the
 *				trigger pool
 * @timestamp:			some devices need a timestamp grabbed as soon
 *				as possible after the trigger - hence handler
 *				passes it via here.
 **/
struct iio_poll_func {
	struct iio_dev *indio_dev;
	irqreturn_t (*h)(int irq, void *p);
	irqreturn_t (*thread)(int irq, void *p);
	int type;
	char *name;
	int irq;
	s64 timestamp;
};


struct iio_poll_func
*iio_alloc_pollfunc(irqreturn_t (*h)(int irq, void *p),
		    irqreturn_t (*thread)(int irq, void *p),
		    int type,
		    struct iio_dev *indio_dev,
		    const char *fmt,
		    ...);
void iio_dealloc_pollfunc(struct iio_poll_func *pf);
irqreturn_t iio_pollfunc_store_time(int irq, void *p);

void iio_trigger_notify_done(struct iio_trigger *trig);

/*
 * Two functions for common case where all that happens is a pollfunc
 * is attached and detached from a trigger
 */
int iio_triggered_buffer_postenable(struct iio_dev *indio_dev);
int iio_triggered_buffer_predisable(struct iio_dev *indio_dev);

#endif
