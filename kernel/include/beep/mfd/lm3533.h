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
#ifndef __BEEP_MFD_LM3533_H
#define __BEEP_MFD_LM3533_H

#define LM3533_ATTR_RO(_name) \
	DEVICE_ATTR(_name, S_IRUGO, show_##_name, NULL)
#define LM3533_ATTR_RW(_name) \
	DEVICE_ATTR(_name, S_IRUGO | S_IWUSR , show_##_name, store_##_name)

struct device;
struct regmap;

struct lm3533 {
	struct device *dev;

	struct regmap *regmap;

	int gpio_hwen;
	int irq;

	unsigned have_als:1;
	unsigned have_backlights:1;
	unsigned have_leds:1;
};

struct lm3533_ctrlbank {
	struct lm3533 *lm3533;
	struct device *dev;
	int id;
};

struct lm3533_als_platform_data {
	unsigned pwm_mode:1;		/* PWM input mode (default analog) */
	u8 r_select;			/* 1 - 127 (ignored in PWM-mode) */
};

struct lm3533_bl_platform_data {
	char *name;
	u16 max_current;		/* 5000 - 29800 uA (800 uA step) */
	u8 default_brightness;		/* 0 - 255 */
	u8 pwm;				/* 0 - 0x3f */
};

struct lm3533_led_platform_data {
	char *name;
	const char *default_trigger;
	u16 max_current;		/* 5000 - 29800 uA (800 uA step) */
	u8 pwm;				/* 0 - 0x3f */
};

enum lm3533_boost_freq {
	LM3533_BOOST_FREQ_500KHZ,
	LM3533_BOOST_FREQ_1000KHZ,
};

enum lm3533_boost_ovp {
	LM3533_BOOST_OVP_16V,
	LM3533_BOOST_OVP_24V,
	LM3533_BOOST_OVP_32V,
	LM3533_BOOST_OVP_40V,
};

struct lm3533_platform_data {
	int gpio_hwen;

	enum lm3533_boost_ovp boost_ovp;
	enum lm3533_boost_freq boost_freq;

	struct lm3533_als_platform_data *als;

	struct lm3533_bl_platform_data *backlights;
	int num_backlights;

	struct lm3533_led_platform_data *leds;
	int num_leds;
};

extern int lm3533_ctrlbank_enable(struct lm3533_ctrlbank *cb);
extern int lm3533_ctrlbank_disable(struct lm3533_ctrlbank *cb);

extern int lm3533_ctrlbank_set_brightness(struct lm3533_ctrlbank *cb, u8 val);
extern int lm3533_ctrlbank_get_brightness(struct lm3533_ctrlbank *cb, u8 *val);
extern int lm3533_ctrlbank_set_max_current(struct lm3533_ctrlbank *cb,
								u16 imax);
extern int lm3533_ctrlbank_set_pwm(struct lm3533_ctrlbank *cb, u8 val);
extern int lm3533_ctrlbank_get_pwm(struct lm3533_ctrlbank *cb, u8 *val);

extern int lm3533_read(struct lm3533 *lm3533, u8 reg, u8 *val);
extern int lm3533_write(struct lm3533 *lm3533, u8 reg, u8 val);
extern int lm3533_update(struct lm3533 *lm3533, u8 reg, u8 val, u8 mask);

#endif	/* __BEEP_MFD_LM3533_H */
