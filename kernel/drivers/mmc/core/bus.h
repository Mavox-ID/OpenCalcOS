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
#ifndef _MMC_CORE_BUS_H
#define _MMC_CORE_BUS_H

#define MMC_DEV_ATTR(name, fmt, args...)					\
static ssize_t mmc_##name##_show (struct device *dev, struct device_attribute *attr, char *buf)	\
{										\
	struct mmc_card *card = mmc_dev_to_card(dev);				\
	return sprintf(buf, fmt, args);						\
}										\
static DEVICE_ATTR(name, S_IRUGO, mmc_##name##_show, NULL)

struct mmc_card *mmc_alloc_card(struct mmc_host *host,
	struct device_type *type);
int mmc_add_card(struct mmc_card *card);
void mmc_remove_card(struct mmc_card *card);

int mmc_register_bus(void);
void mmc_unregister_bus(void);

#endif

