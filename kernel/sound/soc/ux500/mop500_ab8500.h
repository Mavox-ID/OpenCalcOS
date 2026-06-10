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
#ifndef MOP500_AB8500_H
#define MOP500_AB8500_H

extern struct snd_soc_ops mop500_ab8500_ops[];

int mop500_ab8500_machine_init(struct snd_soc_pcm_runtime *runtime);
void mop500_ab8500_remove(struct snd_soc_card *card);

#endif
