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
#ifndef _DIVA_USER_MODE_IDI_DATA_QUEUE_H__
#define _DIVA_USER_MODE_IDI_DATA_QUEUE_H__

#define DIVA_UM_IDI_MAX_MSGS 64

typedef struct _diva_um_idi_data_queue {
	int segments;
	int max_length;
	int read;
	int write;
	int count;
	int segment_pending;
	void *data[DIVA_UM_IDI_MAX_MSGS];
	int length[DIVA_UM_IDI_MAX_MSGS];
} diva_um_idi_data_queue_t;

int diva_data_q_init(diva_um_idi_data_queue_t *q,
		     int max_length, int max_segments);
int diva_data_q_finit(diva_um_idi_data_queue_t *q);
int diva_data_q_get_max_length(const diva_um_idi_data_queue_t *q);
void *diva_data_q_get_segment4write(diva_um_idi_data_queue_t *q);
void diva_data_q_ack_segment4write(diva_um_idi_data_queue_t *q,
				   int length);
const void *diva_data_q_get_segment4read(const diva_um_idi_data_queue_t *
					 q);
int diva_data_q_get_segment_length(const diva_um_idi_data_queue_t *q);
void diva_data_q_ack_segment4read(diva_um_idi_data_queue_t *q);

#endif
