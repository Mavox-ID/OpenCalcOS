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
#ifndef _AT91_ADC_H_
#define _AT91_ADC_H_

/**
 * struct at91_adc_reg_desc - Various informations relative to registers
 * @channel_base:	Base offset for the channel data registers
 * @drdy_mask:		Mask of the DRDY field in the relevant registers
			(Interruptions registers mostly)
 * @status_register:	Offset of the Interrupt Status Register
 * @trigger_register:	Offset of the Trigger setup register
 */
struct at91_adc_reg_desc {
	u8	channel_base;
	u32	drdy_mask;
	u8	status_register;
	u8	trigger_register;
};

/**
 * struct at91_adc_trigger - description of triggers
 * @name:		name of the trigger advertised to the user
 * @value:		value to set in the ADC's trigger setup register
			to enable the trigger
 * @is_external:	Does the trigger rely on an external pin?
 */
struct at91_adc_trigger {
	const char	*name;
	u8		value;
	bool		is_external;
};

/**
 * struct at91_adc_data - platform data for ADC driver
 * @channels_used:		channels in use on the board as a bitmask
 * @num_channels:		global number of channels available on the board
 * @registers:			Registers definition on the board
 * @startup_time:		startup time of the ADC in microseconds
 * @trigger_list:		Triggers available in the ADC
 * @trigger_number:		Number of triggers available in the ADC
 * @use_external_triggers:	does the board has external triggers availables
 * @vref:			Reference voltage for the ADC in millivolts
 */
struct at91_adc_data {
	unsigned long			channels_used;
	u8				num_channels;
	struct at91_adc_reg_desc	*registers;
	u8				startup_time;
	struct at91_adc_trigger		*trigger_list;
	u8				trigger_number;
	bool				use_external_triggers;
	u16				vref;
};

extern void __init at91_add_device_adc(struct at91_adc_data *data);
#endif
