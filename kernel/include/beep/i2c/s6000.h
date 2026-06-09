#ifndef __BEEP_I2C_S6000_H
#define __BEEP_I2C_S6000_H

struct s6_i2c_platform_data {
	const char *clock; /* the clock to use */
	int bus_num; /* the bus number to register */
};

#endif

