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
struct nsc_gpio_ops {
	struct module*	owner;
	u32	(*gpio_config)	(unsigned iminor, u32 mask, u32 bits);
	void	(*gpio_dump)	(struct nsc_gpio_ops *amp, unsigned iminor);
	int	(*gpio_get)	(unsigned iminor);
	void	(*gpio_set)	(unsigned iminor, int state);
	void	(*gpio_change)	(unsigned iminor);
	int	(*gpio_current)	(unsigned iminor);
	struct device*	dev;	/* for dev_dbg() support, set in init  */
};

extern ssize_t nsc_gpio_write(struct file *file, const char __user *data,
			      size_t len, loff_t *ppos);

extern ssize_t nsc_gpio_read(struct file *file, char __user *buf,
			     size_t len, loff_t *ppos);

extern void nsc_gpio_dump(struct nsc_gpio_ops *amp, unsigned index);

