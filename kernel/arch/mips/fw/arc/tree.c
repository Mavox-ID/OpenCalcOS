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
#include <asm/fw/arc/types.h>
#include <asm/sgialib.h>

#undef DEBUG_PROM_TREE

pcomponent * __init
ArcGetPeer(pcomponent *Current)
{
	if (Current == PROM_NULL_COMPONENT)
		return PROM_NULL_COMPONENT;

	return (pcomponent *) ARC_CALL1(next_component, Current);
}

pcomponent * __init
ArcGetChild(pcomponent *Current)
{
	return (pcomponent *) ARC_CALL1(child_component, Current);
}

pcomponent * __init
ArcGetParent(pcomponent *Current)
{
	if (Current == PROM_NULL_COMPONENT)
		return PROM_NULL_COMPONENT;

	return (pcomponent *) ARC_CALL1(parent_component, Current);
}

LONG __init
ArcGetConfigurationData(VOID *Buffer, pcomponent *Current)
{
	return ARC_CALL2(component_data, Buffer, Current);
}

pcomponent * __init
ArcAddChild(pcomponent *Current, pcomponent *Template, VOID *ConfigurationData)
{
	return (pcomponent *)
	       ARC_CALL3(child_add, Current, Template, ConfigurationData);
}

LONG __init
ArcDeleteComponent(pcomponent *ComponentToDelete)
{
	return ARC_CALL1(comp_del, ComponentToDelete);
}

pcomponent * __init
ArcGetComponent(CHAR *Path)
{
	return (pcomponent *)ARC_CALL1(component_by_path, Path);
}

#ifdef DEBUG_PROM_TREE

static char *classes[] = {
	"system", "processor", "cache", "adapter", "controller", "peripheral",
	"memory"
};

static char *types[] = {
	"arc", "cpu", "fpu", "picache", "pdcache", "sicache", "sdcache",
	"sccache", "memdev", "eisa adapter", "tc adapter", "scsi adapter",
	"dti adapter", "multi-func adapter", "disk controller",
	"tp controller", "cdrom controller", "worm controller",
	"serial controller", "net controller", "display controller",
	"parallel controller", "pointer controller", "keyboard controller",
	"audio controller", "misc controller", "disk peripheral",
	"floppy peripheral", "tp peripheral", "modem peripheral",
	"monitor peripheral", "printer peripheral", "pointer peripheral",
	"keyboard peripheral", "terminal peripheral", "line peripheral",
	"net peripheral", "misc peripheral", "anonymous"
};

static char *iflags[] = {
	"bogus", "read only", "removable", "console in", "console out",
	"input", "output"
};

static void __init
dump_component(pcomponent *p)
{
	printk("[%p]:class<%s>type<%s>flags<%s>ver<%d>rev<%d>",
	       p, classes[p->class], types[p->type],
	       iflags[p->iflags], p->vers, p->rev);
	printk("key<%08lx>\n\tamask<%08lx>cdsize<%d>ilen<%d>iname<%s>\n",
	       p->key, p->amask, (int)p->cdsize, (int)p->ilen, p->iname);
}

static void __init
traverse(pcomponent *p, int op)
{
	dump_component(p);
	if(ArcGetChild(p))
		traverse(ArcGetChild(p), 1);
	if(ArcGetPeer(p) && op)
		traverse(ArcGetPeer(p), 1);
}

void __init
prom_testtree(void)
{
	pcomponent *p;

	p = ArcGetChild(PROM_NULL_COMPONENT);
	dump_component(p);
	p = ArcGetChild(p);
	while(p) {
		dump_component(p);
		p = ArcGetPeer(p);
	}
}

#endif /* DEBUG_PROM_TREE  */
