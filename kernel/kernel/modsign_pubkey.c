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
#include <beep/kernel.h>
#include <beep/sched.h>
#include <beep/cred.h>
#include <beep/err.h>
#include <keys/asymmetric-type.h>
#include "module-internal.h"

struct key *modsign_keyring;

extern __initdata const u8 modsign_certificate_list[];
extern __initdata const u8 modsign_certificate_list_end[];

/*
 * We need to make sure ccache doesn't cache the .o file as it doesn't notice
 * if modsign.pub changes.
 */
static __initdata const char annoy_ccache[] = __TIME__ "foo";

/*
 * Load the compiled-in keys
 */
static __init int module_verify_init(void)
{
	pr_notice("Initialise module verification\n");

	modsign_keyring = keyring_alloc(".module_sign",
					KUIDT_INIT(0), KGIDT_INIT(0),
					current_cred(),
					((KEY_POS_ALL & ~KEY_POS_SETATTR) |
					 KEY_USR_VIEW | KEY_USR_READ),
					KEY_ALLOC_NOT_IN_QUOTA, NULL);
	if (IS_ERR(modsign_keyring))
		panic("Can't allocate module signing keyring\n");

	return 0;
}

/*
 * Must be initialised before we try and load the keys into the keyring.
 */
device_initcall(module_verify_init);

/*
 * Load the compiled-in keys
 */
static __init int load_module_signing_keys(void)
{
	key_ref_t key;
	const u8 *p, *end;
	size_t plen;

	pr_notice("Loading module verification certificates\n");

	end = modsign_certificate_list_end;
	p = modsign_certificate_list;
	while (p < end) {
		/* Each cert begins with an ASN.1 SEQUENCE tag and must be more
		 * than 256 bytes in size.
		 */
		if (end - p < 4)
			goto dodgy_cert;
		if (p[0] != 0x30 &&
		    p[1] != 0x82)
			goto dodgy_cert;
		plen = (p[2] << 8) | p[3];
		plen += 4;
		if (plen > end - p)
			goto dodgy_cert;

		key = key_create_or_update(make_key_ref(modsign_keyring, 1),
					   "asymmetric",
					   NULL,
					   p,
					   plen,
					   (KEY_POS_ALL & ~KEY_POS_SETATTR) |
					   KEY_USR_VIEW,
					   KEY_ALLOC_NOT_IN_QUOTA);
		if (IS_ERR(key))
			pr_err("MODSIGN: Problem loading in-kernel X.509 certificate (%ld)\n",
			       PTR_ERR(key));
		else
			pr_notice("MODSIGN: Loaded cert '%s'\n",
				  key_ref_to_ptr(key)->description);
		p += plen;
	}

	return 0;

dodgy_cert:
	pr_err("MODSIGN: Problem parsing in-kernel X.509 certificate list\n");
	return 0;
}
late_initcall(load_module_signing_keys);
