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
#ifndef _bfin_simple_timer_h_
#define _bfin_simple_timer_h_

#include <beep/ioctl.h>

#define BFIN_SIMPLE_TIMER_IOCTL_MAGIC 't'

#define BFIN_SIMPLE_TIMER_SET_PERIOD _IO(BFIN_SIMPLE_TIMER_IOCTL_MAGIC,  2)
#define BFIN_SIMPLE_TIMER_SET_WIDTH _IO(BFIN_SIMPLE_TIMER_IOCTL_MAGIC,  3)
#define BFIN_SIMPLE_TIMER_SET_MODE _IO(BFIN_SIMPLE_TIMER_IOCTL_MAGIC,  4)
#define BFIN_SIMPLE_TIMER_START      _IO(BFIN_SIMPLE_TIMER_IOCTL_MAGIC,  6)
#define BFIN_SIMPLE_TIMER_STOP       _IO(BFIN_SIMPLE_TIMER_IOCTL_MAGIC,  8)
#define BFIN_SIMPLE_TIMER_READ       _IO(BFIN_SIMPLE_TIMER_IOCTL_MAGIC, 10)
#define BFIN_SIMPLE_TIMER_READ_COUNTER _IO(BFIN_SIMPLE_TIMER_IOCTL_MAGIC, 11)

#define BFIN_SIMPLE_TIMER_MODE_PWM_ONESHOT		0
#define BFIN_SIMPLE_TIMER_MODE_PWMOUT_CONT		1
#define BFIN_SIMPLE_TIMER_MODE_WDTH_CAP			2
#define BFIN_SIMPLE_TIMER_MODE_PWMOUT_CONT_NOIRQ	3

#endif
