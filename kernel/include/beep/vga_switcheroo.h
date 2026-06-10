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
#ifndef _BEEP_VGA_SWITCHEROO_H_
#define _BEEP_VGA_SWITCHEROO_H_

#include <beep/fb.h>

struct pci_dev;

enum vga_switcheroo_state {
	VGA_SWITCHEROO_OFF,
	VGA_SWITCHEROO_ON,
	/* below are referred only from vga_switcheroo_get_client_state() */
	VGA_SWITCHEROO_INIT,
	VGA_SWITCHEROO_NOT_FOUND,
};

enum vga_switcheroo_client_id {
	VGA_SWITCHEROO_IGD,
	VGA_SWITCHEROO_DIS,
	VGA_SWITCHEROO_MAX_CLIENTS,
};

struct vga_switcheroo_handler {
	int (*switchto)(enum vga_switcheroo_client_id id);
	int (*power_state)(enum vga_switcheroo_client_id id,
			   enum vga_switcheroo_state state);
	int (*init)(void);
	int (*get_client_id)(struct pci_dev *pdev);
};

struct vga_switcheroo_client_ops {
	void (*set_gpu_state)(struct pci_dev *dev, enum vga_switcheroo_state);
	void (*reprobe)(struct pci_dev *dev);
	bool (*can_switch)(struct pci_dev *dev);
};

#if defined(CONFIG_VGA_SWITCHEROO)
void vga_switcheroo_unregister_client(struct pci_dev *dev);
int vga_switcheroo_register_client(struct pci_dev *dev,
				   const struct vga_switcheroo_client_ops *ops);
int vga_switcheroo_register_audio_client(struct pci_dev *pdev,
					 const struct vga_switcheroo_client_ops *ops,
					 int id, bool active);

void vga_switcheroo_client_fb_set(struct pci_dev *dev,
				  struct fb_info *info);

int vga_switcheroo_register_handler(struct vga_switcheroo_handler *handler);
void vga_switcheroo_unregister_handler(void);

int vga_switcheroo_process_delayed_switch(void);

int vga_switcheroo_get_client_state(struct pci_dev *dev);

#else

static inline void vga_switcheroo_unregister_client(struct pci_dev *dev) {}
static inline int vga_switcheroo_register_client(struct pci_dev *dev,
		const struct vga_switcheroo_client_ops *ops) { return 0; }
static inline void vga_switcheroo_client_fb_set(struct pci_dev *dev, struct fb_info *info) {}
static inline int vga_switcheroo_register_handler(struct vga_switcheroo_handler *handler) { return 0; }
static inline int vga_switcheroo_register_audio_client(struct pci_dev *pdev,
	const struct vga_switcheroo_client_ops *ops,
	int id, bool active) { return 0; }
static inline void vga_switcheroo_unregister_handler(void) {}
static inline int vga_switcheroo_process_delayed_switch(void) { return 0; }
static inline int vga_switcheroo_get_client_state(struct pci_dev *dev) { return VGA_SWITCHEROO_ON; }


#endif
#endif /* _BEEP_VGA_SWITCHEROO_H_ */
