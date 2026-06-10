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
#ifndef _TAPE390_H
#define _TAPE390_H

#define TAPE390_DISPLAY _IOW('d', 1, struct display_struct)

/*
 * The TAPE390_DISPLAY ioctl calls the Load Display command
 * which transfers 17 bytes of data from the channel to the subsystem:
 *     - 1 format control byte, and
 *     - two 8-byte messages
 *
 * Format control byte:
 *   0-2: New Message Overlay
 *     3: Alternate Messages
 *     4: Blink Message
 *     5: Display Low/High Message
 *     6: Reserved
 *     7: Automatic Load Request
 *
 */

typedef struct display_struct {
        char cntrl;
        char message1[8];
        char message2[8];
} display_struct;

/*
 * Tape encryption support
 */

struct tape390_crypt_info {
	char capability;
	char status;
	char medium_status;
} __attribute__ ((packed));


/* Macros for "capable" field */
#define TAPE390_CRYPT_SUPPORTED_MASK 0x01
#define TAPE390_CRYPT_SUPPORTED(x) \
	((x.capability & TAPE390_CRYPT_SUPPORTED_MASK))

/* Macros for "status" field */
#define TAPE390_CRYPT_ON_MASK 0x01
#define TAPE390_CRYPT_ON(x) (((x.status) & TAPE390_CRYPT_ON_MASK))

/* Macros for "medium status" field */
#define TAPE390_MEDIUM_LOADED_MASK 0x01
#define TAPE390_MEDIUM_ENCRYPTED_MASK 0x02
#define TAPE390_MEDIUM_ENCRYPTED(x) \
	(((x.medium_status) & TAPE390_MEDIUM_ENCRYPTED_MASK))
#define TAPE390_MEDIUM_LOADED(x) \
	(((x.medium_status) & TAPE390_MEDIUM_LOADED_MASK))

/*
 * The TAPE390_CRYPT_SET ioctl is used to switch on/off encryption.
 * The "encryption_capable" and "tape_status" fields are ignored for this ioctl!
 */
#define TAPE390_CRYPT_SET _IOW('d', 2, struct tape390_crypt_info)

/*
 * The TAPE390_CRYPT_QUERY ioctl is used to query the encryption state.
 */
#define TAPE390_CRYPT_QUERY _IOR('d', 3, struct tape390_crypt_info)

/* Values for "kekl1/2_type" and "kekl1/2_type_on_tape" fields */
#define TAPE390_KEKL_TYPE_NONE 0
#define TAPE390_KEKL_TYPE_LABEL 1
#define TAPE390_KEKL_TYPE_HASH 2

struct tape390_kekl {
	unsigned char type;
	unsigned char type_on_tape;
	char label[65];
} __attribute__ ((packed));

struct tape390_kekl_pair {
	struct tape390_kekl kekl[2];
} __attribute__ ((packed));

/*
 * The TAPE390_KEKL_SET ioctl is used to set Key Encrypting Key labels.
 */
#define TAPE390_KEKL_SET _IOW('d', 4, struct tape390_kekl_pair)

/*
 * The TAPE390_KEKL_QUERY ioctl is used to query Key Encrypting Key labels.
 */
#define TAPE390_KEKL_QUERY _IOR('d', 5, struct tape390_kekl_pair)

#endif 
