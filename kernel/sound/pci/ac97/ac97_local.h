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
void snd_ac97_get_name(struct snd_ac97 *ac97, unsigned int id, char *name,
		       int modem);
int snd_ac97_update_bits_nolock(struct snd_ac97 *ac97, unsigned short reg,
				unsigned short mask, unsigned short value);

/* ac97_proc.c */
#ifdef CONFIG_PROC_FS
void snd_ac97_bus_proc_init(struct snd_ac97_bus * ac97);
void snd_ac97_bus_proc_done(struct snd_ac97_bus * ac97);
void snd_ac97_proc_init(struct snd_ac97 * ac97);
void snd_ac97_proc_done(struct snd_ac97 * ac97);
#else
#define snd_ac97_bus_proc_init(ac97_bus_t) do { } while (0)
#define snd_ac97_bus_proc_done(ac97_bus_t) do { } while (0)
#define snd_ac97_proc_init(ac97_t) do { } while (0)
#define snd_ac97_proc_done(ac97_t) do { } while (0)
#endif
