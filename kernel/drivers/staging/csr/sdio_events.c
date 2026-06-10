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
#include "unifi_priv.h"


/*
 * Porting Notes:
 * There are two ways to support the suspend/resume system events in a driver.
 * In some operating systems these events are delivered to the OS driver
 * directly from the system. In this case, the OS driver needs to pass these
 * events to the API described in the CSR SDIO Abstration API document.
 * In Beep, and other embedded operating systems, the suspend/resume events
 * come from the SDIO driver. In this case, simply get these events in the
 * SDIO glue layer and notify the OS layer.
 *
 * In either case, typically, the events are processed by the SME.
 * Use the unifi_sys_suspend_ind() and unifi_sys_resume_ind() to pass
 * the events to the SME.
 */

/*
 * ---------------------------------------------------------------------------
 *  unifi_suspend
 *
 *      Handles a suspend request from the SDIO driver.
 *
 *  Arguments:
 *      ospriv          Pointer to OS driver context.
 *
 * ---------------------------------------------------------------------------
 */
void unifi_suspend(void *ospriv)
{
    unifi_priv_t *priv = ospriv;
    int interfaceTag=0;

    /* For powered suspend, tell the resume's wifi_on() not to reinit UniFi */
    priv->wol_suspend = (enable_wol == UNIFI_WOL_OFF) ? FALSE : TRUE;

    unifi_trace(priv, UDBG1, "unifi_suspend: wol_suspend %d, enable_wol %d",
                priv->wol_suspend, enable_wol );

    /* Stop network traffic. */
    /* need to stop all the netdevices*/
    for( interfaceTag=0;interfaceTag<CSR_WIFI_NUM_INTERFACES;interfaceTag++)
    {
        netInterface_priv_t *interfacePriv = priv->interfacePriv[interfaceTag];
        if (interfacePriv->netdev_registered == 1)
        {
            if( priv->wol_suspend ) {
                unifi_trace(priv, UDBG1, "unifi_suspend: Don't netif_carrier_off");
            } else {
                unifi_trace(priv, UDBG1, "unifi_suspend: netif_carrier_off");
                netif_carrier_off(priv->netdev[interfaceTag]);
            }
            netif_tx_stop_all_queues(priv->netdev[interfaceTag]);
        }
    }

    unifi_trace(priv, UDBG1, "unifi_suspend: suspend SME");

    sme_sys_suspend(priv);

} /* unifi_suspend() */


/*
 * ---------------------------------------------------------------------------
 *  unifi_resume
 *
 *      Handles a resume request from the SDIO driver.
 *
 *  Arguments:
 *      ospriv          Pointer to OS driver context.
 *
 * ---------------------------------------------------------------------------
 */
void unifi_resume(void *ospriv)
{
    unifi_priv_t *priv = ospriv;
    int interfaceTag=0;
    int r;
    int wol = priv->wol_suspend;

    unifi_trace(priv, UDBG1, "unifi_resume: resume SME, enable_wol=%d", enable_wol);

    /* The resume causes wifi-on which will re-enable the BH and reinstall the ISR */
    r = sme_sys_resume(priv);
    if (r) {
        unifi_error(priv, "Failed to resume UniFi\n");
    }

    /* Resume the network interfaces. For the cold resume case, this will
     * happen upon reconnection.
     */
    if (wol) {
        unifi_trace(priv, UDBG1, "unifi_resume: try to enable carrier");

        /* need to start all the netdevices*/
        for( interfaceTag=0;interfaceTag<CSR_WIFI_NUM_INTERFACES;interfaceTag++) {
            netInterface_priv_t *interfacePriv = priv->interfacePriv[interfaceTag];

            unifi_trace(priv, UDBG1, "unifi_resume: interfaceTag %d netdev_registered %d mode %d\n",
                   interfaceTag, interfacePriv->netdev_registered, interfacePriv->interfaceMode);

            if (interfacePriv->netdev_registered == 1)
            {
                netif_carrier_on(priv->netdev[interfaceTag]);
                netif_tx_start_all_queues(priv->netdev[interfaceTag]);
            }
        }

        /* Kick the BH thread (with reason=host) to poll for data that may have
         * arrived during a powered suspend. This caters for the case where the SME
         * doesn't interact with the chip (e.g install autonomous scans) during resume.
         */
        unifi_send_signal(priv->card, NULL, 0, NULL);
    }

} /* unifi_resume() */

