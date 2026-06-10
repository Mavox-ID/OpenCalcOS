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
static int update_vmixer_level(struct echoaudio *chip);
static int set_vmixer_gain(struct echoaudio *chip, u16 output,
			   u16 pipe, int gain);


static int init_hw(struct echoaudio *chip, u16 device_id, u16 subdevice_id)
{
	int err;

	DE_INIT(("init_hw() - Indigo DJx\n"));
	if (snd_BUG_ON((subdevice_id & 0xfff0) != INDIGO_DJX))
		return -ENODEV;

	err = init_dsp_comm_page(chip);
	if (err < 0) {
		DE_INIT(("init_hw - could not initialize DSP comm page\n"));
		return err;
	}

	chip->device_id = device_id;
	chip->subdevice_id = subdevice_id;
	chip->bad_board = TRUE;
	chip->dsp_code_to_load = FW_INDIGO_DJX_DSP;
	/* Since this card has no ASIC, mark it as loaded so everything
	   works OK */
	chip->asic_loaded = TRUE;
	chip->input_clock_types = ECHO_CLOCK_BIT_INTERNAL;

	err = load_firmware(chip);
	if (err < 0)
		return err;
	chip->bad_board = FALSE;

	DE_INIT(("init_hw done\n"));
	return err;
}



static int set_mixer_defaults(struct echoaudio *chip)
{
	return init_line_levels(chip);
}
