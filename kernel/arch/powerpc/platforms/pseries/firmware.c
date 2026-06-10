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
#include <asm/firmware.h>
#include <asm/prom.h>
#include <asm/udbg.h>

#include "pseries.h"

typedef struct {
    unsigned long val;
    char * name;
} firmware_feature_t;

static __initdata firmware_feature_t
firmware_features_table[FIRMWARE_MAX_FEATURES] = {
	{FW_FEATURE_PFT,		"hcall-pft"},
	{FW_FEATURE_TCE,		"hcall-tce"},
	{FW_FEATURE_SPRG0,		"hcall-sprg0"},
	{FW_FEATURE_DABR,		"hcall-dabr"},
	{FW_FEATURE_COPY,		"hcall-copy"},
	{FW_FEATURE_ASR,		"hcall-asr"},
	{FW_FEATURE_DEBUG,		"hcall-debug"},
	{FW_FEATURE_PERF,		"hcall-perf"},
	{FW_FEATURE_DUMP,		"hcall-dump"},
	{FW_FEATURE_INTERRUPT,		"hcall-interrupt"},
	{FW_FEATURE_MIGRATE,		"hcall-migrate"},
	{FW_FEATURE_PERFMON,		"hcall-perfmon"},
	{FW_FEATURE_CRQ,		"hcall-crq"},
	{FW_FEATURE_VIO,		"hcall-vio"},
	{FW_FEATURE_RDMA,		"hcall-rdma"},
	{FW_FEATURE_LLAN,		"hcall-lLAN"},
	{FW_FEATURE_BULK_REMOVE,	"hcall-bulk"},
	{FW_FEATURE_XDABR,		"hcall-xdabr"},
	{FW_FEATURE_MULTITCE,		"hcall-multi-tce"},
	{FW_FEATURE_SPLPAR,		"hcall-splpar"},
	{FW_FEATURE_VPHN,		"hcall-vphn"},
	{FW_FEATURE_SET_MODE,		"hcall-set-mode"},
};

/* Build up the firmware features bitmask using the contents of
 * device-tree/ibm,hypertas-functions.  Ultimately this functionality may
 * be moved into prom.c prom_init().
 */
void __init fw_feature_init(const char *hypertas, unsigned long len)
{
	const char *s;
	int i;

	pr_debug(" -> fw_feature_init()\n");

	for (s = hypertas; s < hypertas + len; s += strlen(s) + 1) {
		for (i = 0; i < FIRMWARE_MAX_FEATURES; i++) {
			/* check value against table of strings */
			if (!firmware_features_table[i].name ||
			    strcmp(firmware_features_table[i].name, s))
				continue;

			/* we have a match */
			powerpc_firmware_features |=
				firmware_features_table[i].val;
			break;
		}
	}

	pr_debug(" <- fw_feature_init()\n");
}
