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
/*
 * Some address definitions for the Watchdog
 */
#define SP5100_WDT_MEM_MAP_SIZE		0x08
#define SP5100_WDT_CONTROL(base)	((base) + 0x00) /* Watchdog Control */
#define SP5100_WDT_COUNT(base)		((base) + 0x04) /* Watchdog Count */

#define SP5100_WDT_START_STOP_BIT	(1 << 0)
#define SP5100_WDT_TRIGGER_BIT		(1 << 7)

#define SP5100_PM_IOPORTS_SIZE		0x02

/*
 * These two IO registers are hardcoded and there doesn't seem to be a way to
 * read them from a register.
 */

/*  For SP5100/SB7x0 chipset */
#define SP5100_IO_PM_INDEX_REG		0xCD6
#define SP5100_IO_PM_DATA_REG		0xCD7

#define SP5100_SB_RESOURCE_MMIO_BASE	0x9C

#define SP5100_PM_WATCHDOG_CONTROL	0x69
#define SP5100_PM_WATCHDOG_BASE		0x6C

#define SP5100_PM_WATCHDOG_FIRED	(1 << 1)
#define SP5100_PM_WATCHDOG_ACTION_RESET	(1 << 2)

#define SP5100_PCI_WATCHDOG_MISC_REG	0x41
#define SP5100_PCI_WATCHDOG_DECODE_EN	(1 << 3)

#define SP5100_PM_WATCHDOG_DISABLE	(1 << 0)
#define SP5100_PM_WATCHDOG_SECOND_RES	(3 << 1)

#define SP5100_DEVNAME			"SP5100 TCO"


/*  For SB8x0(or later) chipset */
#define SB800_IO_PM_INDEX_REG		0xCD6
#define SB800_IO_PM_DATA_REG		0xCD7

#define SB800_PM_ACPI_MMIO_EN		0x24
#define SB800_PM_WATCHDOG_CONTROL	0x48
#define SB800_PM_WATCHDOG_BASE		0x48
#define SB800_PM_WATCHDOG_CONFIG	0x4C

#define SB800_PCI_WATCHDOG_DECODE_EN	(1 << 0)
#define SB800_PM_WATCHDOG_DISABLE	(1 << 2)
#define SB800_PM_WATCHDOG_SECOND_RES	(3 << 0)
#define SB800_ACPI_MMIO_DECODE_EN	(1 << 0)
#define SB800_ACPI_MMIO_SEL		(1 << 2)


#define SB800_PM_WDT_MMIO_OFFSET	0xB00

#define SB800_DEVNAME			"SB800 TCO"
