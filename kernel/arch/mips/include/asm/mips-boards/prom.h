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
#ifndef _MIPS_PROM_H
#define _MIPS_PROM_H

extern char *prom_getcmdline(void);
extern char *prom_getenv(char *name);
extern void prom_init_cmdline(void);
extern void prom_meminit(void);
extern void prom_fixup_mem_map(unsigned long start_mem, unsigned long end_mem);
extern void mips_display_message(const char *str);
extern void mips_display_word(unsigned int num);
extern void mips_scroll_message(void);
extern int get_ethernet_addr(char *ethernet_addr);

/* Memory descriptor management. */
#define PROM_MAX_PMEMBLOCKS    32
struct prom_pmemblock {
        unsigned long base; /* Within KSEG0. */
        unsigned int size;  /* In bytes. */
        unsigned int type;  /* free or prom memory */
};

#endif /* !(_MIPS_PROM_H) */
