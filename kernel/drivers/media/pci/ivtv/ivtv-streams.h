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
#ifndef IVTV_STREAMS_H
#define IVTV_STREAMS_H

int ivtv_streams_setup(struct ivtv *itv);
int ivtv_streams_register(struct ivtv *itv);
void ivtv_streams_cleanup(struct ivtv *itv, int unregister);

/* Capture related */
int ivtv_start_v4l2_encode_stream(struct ivtv_stream *s);
int ivtv_stop_v4l2_encode_stream(struct ivtv_stream *s, int gop_end);
int ivtv_start_v4l2_decode_stream(struct ivtv_stream *s, int gop_offset);
int ivtv_stop_v4l2_decode_stream(struct ivtv_stream *s, int flags, u64 pts);

void ivtv_stop_all_captures(struct ivtv *itv);
int ivtv_passthrough_mode(struct ivtv *itv, int enable);

#endif
