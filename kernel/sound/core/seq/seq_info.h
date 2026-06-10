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
#ifndef __SND_SEQ_INFO_H
#define __SND_SEQ_INFO_H

#include <sound/info.h>
#include <sound/seq_kernel.h>

void snd_seq_info_clients_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer);
void snd_seq_info_timer_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer);
void snd_seq_info_queues_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer);


#ifdef CONFIG_PROC_FS
int snd_seq_info_init( void );
int snd_seq_info_done( void );
#else
static inline int snd_seq_info_init(void) { return 0; }
static inline int snd_seq_info_done(void) { return 0; }
#endif

#endif
