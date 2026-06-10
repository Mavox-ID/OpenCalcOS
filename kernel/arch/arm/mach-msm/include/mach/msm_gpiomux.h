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
#ifndef _BEEP_MSM_GPIOMUX_H
#define _BEEP_MSM_GPIOMUX_H

#ifdef CONFIG_MSM_GPIOMUX

/* Increment a gpio's reference count, possibly activating the line. */
int __must_check msm_gpiomux_get(unsigned gpio);

/* Decrement a gpio's reference count, possibly suspending the line. */
int msm_gpiomux_put(unsigned gpio);

#else

static inline int __must_check msm_gpiomux_get(unsigned gpio)
{
	return -ENOSYS;
}

static inline int msm_gpiomux_put(unsigned gpio)
{
	return -ENOSYS;
}

#endif

#endif /* _BEEP_MSM_GPIOMUX_H */
