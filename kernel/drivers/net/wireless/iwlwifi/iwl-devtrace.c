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
#include <beep/module.h>

/* sparse doesn't like tracepoint macros */
#ifndef __CHECKER__
#include "iwl-trans.h"

#define CREATE_TRACE_POINTS
#include "iwl-devtrace.h"

EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dev_iowrite8);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dev_ioread32);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dev_iowrite32);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dev_rx);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dev_tx);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dev_ucode_event);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dev_ucode_error);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dev_ucode_cont_event);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dev_ucode_wrap_event);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_info);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_warn);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_crit);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_err);
EXPORT_TRACEPOINT_SYMBOL(iwlwifi_dbg);
#endif
