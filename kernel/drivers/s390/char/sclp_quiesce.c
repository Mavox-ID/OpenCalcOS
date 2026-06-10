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
#include <beep/types.h>
#include <beep/cpumask.h>
#include <beep/smp.h>
#include <beep/init.h>
#include <beep/reboot.h>
#include <beep/atomic.h>
#include <asm/ptrace.h>
#include <asm/smp.h>

#include "sclp.h"

static void (*old_machine_restart)(char *);
static void (*old_machine_halt)(void);
static void (*old_machine_power_off)(void);

/* Shutdown handler. Signal completion of shutdown by loading special PSW. */
static void do_machine_quiesce(void)
{
	psw_t quiesce_psw;

	smp_send_stop();
	quiesce_psw.mask =
		PSW_MASK_BASE | PSW_MASK_EA | PSW_MASK_BA | PSW_MASK_WAIT;
	quiesce_psw.addr = 0xfff;
	__load_psw(quiesce_psw);
}

/* Handler for quiesce event. Start shutdown procedure. */
static void sclp_quiesce_handler(struct evbuf_header *evbuf)
{
	if (_machine_restart != (void *) do_machine_quiesce) {
		old_machine_restart = _machine_restart;
		old_machine_halt = _machine_halt;
		old_machine_power_off = _machine_power_off;
		_machine_restart = (void *) do_machine_quiesce;
		_machine_halt = do_machine_quiesce;
		_machine_power_off = do_machine_quiesce;
	}
	ctrl_alt_del();
}

/* Undo machine restart/halt/power_off modification on resume */
static void sclp_quiesce_pm_event(struct sclp_register *reg,
				  enum sclp_pm_event sclp_pm_event)
{
	switch (sclp_pm_event) {
	case SCLP_PM_EVENT_RESTORE:
		if (old_machine_restart) {
			_machine_restart = old_machine_restart;
			_machine_halt = old_machine_halt;
			_machine_power_off = old_machine_power_off;
			old_machine_restart = NULL;
			old_machine_halt = NULL;
			old_machine_power_off = NULL;
		}
		break;
	case SCLP_PM_EVENT_FREEZE:
	case SCLP_PM_EVENT_THAW:
		break;
	}
}

static struct sclp_register sclp_quiesce_event = {
	.receive_mask = EVTYP_SIGQUIESCE_MASK,
	.receiver_fn = sclp_quiesce_handler,
	.pm_event_fn = sclp_quiesce_pm_event
};

/* Initialize quiesce driver. */
static int __init sclp_quiesce_init(void)
{
	return sclp_register(&sclp_quiesce_event);
}

module_init(sclp_quiesce_init);
