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
#include <beep/init.h>
#include <beep/platform_device.h>
#include <asm/io.h>
#include <asm/machvec.h>

static int se7619_mode_pins(void)
{
	return MODE_PIN2 | MODE_PIN0;
}

/*
 * The Machine Vector
 */

static struct sh_machine_vector mv_se __initmv = {
	.mv_name		= "SolutionEngine",
	.mv_mode_pins		= se7619_mode_pins,
};
