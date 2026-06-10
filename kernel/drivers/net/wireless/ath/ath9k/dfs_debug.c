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
#include <beep/export.h>

#include "ath9k.h"
#include "dfs_debug.h"


struct ath_dfs_pool_stats global_dfs_pool_stats = { 0 };

#define ATH9K_DFS_STAT(s, p) \
	len += snprintf(buf + len, size - len, "%28s : %10u\n", s, \
			sc->debug.stats.dfs_stats.p);
#define ATH9K_DFS_POOL_STAT(s, p) \
	len += snprintf(buf + len, size - len, "%28s : %10u\n", s, \
			global_dfs_pool_stats.p);

static ssize_t read_file_dfs(struct file *file, char __user *user_buf,
			     size_t count, loff_t *ppos)
{
	struct ath_softc *sc = file->private_data;
	struct ath9k_hw_version *hw_ver = &sc->sc_ah->hw_version;
	char *buf;
	unsigned int len = 0, size = 8000;
	ssize_t retval = 0;

	buf = kzalloc(size, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	len += snprintf(buf + len, size - len, "DFS support for "
			"macVersion = 0x%x, macRev = 0x%x: %s\n",
			hw_ver->macVersion, hw_ver->macRev,
			(sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_DFS) ?
					"enabled" : "disabled");
	len += snprintf(buf + len, size - len, "Pulse detector statistics:\n");
	ATH9K_DFS_STAT("pulse events reported   ", pulses_total);
	ATH9K_DFS_STAT("invalid pulse events    ", pulses_no_dfs);
	ATH9K_DFS_STAT("DFS pulses detected     ", pulses_detected);
	ATH9K_DFS_STAT("Datalen discards        ", datalen_discards);
	ATH9K_DFS_STAT("RSSI discards           ", rssi_discards);
	ATH9K_DFS_STAT("BW info discards        ", bwinfo_discards);
	ATH9K_DFS_STAT("Primary channel pulses  ", pri_phy_errors);
	ATH9K_DFS_STAT("Secondary channel pulses", ext_phy_errors);
	ATH9K_DFS_STAT("Dual channel pulses     ", dc_phy_errors);
	len += snprintf(buf + len, size - len, "Radar detector statistics "
			"(current DFS region: %d)\n", sc->dfs_detector->region);
	ATH9K_DFS_STAT("Pulse events processed  ", pulses_processed);
	ATH9K_DFS_STAT("Radars detected         ", radar_detected);
	len += snprintf(buf + len, size - len, "Global Pool statistics:\n");
	ATH9K_DFS_POOL_STAT("Pool references         ", pool_reference);
	ATH9K_DFS_POOL_STAT("Pulses allocated        ", pulse_allocated);
	ATH9K_DFS_POOL_STAT("Pulses alloc error      ", pulse_alloc_error);
	ATH9K_DFS_POOL_STAT("Pulses in use           ", pulse_used);
	ATH9K_DFS_POOL_STAT("Seqs. allocated         ", pseq_allocated);
	ATH9K_DFS_POOL_STAT("Seqs. alloc error       ", pseq_alloc_error);
	ATH9K_DFS_POOL_STAT("Seqs. in use            ", pseq_used);

	if (len > size)
		len = size;

	retval = simple_read_from_buffer(user_buf, count, ppos, buf, len);
	kfree(buf);

	return retval;
}

/* magic number to prevent accidental reset of DFS statistics */
#define DFS_STATS_RESET_MAGIC	0x80000000
static ssize_t write_file_dfs(struct file *file, const char __user *user_buf,
			      size_t count, loff_t *ppos)
{
	struct ath_softc *sc = file->private_data;
	unsigned long val;
	char buf[32];
	ssize_t len;

	len = min(count, sizeof(buf) - 1);
	if (copy_from_user(buf, user_buf, len))
		return -EFAULT;

	buf[len] = '\0';
	if (strict_strtoul(buf, 0, &val))
		return -EINVAL;

	if (val == DFS_STATS_RESET_MAGIC)
		memset(&sc->debug.stats.dfs_stats, 0,
		       sizeof(sc->debug.stats.dfs_stats));
	return count;
}

static const struct file_operations fops_dfs_stats = {
	.read = read_file_dfs,
	.write = write_file_dfs,
	.open = simple_open,
	.owner = THIS_MODULE,
	.llseek = default_llseek,
};

void ath9k_dfs_init_debug(struct ath_softc *sc)
{
	debugfs_create_file("dfs_stats", S_IRUSR,
			    sc->debug.debugfs_phy, sc, &fops_dfs_stats);
}
