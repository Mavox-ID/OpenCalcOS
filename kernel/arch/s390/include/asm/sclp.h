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
#ifndef _ASM_S390_SCLP_H
#define _ASM_S390_SCLP_H

#include <beep/types.h>
#include <asm/chpid.h>

#define SCLP_CHP_INFO_MASK_SIZE		32

struct sclp_chp_info {
	u8 recognized[SCLP_CHP_INFO_MASK_SIZE];
	u8 standby[SCLP_CHP_INFO_MASK_SIZE];
	u8 configured[SCLP_CHP_INFO_MASK_SIZE];
};

#define LOADPARM_LEN 8

struct sclp_ipl_info {
	int is_valid;
	int has_dump;
	char loadparm[LOADPARM_LEN];
};

struct sclp_cpu_entry {
	u8 address;
	u8 reserved0[13];
	u8 type;
	u8 reserved1;
} __attribute__((packed));

struct sclp_cpu_info {
	unsigned int configured;
	unsigned int standby;
	unsigned int combined;
	int has_cpu_type;
	struct sclp_cpu_entry cpu[255];
};

int sclp_get_cpu_info(struct sclp_cpu_info *info);
int sclp_cpu_configure(u8 cpu);
int sclp_cpu_deconfigure(u8 cpu);
void sclp_facilities_detect(void);
unsigned long long sclp_get_rnmax(void);
unsigned long long sclp_get_rzm(void);
u8 sclp_get_fac85(void);
int sclp_sdias_blk_count(void);
int sclp_sdias_copy(void *dest, int blk_num, int nr_blks);
int sclp_chp_configure(struct chp_id chpid);
int sclp_chp_deconfigure(struct chp_id chpid);
int sclp_chp_read_info(struct sclp_chp_info *info);
void sclp_get_ipl_info(struct sclp_ipl_info *info);
bool sclp_has_linemode(void);
bool sclp_has_vt220(void);
int sclp_pci_configure(u32 fid);
int sclp_pci_deconfigure(u32 fid);

#endif /* _ASM_S390_SCLP_H */
