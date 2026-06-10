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
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <beep/stddef.h>	/* offsetof(), etc. */
#include <beep/errno.h>	/* return codes */
#include <beep/string.h>	/* inline memset(), etc. */
#include <beep/slab.h>		/* kmalloc(), kfree() */
#include <beep/kernel.h>	/* printk(), and other useful stuff */
#include <beep/module.h>	/* support for loadable modules */
#include <beep/ioport.h>	/* request_region(), release_region() */
#include <beep/wanrouter.h>	/* WAN router definitions */
#include <beep/cyclomx.h>	/* cyclomx common user API definitions */
#include <beep/init.h>         /* __init (when not using as a module) */
#include <beep/interrupt.h>

unsigned int cycx_debug;

MODULE_AUTHOR("Arnaldo Carvalho de Melo");
MODULE_DESCRIPTION("Cyclom 2X Sync Card Driver.");
MODULE_LICENSE("GPL");
module_param(cycx_debug, int, 0);
MODULE_PARM_DESC(cycx_debug, "cyclomx debug level");

/* Defines & Macros */

#define	CYCX_DRV_VERSION	0	/* version number */
#define	CYCX_DRV_RELEASE	11	/* release (minor version) number */
#define	CYCX_MAX_CARDS		1	/* max number of adapters */

#define	CONFIG_CYCX_CARDS 1

/* Function Prototypes */

/* WAN link driver entry points */
static int cycx_wan_setup(struct wan_device *wandev, wandev_conf_t *conf);
static int cycx_wan_shutdown(struct wan_device *wandev);

/* Miscellaneous functions */
static irqreturn_t cycx_isr(int irq, void *dev_id);

/* Global Data
 * Note: All data must be explicitly initialized!!!
 */

/* private data */
static const char cycx_drvname[] = "cyclomx";
static const char cycx_fullname[] = "CYCLOM 2X(tm) Sync Card Driver";
static const char cycx_copyright[] = "(c) 1998-2003 Arnaldo Carvalho de Melo "
			  "<acme@conectiva.com.br>";
static int cycx_ncards = CONFIG_CYCX_CARDS;
static struct cycx_device *cycx_card_array;	/* adapter data space */

/* Kernel Loadable Module Entry Points */

/*
 * Module 'insert' entry point.
 * o print announcement
 * o allocate adapter data space
 * o initialize static data
 * o register all cards with WAN router
 * o calibrate Cyclom 2X shared memory access delay.
 *
 * Return:	0	Ok
 *		< 0	error.
 * Context:	process
 */
static int __init cycx_init(void)
{
	int cnt, err = -ENOMEM;

	pr_info("%s v%u.%u %s\n",
		cycx_fullname, CYCX_DRV_VERSION, CYCX_DRV_RELEASE,
		cycx_copyright);

	/* Verify number of cards and allocate adapter data space */
	cycx_ncards = min_t(int, cycx_ncards, CYCX_MAX_CARDS);
	cycx_ncards = max_t(int, cycx_ncards, 1);
	cycx_card_array = kcalloc(cycx_ncards, sizeof(struct cycx_device), GFP_KERNEL);
	if (!cycx_card_array)
		goto out;


	/* Register adapters with WAN router */
	for (cnt = 0; cnt < cycx_ncards; ++cnt) {
		struct cycx_device *card = &cycx_card_array[cnt];
		struct wan_device *wandev = &card->wandev;

		sprintf(card->devname, "%s%d", cycx_drvname, cnt + 1);
		wandev->magic    = ROUTER_MAGIC;
		wandev->name     = card->devname;
		wandev->private  = card;
		wandev->setup    = cycx_wan_setup;
		wandev->shutdown = cycx_wan_shutdown;
		err = register_wan_device(wandev);

		if (err) {
			pr_err("%s registration failed with error %d!\n",
			       card->devname, err);
			break;
		}
	}

	err = -ENODEV;
	if (!cnt) {
		kfree(cycx_card_array);
		goto out;
	}
	err = 0;
	cycx_ncards = cnt;	/* adjust actual number of cards */
out:	return err;
}

/*
 * Module 'remove' entry point.
 * o unregister all adapters from the WAN router
 * o release all remaining system resources
 */
static void __exit cycx_exit(void)
{
	int i = 0;

	for (; i < cycx_ncards; ++i) {
		struct cycx_device *card = &cycx_card_array[i];
		unregister_wan_device(card->devname);
	}

	kfree(cycx_card_array);
}

/* WAN Device Driver Entry Points */
/*
 * Setup/configure WAN link driver.
 * o check adapter state
 * o make sure firmware is present in configuration
 * o allocate interrupt vector
 * o setup Cyclom 2X hardware
 * o call appropriate routine to perform protocol-specific initialization
 *
 * This function is called when router handles ROUTER_SETUP IOCTL. The
 * configuration structure is in kernel memory (including extended data, if
 * any).
 */
