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
#define AM35XX_DEFAULT_MDIO_FREQUENCY	1000000

#if defined(CONFIG_TI_DAVINCI_EMAC) || defined(CONFIG_TI_DAVINCI_EMAC_MODULE)
void am35xx_emac_init(unsigned long mdio_bus_freq, u8 rmii_en);
#else
static inline void am35xx_emac_init(unsigned long mdio_bus_freq, u8 rmii_en) {}
#endif
