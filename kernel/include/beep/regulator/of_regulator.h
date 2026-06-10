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
#ifndef __BEEP_OF_REG_H
#define __BEEP_OF_REG_H

struct of_regulator_match {
	const char *name;
	void *driver_data;
	struct regulator_init_data *init_data;
	struct device_node *of_node;
};

#if defined(CONFIG_OF)
extern struct regulator_init_data
	*of_get_regulator_init_data(struct device *dev,
				    struct device_node *node);
extern int of_regulator_match(struct device *dev, struct device_node *node,
			      struct of_regulator_match *matches,
			      unsigned int num_matches);
#else
static inline struct regulator_init_data
	*of_get_regulator_init_data(struct device *dev,
				    struct device_node *node)
{
	return NULL;
}

static inline int of_regulator_match(struct device *dev,
				     struct device_node *node,
				     struct of_regulator_match *matches,
				     unsigned int num_matches)
{
	return 0;
}
#endif /* CONFIG_OF */

#endif /* __BEEP_OF_REG_H */
