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
/**
 * /sys/bus/iio/devices/.../out_altvoltageX_frequencyY
 */

#define IIO_DEV_ATTR_FREQ(_channel, _num, _mode, _show, _store, _addr)	\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_frequency##_num,	\
			_mode, _show, _store, _addr)

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_frequencyY_scale
 */

#define IIO_CONST_ATTR_FREQ_SCALE(_channel, _string)			\
	IIO_CONST_ATTR(out_altvoltage##_channel##_frequency_scale, _string)

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_frequencysymbol
 */

#define IIO_DEV_ATTR_FREQSYMBOL(_channel, _mode, _show, _store, _addr)	\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_frequencysymbol,	\
			_mode, _show, _store, _addr);

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_phaseY
 */

#define IIO_DEV_ATTR_PHASE(_channel, _num, _mode, _show, _store, _addr)	\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_phase##_num,		\
			_mode, _show, _store, _addr)

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_phaseY_scale
 */

#define IIO_CONST_ATTR_PHASE_SCALE(_channel, _string)			\
	IIO_CONST_ATTR(out_altvoltage##_channel##_phase_scale, _string)

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_phasesymbol
 */

#define IIO_DEV_ATTR_PHASESYMBOL(_channel, _mode, _show, _store, _addr)	\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_phasesymbol,		\
			_mode, _show, _store, _addr);

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_pincontrol_en
 */

#define IIO_DEV_ATTR_PINCONTROL_EN(_channel, _mode, _show, _store, _addr)\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_pincontrol_en,	\
			_mode, _show, _store, _addr);

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_pincontrol_frequency_en
 */

#define IIO_DEV_ATTR_PINCONTROL_FREQ_EN(_channel, _mode, _show, _store, _addr)\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_pincontrol_frequency_en,\
			_mode, _show, _store, _addr);

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_pincontrol_phase_en
 */

#define IIO_DEV_ATTR_PINCONTROL_PHASE_EN(_channel, _mode, _show, _store, _addr)\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_pincontrol_phase_en,	\
			_mode, _show, _store, _addr);

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_out_enable
 */

#define IIO_DEV_ATTR_OUT_ENABLE(_channel, _mode, _show, _store, _addr)	\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_out_enable,		\
			_mode, _show, _store, _addr);

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_outY_enable
 */

#define IIO_DEV_ATTR_OUTY_ENABLE(_channel, _output,			\
			_mode, _show, _store, _addr)			\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_out##_output##_enable,\
			_mode, _show, _store, _addr);

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_outY_wavetype
 */

#define IIO_DEV_ATTR_OUT_WAVETYPE(_channel, _output, _store, _addr)	\
	IIO_DEVICE_ATTR(out_altvoltage##_channel##_out##_output##_wavetype,\
			S_IWUSR, NULL, _store, _addr);

/**
 * /sys/bus/iio/devices/.../out_altvoltageX_outY_wavetype_available
 */

#define IIO_CONST_ATTR_OUT_WAVETYPES_AVAILABLE(_channel, _output, _modes)\
	IIO_CONST_ATTR(							\
	out_altvoltage##_channel##_out##_output##_wavetype_available, _modes);
