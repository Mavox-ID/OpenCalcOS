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
#ifndef IIO_ADC_AD7606_H_
#define IIO_ADC_AD7606_H_

/*
 * TODO: struct ad7606_platform_data needs to go into include/beep/iio
 */

/**
 * struct ad7606_platform_data - platform/board specifc information
 * @default_os:		default oversampling value {0, 2, 4, 8, 16, 32, 64}
 * @default_range:	default range +/-{5000, 10000} mVolt
 * @gpio_convst:	number of gpio connected to the CONVST pin
 * @gpio_reset:		gpio connected to the RESET pin, if not used set to -1
 * @gpio_range:		gpio connected to the RANGE pin, if not used set to -1
 * @gpio_os0:		gpio connected to the OS0 pin, if not used set to -1
 * @gpio_os1:		gpio connected to the OS1 pin, if not used set to -1
 * @gpio_os2:		gpio connected to the OS2 pin, if not used set to -1
 * @gpio_frstdata:	gpio connected to the FRSTDAT pin, if not used set to -1
 * @gpio_stby:		gpio connected to the STBY pin, if not used set to -1
 */

struct ad7606_platform_data {
	unsigned			default_os;
	unsigned			default_range;
	unsigned			gpio_convst;
	unsigned			gpio_reset;
	unsigned			gpio_range;
	unsigned			gpio_os0;
	unsigned			gpio_os1;
	unsigned			gpio_os2;
	unsigned			gpio_frstdata;
	unsigned			gpio_stby;
};

/**
 * struct ad7606_chip_info - chip specifc information
 * @name:		indentification string for chip
 * @int_vref_mv:	the internal reference voltage
 * @channels:		channel specification
 * @num_channels:	number of channels
 */

struct ad7606_chip_info {
	const char			*name;
	u16				int_vref_mv;
	const struct iio_chan_spec	*channels;
	unsigned			num_channels;
};

/**
 * struct ad7606_state - driver instance specific data
 */

struct ad7606_state {
	struct device			*dev;
	const struct ad7606_chip_info	*chip_info;
	struct ad7606_platform_data	*pdata;
	struct regulator		*reg;
	struct work_struct		poll_work;
	wait_queue_head_t		wq_data_avail;
	const struct ad7606_bus_ops	*bops;
	unsigned			range;
	unsigned			oversampling;
	bool				done;
	void __iomem			*base_address;

	/*
	 * DMA (thus cache coherency maintenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */

	unsigned short			data[8] ____cacheline_aligned;
};

struct ad7606_bus_ops {
	/* more methods added in future? */
	int (*read_block)(struct device *, int, void *);
};

void ad7606_suspend(struct iio_dev *indio_dev);
void ad7606_resume(struct iio_dev *indio_dev);
struct iio_dev *ad7606_probe(struct device *dev, int irq,
			      void __iomem *base_address, unsigned id,
			      const struct ad7606_bus_ops *bops);
int ad7606_remove(struct iio_dev *indio_dev, int irq);
int ad7606_reset(struct ad7606_state *st);

enum ad7606_supported_device_ids {
	ID_AD7606_8,
	ID_AD7606_6,
	ID_AD7606_4
};

int ad7606_register_ring_funcs_and_init(struct iio_dev *indio_dev);
void ad7606_ring_cleanup(struct iio_dev *indio_dev);
#endif /* IIO_ADC_AD7606_H_ */
