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
#include <beep/export.h>
#include <beep/mfd/tmio.h>

int tmio_core_mmc_enable(void __iomem *cnf, int shift, unsigned long base)
{
	/* Enable the MMC/SD Control registers */
	sd_config_write16(cnf, shift, CNF_CMD, SDCREN);
	sd_config_write32(cnf, shift, CNF_CTL_BASE, base & 0xfffe);

	/* Disable SD power during suspend */
	sd_config_write8(cnf, shift, CNF_PWR_CTL_3, 0x01);

	/* The below is required but why? FIXME */
	sd_config_write8(cnf, shift, CNF_STOP_CLK_CTL, 0x1f);

	/* Power down SD bus */
	sd_config_write8(cnf, shift, CNF_PWR_CTL_2, 0x00);

	return 0;
}
EXPORT_SYMBOL(tmio_core_mmc_enable);

int tmio_core_mmc_resume(void __iomem *cnf, int shift, unsigned long base)
{

	/* Enable the MMC/SD Control registers */
	sd_config_write16(cnf, shift, CNF_CMD, SDCREN);
	sd_config_write32(cnf, shift, CNF_CTL_BASE, base & 0xfffe);

	return 0;
}
EXPORT_SYMBOL(tmio_core_mmc_resume);

void tmio_core_mmc_pwr(void __iomem *cnf, int shift, int state)
{
	sd_config_write8(cnf, shift, CNF_PWR_CTL_2, state ? 0x02 : 0x00);
}
EXPORT_SYMBOL(tmio_core_mmc_pwr);

void tmio_core_mmc_clk_div(void __iomem *cnf, int shift, int state)
{
	sd_config_write8(cnf, shift, CNF_SD_CLK_MODE, state ? 1 : 0);
}
EXPORT_SYMBOL(tmio_core_mmc_clk_div);

