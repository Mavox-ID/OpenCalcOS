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
#include <beep/types.h>
#include <beep/jiffies.h>
#include <beep/timer.h>
#include <beep/module.h>

#include <asm/amigayle.h>
#include <asm/amipcmcia.h>

/* gayle config byte for program voltage and access speed */
static unsigned char cfg_byte = GAYLE_CFG_0V|GAYLE_CFG_150NS;

void pcmcia_reset(void)
{
	unsigned long reset_start_time = jiffies;
	unsigned char b;

	gayle_reset = 0x00;
	while (time_before(jiffies, reset_start_time + 1*HZ/100));
	b = gayle_reset;
}
EXPORT_SYMBOL(pcmcia_reset);


/* copy a tuple, including tuple header. return nb bytes copied */
/* be careful as this may trigger a GAYLE_IRQ_WR interrupt ! */

int pcmcia_copy_tuple(unsigned char tuple_id, void *tuple, int max_len)
{
	unsigned char id, *dest;
	int cnt, pos, len;

	dest = tuple;
	pos = 0;

	id = gayle_attribute[pos];

	while((id != CISTPL_END) && (pos < 0x10000)) {
		len = (int)gayle_attribute[pos+2] + 2;
		if (id == tuple_id) {
			len = (len > max_len)?max_len:len;
			for (cnt = 0; cnt < len; cnt++) {
				*dest++ = gayle_attribute[pos+(cnt<<1)];
			}

			return len;
		}
		pos += len<<1;
		id = gayle_attribute[pos];
	}

	return 0;
}
EXPORT_SYMBOL(pcmcia_copy_tuple);

void pcmcia_program_voltage(int voltage)
{
	unsigned char v;

	switch (voltage) {
	case PCMCIA_0V:
		v = GAYLE_CFG_0V;
		break;
	case PCMCIA_5V:
		v = GAYLE_CFG_5V;
		break;
	case PCMCIA_12V:
		v = GAYLE_CFG_12V;
		break;
	default:
		v = GAYLE_CFG_0V;
	}

	cfg_byte = (cfg_byte & 0xfc) | v;
	gayle.config = cfg_byte;

}
EXPORT_SYMBOL(pcmcia_program_voltage);

void pcmcia_access_speed(int speed)
{
	unsigned char s;

	if (speed <= PCMCIA_SPEED_100NS)
		s = GAYLE_CFG_100NS;
	else if (speed <= PCMCIA_SPEED_150NS)
		s = GAYLE_CFG_150NS;
	else if (speed <= PCMCIA_SPEED_250NS)
		s = GAYLE_CFG_250NS;
	else
		s = GAYLE_CFG_720NS;

	cfg_byte = (cfg_byte & 0xf3) | s;
	gayle.config = cfg_byte;
}
EXPORT_SYMBOL(pcmcia_access_speed);

void pcmcia_write_enable(void)
{
	gayle.cardstatus = GAYLE_CS_WR|GAYLE_CS_DA;
}
EXPORT_SYMBOL(pcmcia_write_enable);

void pcmcia_write_disable(void)
{
	gayle.cardstatus = 0;
}
EXPORT_SYMBOL(pcmcia_write_disable);

