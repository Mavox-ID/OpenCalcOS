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
#ifndef SSP_H
#define SSP_H

struct ssp_state {
	unsigned int	cr0;
	unsigned int	cr1;
};

int ssp_write_word(u16 data);
int ssp_read_word(u16 *data);
int ssp_flush(void);
void ssp_enable(void);
void ssp_disable(void);
void ssp_save_state(struct ssp_state *ssp);
void ssp_restore_state(struct ssp_state *ssp);
int ssp_init(void);
void ssp_exit(void);

#endif
