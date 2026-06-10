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
#ifndef IVTV_MAILBOX_H
#define IVTV_MAILBOX_H

#define IVTV_MBOX_DMA_END         8
#define IVTV_MBOX_DMA             9

void ivtv_api_get_data(struct ivtv_mailbox_data *mbdata, int mb,
		       int argc, u32 data[]);
int ivtv_api(struct ivtv *itv, int cmd, int args, u32 data[]);
int ivtv_vapi_result(struct ivtv *itv, u32 data[CX2341X_MBOX_MAX_DATA], int cmd, int args, ...);
int ivtv_vapi(struct ivtv *itv, int cmd, int args, ...);
int ivtv_api_func(void *priv, u32 cmd, int in, int out, u32 data[CX2341X_MBOX_MAX_DATA]);
void ivtv_mailbox_cache_invalidate(struct ivtv *itv);

#endif
