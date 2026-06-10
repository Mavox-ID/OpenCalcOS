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
#define IOTABLE_ENTRY(t) \
	{ \
		.virtual	= NSPIRE_##t##_VIRT_BASE, \
		.pfn		= __phys_to_pfn(NSPIRE_##t##_PHYS_BASE), \
		.length		= NSPIRE_##t##_SIZE, \
		.type		= MT_DEVICE \
	}

#define RESOURCE_ENTRY_IRQ(t) \
	{ \
		.start	= NSPIRE_IRQ_##t, \
		.end	= NSPIRE_IRQ_##t, \
		.flags	= IORESOURCE_IRQ \
	}

#define RESOURCE_ENTRY_MEM(t) \
	{ \
		.start	= NSPIRE_##t##_PHYS_BASE, \
		.end	= NSPIRE_##t##_PHYS_BASE + NSPIRE_##t##_SIZE - 1, \
		.flags	= IORESOURCE_MEM \
	}

extern struct platform_device nspire_keypad_device;
extern struct platform_device nspire_cxusbhost_device;

extern struct nspire_keypad_data nspire_keypad_data;

void __init nspire_map_io(void);
void __init nspire_init_early(void);
void __init nspire_init(void);
void __init nspire_init_late(void);

void nspire_restart(char mode, const char *cmd);

int nspire_clcd_mmap(struct clcd_fb *fb, struct vm_area_struct *vma);
void nspire_clcd_remove(struct clcd_fb *fb);
int nspire_clcd_setup(struct clcd_fb *fb, unsigned panel_size,
	struct clcd_panel * panel);
