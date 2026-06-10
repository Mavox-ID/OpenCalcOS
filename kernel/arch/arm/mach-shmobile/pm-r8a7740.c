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
#include <beep/console.h>
#include <mach/pm-rmobile.h>

#ifdef CONFIG_PM
static int r8a7740_pd_a4s_suspend(void)
{
	/*
	 * The A4S domain contains the CPU core and therefore it should
	 * only be turned off if the CPU is in use.
	 */
	return -EBUSY;
}

static int r8a7740_pd_a3sp_suspend(void)
{
	/*
	 * Serial consoles make use of SCIF hardware located in A3SP,
	 * keep such power domain on if "no_console_suspend" is set.
	 */
	return console_suspend_enabled ? 0 : -EBUSY;
}

static struct rmobile_pm_domain r8a7740_pm_domains[] = {
	{
		.genpd.name	= "A4S",
		.bit_shift	= 10,
		.gov		= &pm_domain_always_on_gov,
		.no_debug	= true,
		.suspend	= r8a7740_pd_a4s_suspend,
	},
	{
		.genpd.name	= "A3SP",
		.bit_shift	= 11,
		.gov		= &pm_domain_always_on_gov,
		.no_debug	= true,
		.suspend	= r8a7740_pd_a3sp_suspend,
	},
	{
		.genpd.name	= "A4LC",
		.bit_shift	= 1,
	},
};

void __init r8a7740_init_pm_domains(void)
{
	rmobile_init_domains(r8a7740_pm_domains, ARRAY_SIZE(r8a7740_pm_domains));
	pm_genpd_add_subdomain_names("A4S", "A3SP");
}

#endif /* CONFIG_PM */