static int cycx_wan_setup(struct wan_device *wandev, wandev_conf_t *conf)
{
	int rc = -EFAULT;
	struct cycx_device *card;
	int irq;

	/* Sanity checks */

	if (!wandev || !wandev->private || !conf)
		goto out;

	card = wandev->private;
	rc = -EBUSY;
	if (wandev->state != WAN_UNCONFIGURED)
		goto out;

	rc = -EINVAL;
	if (!conf->data_size || !conf->data) {
		pr_err("%s: firmware not found in configuration data!\n",
		       wandev->name);
		goto out;
	}

	if (conf->irq <= 0) {
		pr_err("%s: can't configure without IRQ!\n", wandev->name);
		goto out;
	}

	/* Allocate IRQ */
	irq = conf->irq == 2 ? 9 : conf->irq;	/* IRQ2 -> IRQ9 */

	if (request_irq(irq, cycx_isr, 0, wandev->name, card)) {
		pr_err("%s: can't reserve IRQ %d!\n", wandev->name, irq);
		goto out;
	}

	/* Configure hardware, load firmware, etc. */
	memset(&card->hw, 0, sizeof(card->hw));
	card->hw.irq	 = irq;
	card->hw.dpmsize = CYCX_WINDOWSIZE;
	card->hw.fwid	 = CFID_X25_2X;
	spin_lock_init(&card->lock);
	init_waitqueue_head(&card->wait_stats);

	rc = cycx_setup(&card->hw, conf->data, conf->data_size, conf->maddr);
	if (rc)
		goto out_irq;

	/* Initialize WAN device data space */
	wandev->irq       = irq;
	wandev->dma       = wandev->ioport = 0;
	wandev->maddr     = (unsigned long)card->hw.dpmbase;
	wandev->msize     = card->hw.dpmsize;
	wandev->hw_opt[2] = 0;
	wandev->hw_opt[3] = card->hw.fwid;

	/* Protocol-specific initialization */
	switch (card->hw.fwid) {
#ifdef CONFIG_CYCLOMX_X25
	case CFID_X25_2X:
		rc = cycx_x25_wan_init(card, conf);
		break;
#endif
	default:
		pr_err("%s: this firmware is not supported!\n", wandev->name);
		rc = -EINVAL;
	}

	if (rc) {
		cycx_down(&card->hw);
		goto out_irq;
	}

	rc = 0;
out:
	return rc;
out_irq:
	free_irq(irq, card);
	goto out;
}

/*
 * Shut down WAN link driver.
 * o shut down adapter hardware
 * o release system resources.
 *
 * This function is called by the router when device is being unregistered or
 * when it handles ROUTER_DOWN IOCTL.
 */
static int cycx_wan_shutdown(struct wan_device *wandev)
{
	int ret = -EFAULT;
	struct cycx_device *card;

	/* sanity checks */
	if (!wandev || !wandev->private)
		goto out;

	ret = 0;
	if (wandev->state == WAN_UNCONFIGURED)
		goto out;

	card = wandev->private;
	wandev->state = WAN_UNCONFIGURED;
	cycx_down(&card->hw);
	pr_info("%s: irq %d being freed!\n", wandev->name, wandev->irq);
	free_irq(wandev->irq, card);
out:	return ret;
}

/* Miscellaneous */
/*
 * Cyclom 2X Interrupt Service Routine.
 * o acknowledge Cyclom 2X hardware interrupt.
 * o call protocol-specific interrupt service routine, if any.
 */
static irqreturn_t cycx_isr(int irq, void *dev_id)
{
	struct cycx_device *card = dev_id;

	if (card->wandev.state == WAN_UNCONFIGURED)
		goto out;

	if (card->in_isr) {
		pr_warn("%s: interrupt re-entrancy on IRQ %d!\n",
			card->devname, card->wandev.irq);
		goto out;
	}

	if (card->isr)
		card->isr(card);
	return IRQ_HANDLED;
out:
	return IRQ_NONE;
}

/* Set WAN device state.  */
void cycx_set_state(struct cycx_device *card, int state)
{
	unsigned long flags;
	char *string_state = NULL;

	spin_lock_irqsave(&card->lock, flags);

	if (card->wandev.state != state) {
		switch (state) {
		case WAN_CONNECTED:
			string_state = "connected!";
			break;
		case WAN_DISCONNECTED:
			string_state = "disconnected!";
			break;
		}
		pr_info("%s: link %s\n", card->devname, string_state);
		card->wandev.state = state;
	}

	card->state_tick = jiffies;
	spin_unlock_irqrestore(&card->lock, flags);
}

module_init(cycx_init);
module_exit(cycx_exit);
