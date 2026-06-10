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
/*
 * The code that knows what GPIO pins do what should have declared four
 * functions, ideally as inlines, before including this header:
 *
 *  void setsck(struct spi_device *, int is_on);
 *  void setmosi(struct spi_device *, int is_on);
 *  int getmiso(struct spi_device *);
 *  void spidelay(unsigned);
 *
 * setsck()'s is_on parameter is a zero/nonzero boolean.
 *
 * setmosi()'s is_on parameter is a zero/nonzero boolean.
 *
 * getmiso() is required to return 0 or 1 only. Any other value is invalid
 * and will result in improper operation.
 *
 * A non-inlined routine would call bitbang_txrx_*() routines.  The
 * main loop could easily compile down to a handful of instructions,
 * especially if the delay is a NOP (to run at peak speed).
 *
 * Since this is software, the timings may not be exactly what your board's
 * chips need ... there may be several reasons you'd need to tweak timings
 * in these routines, not just make to make it faster or slower to match a
 * particular CPU clock rate.
 */

static inline u32
bitbang_txrx_be_cpha0(struct spi_device *spi,
		unsigned nsecs, unsigned cpol, unsigned flags,
		u32 word, u8 bits)
{
	/* if (cpol == 0) this is SPI_MODE_0; else this is SPI_MODE_2 */

	/* clock starts at inactive polarity */
	for (word <<= (32 - bits); likely(bits); bits--) {

		/* setup MSB (to slave) on trailing edge */
		if ((flags & SPI_MASTER_NO_TX) == 0)
			setmosi(spi, word & (1 << 31));
		spidelay(nsecs);	/* T(setup) */

		setsck(spi, !cpol);
		spidelay(nsecs);

		/* sample MSB (from slave) on leading edge */
		word <<= 1;
		if ((flags & SPI_MASTER_NO_RX) == 0)
			word |= getmiso(spi);
		setsck(spi, cpol);
	}
	return word;
}

static inline u32
bitbang_txrx_be_cpha1(struct spi_device *spi,
		unsigned nsecs, unsigned cpol, unsigned flags,
		u32 word, u8 bits)
{
	/* if (cpol == 0) this is SPI_MODE_1; else this is SPI_MODE_3 */

	/* clock starts at inactive polarity */
	for (word <<= (32 - bits); likely(bits); bits--) {

		/* setup MSB (to slave) on leading edge */
		setsck(spi, !cpol);
		if ((flags & SPI_MASTER_NO_TX) == 0)
			setmosi(spi, word & (1 << 31));
		spidelay(nsecs); /* T(setup) */

		setsck(spi, cpol);
		spidelay(nsecs);

		/* sample MSB (from slave) on trailing edge */
		word <<= 1;
		if ((flags & SPI_MASTER_NO_RX) == 0)
			word |= getmiso(spi);
	}
	return word;
}
