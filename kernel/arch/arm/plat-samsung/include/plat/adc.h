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
#ifndef __ASM_PLAT_ADC_H
#define __ASM_PLAT_ADC_H __FILE__

struct s3c_adc_client;

extern int s3c_adc_start(struct s3c_adc_client *client,
			 unsigned int channel, unsigned int nr_samples);

extern int s3c_adc_read(struct s3c_adc_client *client, unsigned int ch);

extern struct s3c_adc_client *
	s3c_adc_register(struct platform_device *pdev,
			 void (*select)(struct s3c_adc_client *client,
					unsigned selected),
			 void (*conv)(struct s3c_adc_client *client,
				      unsigned d0, unsigned d1,
				      unsigned *samples_left),
			 unsigned int is_ts);

extern void s3c_adc_release(struct s3c_adc_client *client);

#endif /* __ASM_PLAT_ADC_H */
