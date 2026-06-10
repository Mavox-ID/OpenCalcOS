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
#ifdef CONFIG_CPU_S3C2412

extern  int s3c2412_init(void);

extern void s3c2412_map_io(void);

extern void s3c2412_init_uarts(struct s3c2410_uartcfg *cfg, int no);

extern void s3c2412_init_clocks(int xtal);

extern  int s3c2412_baseclk_add(void);

extern void s3c2412_restart(char mode, const char *cmd);
#else
#define s3c2412_init_clocks NULL
#define s3c2412_init_uarts NULL
#define s3c2412_map_io NULL
#define s3c2412_init NULL
#define s3c2412_restart NULL
#endif
