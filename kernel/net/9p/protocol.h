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
int p9pdu_vwritef(struct p9_fcall *pdu, int proto_version, const char *fmt,
								va_list ap);
int p9pdu_readf(struct p9_fcall *pdu, int proto_version, const char *fmt, ...);
int p9pdu_prepare(struct p9_fcall *pdu, int16_t tag, int8_t type);
int p9pdu_finalize(struct p9_client *clnt, struct p9_fcall *pdu);
void p9pdu_reset(struct p9_fcall *pdu);
size_t pdu_read(struct p9_fcall *pdu, void *data, size_t size);
