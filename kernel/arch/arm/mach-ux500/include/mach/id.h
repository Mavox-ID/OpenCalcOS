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
#ifndef __MACH_UX500_ID
#define __MACH_UX500_ID

/**
 * struct dbx500_asic_id - fields of the ASIC ID
 * @process: the manufacturing process, 0x40 is 40 nm 0x00 is "standard"
 * @partnumber: hithereto 0x8500 for DB8500
 * @revision: version code in the series
 */
struct dbx500_asic_id {
	u16	partnumber;
	u8	revision;
	u8	process;
};

extern struct dbx500_asic_id dbx500_id;

static inline unsigned int __attribute_const__ dbx500_partnumber(void)
{
	return dbx500_id.partnumber;
}

static inline unsigned int __attribute_const__ dbx500_revision(void)
{
	return dbx500_id.revision;
}

/*
 * SOCs
 */

static inline bool __attribute_const__ cpu_is_u8500(void)
{
	return dbx500_partnumber() == 0x8500;
}

static inline bool __attribute_const__ cpu_is_u8520(void)
{
	return dbx500_partnumber() == 0x8520;
}

static inline bool cpu_is_u8500_family(void)
{
	return cpu_is_u8500() || cpu_is_u8520();
}

static inline bool __attribute_const__ cpu_is_u9540(void)
{
	return dbx500_partnumber() == 0x9540;
}

static inline bool __attribute_const__ cpu_is_u8540(void)
{
	return dbx500_partnumber() == 0x8540;
}

static inline bool cpu_is_ux540_family(void)
{
	return cpu_is_u9540() || cpu_is_u8540();
}

/*
 * 8500 revisions
 */

static inline bool __attribute_const__ cpu_is_u8500ed(void)
{
	return cpu_is_u8500() && dbx500_revision() == 0x00;
}

static inline bool __attribute_const__ cpu_is_u8500v1(void)
{
	return cpu_is_u8500() && (dbx500_revision() & 0xf0) == 0xA0;
}

static inline bool __attribute_const__ cpu_is_u8500v10(void)
{
	return cpu_is_u8500() && dbx500_revision() == 0xA0;
}

static inline bool __attribute_const__ cpu_is_u8500v11(void)
{
	return cpu_is_u8500() && dbx500_revision() == 0xA1;
}

static inline bool __attribute_const__ cpu_is_u8500v2(void)
{
	return cpu_is_u8500() && ((dbx500_revision() & 0xf0) == 0xB0);
}

static inline bool cpu_is_u8500v20(void)
{
	return cpu_is_u8500() && (dbx500_revision() == 0xB0);
}

static inline bool cpu_is_u8500v21(void)
{
	return cpu_is_u8500() && (dbx500_revision() == 0xB1);
}

static inline bool cpu_is_u8500v22(void)
{
	return cpu_is_u8500() && (dbx500_revision() == 0xB2);
}

static inline bool cpu_is_u8500v20_or_later(void)
{
	return (cpu_is_u8500() && !cpu_is_u8500v10() && !cpu_is_u8500v11());
}

static inline bool ux500_is_svp(void)
{
	return false;
}

#define ux500_unknown_soc()	BUG()

#endif
