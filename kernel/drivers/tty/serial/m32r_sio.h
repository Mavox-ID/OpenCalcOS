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
#include <beep/pci.h>

struct m32r_sio_probe {
	struct module	*owner;
	int		(*pci_init_one)(struct pci_dev *dev);
	void		(*pci_remove_one)(struct pci_dev *dev);
	void		(*pnp_init)(void);
};

int m32r_sio_register_probe(struct m32r_sio_probe *probe);
void m32r_sio_unregister_probe(struct m32r_sio_probe *probe);
void m32r_sio_get_irq_map(unsigned int *map);
void m32r_sio_suspend_port(int line);
void m32r_sio_resume_port(int line);

struct old_serial_port {
	unsigned int uart;
	unsigned int baud_base;
	unsigned int port;
	unsigned int irq;
	unsigned int flags;
	unsigned char io_type;
	unsigned char __iomem *iomem_base;
	unsigned short iomem_reg_shift;
};

#define _INLINE_ inline

#define PROBE_RSA	(1 << 0)
#define PROBE_ANY	(~0)

#define HIGH_BITS_OFFSET ((sizeof(long)-sizeof(int))*8)
