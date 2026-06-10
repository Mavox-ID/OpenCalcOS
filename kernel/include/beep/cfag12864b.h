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
#ifndef _CFAG12864B_H_
#define _CFAG12864B_H_

#define CFAG12864B_WIDTH	(128)
#define CFAG12864B_HEIGHT	(64)
#define CFAG12864B_CONTROLLERS	(2)
#define CFAG12864B_PAGES	(8)
#define CFAG12864B_ADDRESSES	(64)
#define CFAG12864B_SIZE		((CFAG12864B_CONTROLLERS) * \
				(CFAG12864B_PAGES) * \
				(CFAG12864B_ADDRESSES))

/*
 * The driver will blit this buffer to the LCD
 *
 * Its size is CFAG12864B_SIZE.
 */
extern unsigned char * cfag12864b_buffer;

/*
 * Get the refresh rate of the LCD
 *
 * Returns the refresh rate (hertz).
 */
extern unsigned int cfag12864b_getrate(void);

/*
 * Enable refreshing
 *
 * Returns 0 if successful (anyone was using it),
 * or != 0 if failed (someone is using it).
 */
extern unsigned char cfag12864b_enable(void);

/*
 * Disable refreshing
 *
 * You should call this only when you finish using the LCD.
 */
extern void cfag12864b_disable(void);

/*
 * Is enabled refreshing? (is anyone using the module?)
 *
 * Returns 0 if refreshing is not enabled (anyone is using it),
 * or != 0 if refreshing is enabled (someone is using it).
 *
 * Useful for buffer read-only modules.
 */
extern unsigned char cfag12864b_isenabled(void);

/*
 * Is the module inited?
 */
extern unsigned char cfag12864b_isinited(void);

#endif /* _CFAG12864B_H_ */

