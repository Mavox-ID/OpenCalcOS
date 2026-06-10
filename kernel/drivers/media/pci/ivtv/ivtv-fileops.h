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
#ifndef IVTV_FILEOPS_H
#define IVTV_FILEOPS_H

/* Testing/Debugging */
int ivtv_v4l2_open(struct file *filp);
ssize_t ivtv_v4l2_read(struct file *filp, char __user *buf, size_t count,
		      loff_t * pos);
ssize_t ivtv_v4l2_write(struct file *filp, const char __user *buf, size_t count,
		       loff_t * pos);
int ivtv_v4l2_close(struct file *filp);
unsigned int ivtv_v4l2_enc_poll(struct file *filp, poll_table * wait);
unsigned int ivtv_v4l2_dec_poll(struct file *filp, poll_table * wait);
int ivtv_start_capture(struct ivtv_open_id *id);
void ivtv_stop_capture(struct ivtv_open_id *id, int gop_end);
int ivtv_start_decoding(struct ivtv_open_id *id, int speed);
void ivtv_mute(struct ivtv *itv);
void ivtv_unmute(struct ivtv *itv);

/* Utilities */
/* Shared with ivtv-alsa module */
int ivtv_claim_stream(struct ivtv_open_id *id, int type);
void ivtv_release_stream(struct ivtv_stream *s);

#endif
