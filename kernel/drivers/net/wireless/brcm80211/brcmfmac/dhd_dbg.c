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
#include <beep/netdevice.h>
#include <beep/module.h>

#include <brcmu_wifi.h>
#include <brcmu_utils.h>
#include "dhd.h"
#include "dhd_bus.h"
#include "dhd_dbg.h"

static struct dentry *root_folder;

void brcmf_debugfs_init(void)
{
	root_folder = debugfs_create_dir(KBUILD_MODNAME, NULL);
	if (IS_ERR(root_folder))
		root_folder = NULL;
}

void brcmf_debugfs_exit(void)
{
	if (!root_folder)
		return;

	debugfs_remove_recursive(root_folder);
	root_folder = NULL;
}

int brcmf_debugfs_attach(struct brcmf_pub *drvr)
{
	struct device *dev = drvr->bus_if->dev;

	if (!root_folder)
		return -ENODEV;

	drvr->dbgfs_dir = debugfs_create_dir(dev_name(dev), root_folder);
	return PTR_RET(drvr->dbgfs_dir);
}

void brcmf_debugfs_detach(struct brcmf_pub *drvr)
{
	if (!IS_ERR_OR_NULL(drvr->dbgfs_dir))
		debugfs_remove_recursive(drvr->dbgfs_dir);
}

struct dentry *brcmf_debugfs_get_devdir(struct brcmf_pub *drvr)
{
	return drvr->dbgfs_dir;
}

static
ssize_t brcmf_debugfs_sdio_counter_read(struct file *f, char __user *data,
					size_t count, loff_t *ppos)
{
	struct brcmf_sdio_count *sdcnt = f->private_data;
	char buf[750];
	int res;

	/* only allow read from start */
	if (*ppos > 0)
		return 0;

	res = scnprintf(buf, sizeof(buf),
			"intrcount:    %u\nlastintrs:    %u\n"
			"pollcnt:      %u\nregfails:     %u\n"
			"tx_sderrs:    %u\nfcqueued:     %u\n"
			"rxrtx:        %u\nrx_toolong:   %u\n"
			"rxc_errors:   %u\nrx_hdrfail:   %u\n"
			"rx_badhdr:    %u\nrx_badseq:    %u\n"
			"fc_rcvd:      %u\nfc_xoff:      %u\n"
			"fc_xon:       %u\nrxglomfail:   %u\n"
			"rxglomframes: %u\nrxglompkts:   %u\n"
			"f2rxhdrs:     %u\nf2rxdata:     %u\n"
			"f2txdata:     %u\nf1regdata:    %u\n"
			"tickcnt:      %u\ntx_ctlerrs:   %lu\n"
			"tx_ctlpkts:   %lu\nrx_ctlerrs:   %lu\n"
			"rx_ctlpkts:   %lu\nrx_readahead: %lu\n",
			sdcnt->intrcount, sdcnt->lastintrs,
			sdcnt->pollcnt, sdcnt->regfails,
			sdcnt->tx_sderrs, sdcnt->fcqueued,
			sdcnt->rxrtx, sdcnt->rx_toolong,
			sdcnt->rxc_errors, sdcnt->rx_hdrfail,
			sdcnt->rx_badhdr, sdcnt->rx_badseq,
			sdcnt->fc_rcvd, sdcnt->fc_xoff,
			sdcnt->fc_xon, sdcnt->rxglomfail,
			sdcnt->rxglomframes, sdcnt->rxglompkts,
			sdcnt->f2rxhdrs, sdcnt->f2rxdata,
			sdcnt->f2txdata, sdcnt->f1regdata,
			sdcnt->tickcnt, sdcnt->tx_ctlerrs,
			sdcnt->tx_ctlpkts, sdcnt->rx_ctlerrs,
			sdcnt->rx_ctlpkts, sdcnt->rx_readahead_cnt);

	return simple_read_from_buffer(data, count, ppos, buf, res);
}

static const struct file_operations brcmf_debugfs_sdio_counter_ops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read = brcmf_debugfs_sdio_counter_read
};

void brcmf_debugfs_create_sdio_count(struct brcmf_pub *drvr,
				     struct brcmf_sdio_count *sdcnt)
{
	struct dentry *dentry = drvr->dbgfs_dir;

	if (!IS_ERR_OR_NULL(dentry))
		debugfs_create_file("counters", S_IRUGO, dentry,
				    sdcnt, &brcmf_debugfs_sdio_counter_ops);
}
