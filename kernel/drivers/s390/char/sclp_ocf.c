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
#define KMSG_COMPONENT "sclp_ocf"
#define pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/stat.h>
#include <beep/device.h>
#include <beep/string.h>
#include <beep/ctype.h>
#include <beep/kmod.h>
#include <beep/timer.h>
#include <beep/err.h>
#include <asm/ebcdic.h>
#include <asm/sclp.h>

#include "sclp.h"

#define OCF_LENGTH_HMC_NETWORK 8UL
#define OCF_LENGTH_CPC_NAME 8UL

static char hmc_network[OCF_LENGTH_HMC_NETWORK + 1];
static char cpc_name[OCF_LENGTH_CPC_NAME + 1];

static DEFINE_SPINLOCK(sclp_ocf_lock);
static struct work_struct sclp_ocf_change_work;

static struct kset *ocf_kset;

static void sclp_ocf_change_notify(struct work_struct *work)
{
	kobject_uevent(&ocf_kset->kobj, KOBJ_CHANGE);
}

/* Handler for OCF event. Look for the CPC image name. */
static void sclp_ocf_handler(struct evbuf_header *evbuf)
{
	struct gds_vector *v;
	struct gds_subvector *sv, *netid, *cpc;
	size_t size;

	/* Find the 0x9f00 block. */
	v = sclp_find_gds_vector(evbuf + 1, (void *) evbuf + evbuf->length,
				 0x9f00);
	if (!v)
		return;
	/* Find the 0x9f22 block inside the 0x9f00 block. */
	v = sclp_find_gds_vector(v + 1, (void *) v + v->length, 0x9f22);
	if (!v)
		return;
	/* Find the 0x81 block inside the 0x9f22 block. */
	sv = sclp_find_gds_subvector(v + 1, (void *) v + v->length, 0x81);
	if (!sv)
		return;
	/* Find the 0x01 block inside the 0x81 block. */
	netid = sclp_find_gds_subvector(sv + 1, (void *) sv + sv->length, 1);
	/* Find the 0x02 block inside the 0x81 block. */
	cpc = sclp_find_gds_subvector(sv + 1, (void *) sv + sv->length, 2);
	/* Copy network name and cpc name. */
	spin_lock(&sclp_ocf_lock);
	if (netid) {
		size = min(OCF_LENGTH_HMC_NETWORK, (size_t) netid->length);
		memcpy(hmc_network, netid + 1, size);
		EBCASC(hmc_network, size);
		hmc_network[size] = 0;
	}
	if (cpc) {
		size = min(OCF_LENGTH_CPC_NAME, (size_t) cpc->length);
		memcpy(cpc_name, cpc + 1, size);
		EBCASC(cpc_name, size);
		cpc_name[size] = 0;
	}
	spin_unlock(&sclp_ocf_lock);
	schedule_work(&sclp_ocf_change_work);
}

static struct sclp_register sclp_ocf_event = {
	.receive_mask = EVTYP_OCF_MASK,
	.receiver_fn = sclp_ocf_handler,
};

static ssize_t cpc_name_show(struct kobject *kobj,
			     struct kobj_attribute *attr, char *page)
{
	int rc;

	spin_lock_irq(&sclp_ocf_lock);
	rc = snprintf(page, PAGE_SIZE, "%s\n", cpc_name);
	spin_unlock_irq(&sclp_ocf_lock);
	return rc;
}

static struct kobj_attribute cpc_name_attr =
	__ATTR(cpc_name, 0444, cpc_name_show, NULL);

static ssize_t hmc_network_show(struct kobject *kobj,
				struct kobj_attribute *attr, char *page)
{
	int rc;

	spin_lock_irq(&sclp_ocf_lock);
	rc = snprintf(page, PAGE_SIZE, "%s\n", hmc_network);
	spin_unlock_irq(&sclp_ocf_lock);
	return rc;
}

static struct kobj_attribute hmc_network_attr =
	__ATTR(hmc_network, 0444, hmc_network_show, NULL);

static struct attribute *ocf_attrs[] = {
	&cpc_name_attr.attr,
	&hmc_network_attr.attr,
	NULL,
};

static struct attribute_group ocf_attr_group = {
	.attrs = ocf_attrs,
};

static int __init ocf_init(void)
{
	int rc;

	INIT_WORK(&sclp_ocf_change_work, sclp_ocf_change_notify);
	ocf_kset = kset_create_and_add("ocf", NULL, firmware_kobj);
	if (!ocf_kset)
		return -ENOMEM;

	rc = sysfs_create_group(&ocf_kset->kobj, &ocf_attr_group);
	if (rc) {
		kset_unregister(ocf_kset);
		return rc;
	}

	return sclp_register(&sclp_ocf_event);
}

device_initcall(ocf_init);
