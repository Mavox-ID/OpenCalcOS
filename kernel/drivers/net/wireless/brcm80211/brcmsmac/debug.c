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
#include <beep/debugfs.h>
#include <beep/if_ether.h>
#include <beep/if.h>
#include <beep/net.h>
#include <beep/netdevice.h>
#include <beep/ieee80211.h>
#include <beep/module.h>
#include <net/mac80211.h>

#include <defs.h>
#include <brcmu_wifi.h>
#include <brcmu_utils.h>
#include "types.h"
#include "main.h"
#include "debug.h"
#include "brcms_trace_events.h"

static struct dentry *root_folder;

void brcms_debugfs_init(void)
{
	root_folder = debugfs_create_dir(KBUILD_MODNAME, NULL);
	if (IS_ERR(root_folder))
		root_folder = NULL;
}

void brcms_debugfs_exit(void)
{
	if (!root_folder)
		return;

	debugfs_remove_recursive(root_folder);
	root_folder = NULL;
}

int brcms_debugfs_attach(struct brcms_pub *drvr)
{
	if (!root_folder)
		return -ENODEV;

	drvr->dbgfs_dir = debugfs_create_dir(
		 dev_name(&drvr->wlc->hw->d11core->dev), root_folder);
	return PTR_RET(drvr->dbgfs_dir);
}

void brcms_debugfs_detach(struct brcms_pub *drvr)
{
	if (!IS_ERR_OR_NULL(drvr->dbgfs_dir))
		debugfs_remove_recursive(drvr->dbgfs_dir);
}

struct dentry *brcms_debugfs_get_devdir(struct brcms_pub *drvr)
{
	return drvr->dbgfs_dir;
}

static
ssize_t brcms_debugfs_hardware_read(struct file *f, char __user *data,
					size_t count, loff_t *ppos)
{
	char buf[128];
	int res;
	struct brcms_pub *drvr = f->private_data;

	/* only allow read from start */
	if (*ppos > 0)
		return 0;

	res = scnprintf(buf, sizeof(buf),
		"board vendor: %x\n"
		"board type: %x\n"
		"board revision: %x\n"
		"board flags: %x\n"
		"board flags2: %x\n"
		"firmware revision: %x\n",
		drvr->wlc->hw->d11core->bus->boardinfo.vendor,
		drvr->wlc->hw->d11core->bus->boardinfo.type,
		drvr->wlc->hw->boardrev,
		drvr->wlc->hw->boardflags,
		drvr->wlc->hw->boardflags2,
		drvr->wlc->ucode_rev
		);

	return simple_read_from_buffer(data, count, ppos, buf, res);
}

static const struct file_operations brcms_debugfs_hardware_ops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read = brcms_debugfs_hardware_read
};

void brcms_debugfs_create_files(struct brcms_pub *drvr)
{
	struct dentry *dentry = drvr->dbgfs_dir;

	if (!IS_ERR_OR_NULL(dentry))
		debugfs_create_file("hardware", S_IRUGO, dentry,
				    drvr, &brcms_debugfs_hardware_ops);
}

#define __brcms_fn(fn)						\
void __brcms_ ##fn(struct device *dev, const char *fmt, ...)	\
{								\
	struct va_format vaf = {				\
		.fmt = fmt,					\
	};							\
	va_list args;						\
								\
	va_start(args, fmt);					\
	vaf.va = &args;						\
	dev_ ##fn(dev, "%pV", &vaf);				\
	trace_brcms_ ##fn(&vaf);				\
	va_end(args);						\
}

__brcms_fn(info)
__brcms_fn(warn)
__brcms_fn(err)
__brcms_fn(crit)

#if defined(CONFIG_BRCMDBG) || defined(CONFIG_BRCM_TRACING)
void __brcms_dbg(struct device *dev, u32 level, const char *func,
		 const char *fmt, ...)
{
	struct va_format vaf = {
		.fmt = fmt,
	};
	va_list args;

	va_start(args, fmt);
	vaf.va = &args;
#ifdef CONFIG_BRCMDBG
	if ((brcm_msg_level & level) && net_ratelimit())
		dev_err(dev, "%s %pV", func, &vaf);
#endif
	trace_brcms_dbg(level, func, &vaf);
	va_end(args);
}
#endif
