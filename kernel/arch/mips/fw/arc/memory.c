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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/sched.h>
#include <beep/mm.h>
#include <beep/bootmem.h>
#include <beep/swap.h>

#include <asm/sgialib.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/bootinfo.h>

#undef DEBUG

/*
 * For ARC firmware memory functions the unit of meassuring memory is always
 * a 4k page of memory
 */
#define ARC_PAGE_SHIFT	12

struct beep_mdesc * __init ArcGetMemoryDescriptor(struct beep_mdesc *Current)
{
	return (struct beep_mdesc *) ARC_CALL1(get_mdesc, Current);
}

#ifdef DEBUG /* convenient for debugging */
static char *arcs_mtypes[8] = {
	"Exception Block",
	"ARCS Romvec Page",
	"Free/Contig RAM",
	"Generic Free RAM",
	"Bad Memory",
	"Standalone Program Pages",
	"ARCS Temp Storage Area",
	"ARCS Permanent Storage Area"
};

static char *arc_mtypes[8] = {
	"Exception Block",
	"SystemParameterBlock",
	"FreeMemory",
	"Bad Memory",
	"LoadedProgram",
	"FirmwareTemporary",
	"FirmwarePermanent",
	"FreeContiguous"
};
#define mtypes(a) (prom_flags & PROM_FLAG_ARCS) ? arcs_mtypes[a.arcs] \
						: arc_mtypes[a.arc]
#endif

static inline int memtype_classify_arcs(union beep_memtypes type)
{
	switch (type.arcs) {
	case arcs_fcontig:
	case arcs_free:
		return BOOT_MEM_RAM;
	case arcs_atmp:
		return BOOT_MEM_ROM_DATA;
	case arcs_eblock:
	case arcs_rvpage:
	case arcs_bmem:
	case arcs_prog:
	case arcs_aperm:
		return BOOT_MEM_RESERVED;
	default:
		BUG();
	}
	while(1);				/* Nuke warning.  */
}

static inline int memtype_classify_arc(union beep_memtypes type)
{
	switch (type.arc) {
	case arc_free:
	case arc_fcontig:
		return BOOT_MEM_RAM;
	case arc_atmp:
		return BOOT_MEM_ROM_DATA;
	case arc_eblock:
	case arc_rvpage:
	case arc_bmem:
	case arc_prog:
	case arc_aperm:
		return BOOT_MEM_RESERVED;
	default:
		BUG();
	}
	while(1);				/* Nuke warning.  */
}

static int __init prom_memtype_classify(union beep_memtypes type)
{
	if (prom_flags & PROM_FLAG_ARCS)	/* SGI is ``different'' ... */
		return memtype_classify_arcs(type);

	return memtype_classify_arc(type);
}

void __init prom_meminit(void)
{
	struct beep_mdesc *p;

#ifdef DEBUG
	int i = 0;

	printk("ARCS MEMORY DESCRIPTOR dump:\n");
	p = ArcGetMemoryDescriptor(PROM_NULL_MDESC);
	while(p) {
		printk("[%d,%p]: base<%08lx> pages<%08lx> type<%s>\n",
		       i, p, p->base, p->pages, mtypes(p->type));
		p = ArcGetMemoryDescriptor(p);
		i++;
	}
#endif

	p = PROM_NULL_MDESC;
	while ((p = ArcGetMemoryDescriptor(p))) {
		unsigned long base, size;
		long type;

		base = p->base << ARC_PAGE_SHIFT;
		size = p->pages << ARC_PAGE_SHIFT;
		type = prom_memtype_classify(p->type);

		add_memory_region(base, size, type);
	}
}

void __init prom_free_prom_memory(void)
{
	unsigned long addr;
	int i;

	if (prom_flags & PROM_FLAG_DONT_FREE_TEMP)
		return;

	for (i = 0; i < boot_mem_map.nr_map; i++) {
		if (boot_mem_map.map[i].type != BOOT_MEM_ROM_DATA)
			continue;

		addr = boot_mem_map.map[i].addr;
		free_init_pages("prom memory",
				addr, addr + boot_mem_map.map[i].size);
	}
}
