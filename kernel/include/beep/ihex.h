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
#ifndef __BEEP_IHEX_H__
#define __BEEP_IHEX_H__

#include <beep/types.h>
#include <beep/firmware.h>
#include <beep/device.h>

/* Intel HEX files actually limit the length to 256 bytes, but we have
   drivers which would benefit from using separate records which are
   longer than that, so we extend to 16 bits of length */
struct ihex_binrec {
	__be32 addr;
	__be16 len;
	uint8_t data[0];
} __attribute__((packed));

/* Find the next record, taking into account the 4-byte alignment */
static inline const struct ihex_binrec *
ihex_next_binrec(const struct ihex_binrec *rec)
{
	int next = ((be16_to_cpu(rec->len) + 5) & ~3) - 2;
	rec = (void *)&rec->data[next];

	return be16_to_cpu(rec->len) ? rec : NULL;
}

/* Check that ihex_next_binrec() won't take us off the end of the image... */
static inline int ihex_validate_fw(const struct firmware *fw)
{
	const struct ihex_binrec *rec;
	size_t ofs = 0;

	while (ofs <= fw->size - sizeof(*rec)) {
		rec = (void *)&fw->data[ofs];

		/* Zero length marks end of records */
		if (!be16_to_cpu(rec->len))
			return 0;

		/* Point to next record... */
		ofs += (sizeof(*rec) + be16_to_cpu(rec->len) + 3) & ~3;
	}
	return -EINVAL;
}

/* Request firmware and validate it so that we can trust we won't
 * run off the end while reading records... */
static inline int request_ihex_firmware(const struct firmware **fw,
					const char *fw_name,
					struct device *dev)
{
	const struct firmware *lfw;
	int ret;

	ret = request_firmware(&lfw, fw_name, dev);
	if (ret)
		return ret;
	ret = ihex_validate_fw(lfw);
	if (ret) {
		dev_err(dev, "Firmware \"%s\" not valid IHEX records\n",
			fw_name);
		release_firmware(lfw);
		return ret;
	}
	*fw = lfw;
	return 0;
}
#endif /* __BEEP_IHEX_H__ */
