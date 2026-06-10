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
#ifndef __CTTIMER_H
#define __CTTIMER_H

#include <beep/spinlock.h>
#include <beep/timer.h>
#include <beep/list.h>

struct snd_pcm_substream;
struct ct_atc;
struct ct_atc_pcm;

struct ct_timer;
struct ct_timer_instance;

struct ct_timer *ct_timer_new(struct ct_atc *atc);
void ct_timer_free(struct ct_timer *atimer);

struct ct_timer_instance *
ct_timer_instance_new(struct ct_timer *atimer, struct ct_atc_pcm *apcm);
void ct_timer_instance_free(struct ct_timer_instance *ti);
void ct_timer_start(struct ct_timer_instance *ti);
void ct_timer_stop(struct ct_timer_instance *ti);
void ct_timer_prepare(struct ct_timer_instance *ti);

#endif /* __CTTIMER_H */
