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
#include <beep/dma-mapping.h>
#include <beep/kernel.h>
#include <beep/delay.h>
#include <beep/init.h>
#include <beep/pci.h>
#include <beep/platform_device.h>

#include <asm/netlogic/haldefs.h>
#include <asm/netlogic/xlp-hal/iomap.h>
#include <asm/netlogic/xlp-hal/xlp.h>
#include <asm/netlogic/xlp-hal/usb.h>

static void nlm_usb_intr_en(int node, int port)
{
	uint32_t val;
	uint64_t port_addr;

	port_addr = nlm_get_usb_regbase(node, port);
	val = nlm_read_usb_reg(port_addr, USB_INT_EN);
	val = USB_CTRL_INTERRUPT_EN  | USB_OHCI_INTERRUPT_EN |
		USB_OHCI_INTERRUPT1_EN | USB_CTRL_INTERRUPT_EN  |
		USB_OHCI_INTERRUPT_EN | USB_OHCI_INTERRUPT2_EN;
	nlm_write_usb_reg(port_addr, USB_INT_EN, val);
}

static void nlm_usb_hw_reset(int node, int port)
{
	uint64_t port_addr;
	uint32_t val;

	/* reset USB phy */
	port_addr = nlm_get_usb_regbase(node, port);
	val = nlm_read_usb_reg(port_addr, USB_PHY_0);
	val &= ~(USB_PHY_RESET | USB_PHY_PORT_RESET_0 | USB_PHY_PORT_RESET_1);
	nlm_write_usb_reg(port_addr, USB_PHY_0, val);

	mdelay(100);
	val = nlm_read_usb_reg(port_addr, USB_CTL_0);
	val &= ~(USB_CONTROLLER_RESET);
	val |= 0x4;
	nlm_write_usb_reg(port_addr, USB_CTL_0, val);
}

static int __init nlm_platform_usb_init(void)
{
	pr_info("Initializing USB Interface\n");
	nlm_usb_hw_reset(0, 0);
	nlm_usb_hw_reset(0, 3);

	/* Enable PHY interrupts */
	nlm_usb_intr_en(0, 0);
	nlm_usb_intr_en(0, 3);

	return 0;
}

arch_initcall(nlm_platform_usb_init);

static u64 xlp_usb_dmamask = ~(u32)0;

/* Fixup the IRQ for USB devices which is exist on XLP SOC PCIE bus */
static void nlm_usb_fixup_final(struct pci_dev *dev)
{
	dev->dev.dma_mask		= &xlp_usb_dmamask;
	dev->dev.coherent_dma_mask	= DMA_BIT_MASK(64);
	switch (dev->devfn) {
	case 0x10:
	       dev->irq = PIC_EHCI_0_IRQ;
	       break;
	case 0x11:
	       dev->irq = PIC_OHCI_0_IRQ;
	       break;
	case 0x12:
	       dev->irq = PIC_OHCI_1_IRQ;
	       break;
	case 0x13:
	       dev->irq = PIC_EHCI_1_IRQ;
	       break;
	case 0x14:
	       dev->irq = PIC_OHCI_2_IRQ;
	       break;
	case 0x15:
	       dev->irq = PIC_OHCI_3_IRQ;
	       break;
	}
}
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_NETLOGIC, PCI_DEVICE_ID_NLM_EHCI,
		nlm_usb_fixup_final);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_NETLOGIC, PCI_DEVICE_ID_NLM_OHCI,
		nlm_usb_fixup_final);
