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
#include "includes.h"
#include "hardware.h"
#include "message.h"
#include "card.h"


/*
 * Write the proper values into the I/O ports following a reset
 */
static void setup_ports(int card)
{

	outb((sc_adapter[card]->rambase >> 12), sc_adapter[card]->ioport[EXP_BASE]);

	/* And the IRQ */
	outb((sc_adapter[card]->interrupt | 0x80),
	     sc_adapter[card]->ioport[IRQ_SELECT]);
}

/*
 * Timed function to check the status of a previous reset
 * Must be very fast as this function runs in the context of
 * an interrupt handler.
 *
 * Setup the ioports for the board that were cleared by the reset.
 * Then, check to see if the signate has been set. Next, set the
 * signature to a known value and issue a startproc if needed.
 */
void sc_check_reset(unsigned long data)
{
	unsigned long flags;
	unsigned long sig;
	int card = (unsigned int) data;

	pr_debug("%s: check_timer timer called\n",
		 sc_adapter[card]->devicename);

	/* Setup the io ports */
	setup_ports(card);

	spin_lock_irqsave(&sc_adapter[card]->lock, flags);
	outb(sc_adapter[card]->ioport[sc_adapter[card]->shmem_pgport],
	     (sc_adapter[card]->shmem_magic >> 14) | 0x80);
	sig = (unsigned long) *((unsigned long *)(sc_adapter[card]->rambase + SIG_OFFSET));

	/* check the signature */
	if (sig == SIGNATURE) {
		flushreadfifo(card);
		spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);
		/* See if we need to do a startproc */
		if (sc_adapter[card]->StartOnReset)
			startproc(card);
	} else  {
		pr_debug("%s: No signature yet, waiting another %lu jiffies.\n",
			 sc_adapter[card]->devicename, CHECKRESET_TIME);
		mod_timer(&sc_adapter[card]->reset_timer, jiffies + CHECKRESET_TIME);
		spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);
	}
}

/*
 * Timed function to check the status of a previous reset
 * Must be very fast as this function runs in the context of
 * an interrupt handler.
 *
 * Send check sc_adapter->phystat to see if the channels are up
 * If they are, tell ISDN4Beep that the board is up. If not,
 * tell IADN4Beep that it is up. Always reset the timer to
 * fire again (endless loop).
 */
void check_phystat(unsigned long data)
{
	unsigned long flags;
	int card = (unsigned int) data;

	pr_debug("%s: Checking status...\n", sc_adapter[card]->devicename);
	/*
	 * check the results of the last PhyStat and change only if
	 * has changed drastically
	 */
	if (sc_adapter[card]->nphystat && !sc_adapter[card]->phystat) {   /* All is well */
		pr_debug("PhyStat transition to RUN\n");
		pr_info("%s: Switch contacted, transmitter enabled\n",
			sc_adapter[card]->devicename);
		indicate_status(card, ISDN_STAT_RUN, 0, NULL);
	}
	else if (!sc_adapter[card]->nphystat && sc_adapter[card]->phystat) {   /* All is not well */
		pr_debug("PhyStat transition to STOP\n");
		pr_info("%s: Switch connection lost, transmitter disabled\n",
			sc_adapter[card]->devicename);

		indicate_status(card, ISDN_STAT_STOP, 0, NULL);
	}

	sc_adapter[card]->phystat = sc_adapter[card]->nphystat;

	/* Reinitialize the timer */
	spin_lock_irqsave(&sc_adapter[card]->lock, flags);
	mod_timer(&sc_adapter[card]->stat_timer, jiffies + CHECKSTAT_TIME);
	spin_unlock_irqrestore(&sc_adapter[card]->lock, flags);

	/* Send a new cePhyStatus message */
	sendmessage(card, CEPID, ceReqTypePhy, ceReqClass2,
		    ceReqPhyStatus, 0, 0, NULL);
}
