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
#ifndef _BEEP_TP3780I_H
#define _BEEP_TP3780I_H

#include <asm/io.h>
#include "mwavepub.h"


/* DSP abilities constants for 3780i based Thinkpads */
#define TP_ABILITIES_INTS_PER_SEC       39160800
#define TP_ABILITIES_DATA_SIZE          32768
#define TP_ABILITIES_INST_SIZE          32768
#define TP_ABILITIES_MWAVEOS_NAME       "mwaveos0700.dsp"
#define TP_ABILITIES_BIOSTASK_NAME      "mwbio701.dsp"


/* DSP configuration values for 3780i based Thinkpads */
#define TP_CFG_NumTransfers     3	/* 16 transfers */
#define TP_CFG_RerequestTimer   1	/* 2 usec */
#define TP_CFG_MEMCS16          0	/* Disabled, 16-bit memory assumed */
#define TP_CFG_IsaMemCmdWidth   3	/* 295 nsec (16-bit) */
#define TP_CFG_GateIOCHRDY      0	/* No IOCHRDY gating */
#define TP_CFG_EnablePwrMgmt    1	/* Enable low poser suspend/resume */
#define TP_CFG_HBusTimerValue 255	/* HBus timer load value */
#define TP_CFG_DisableLBusTimeout 0	/* Enable LBus timeout */
#define TP_CFG_N_Divisor       32	/* Clock = 39.1608 Mhz */
#define TP_CFG_M_Multiplier    37	/* " */
#define TP_CFG_PllBypass        0	/* don't bypass */
#define TP_CFG_ChipletEnable 0xFFFF	/* Enable all chiplets */

typedef struct {
	int bDSPEnabled;
	int bShareDspIrq;
	int bShareUartIrq;
	DSP_3780I_CONFIG_SETTINGS rDspSettings;
} THINKPAD_BD_DATA;

int tp3780I_InitializeBoardData(THINKPAD_BD_DATA * pBDData);
int tp3780I_CalcResources(THINKPAD_BD_DATA * pBDData);
int tp3780I_ClaimResources(THINKPAD_BD_DATA * pBDData);
int tp3780I_ReleaseResources(THINKPAD_BD_DATA * pBDData);
int tp3780I_EnableDSP(THINKPAD_BD_DATA * pBDData);
int tp3780I_DisableDSP(THINKPAD_BD_DATA * pBDData);
int tp3780I_ResetDSP(THINKPAD_BD_DATA * pBDData);
int tp3780I_StartDSP(THINKPAD_BD_DATA * pBDData);
int tp3780I_QueryAbilities(THINKPAD_BD_DATA * pBDData, MW_ABILITIES * pAbilities);
int tp3780I_Cleanup(THINKPAD_BD_DATA * pBDData);
int tp3780I_ReadWriteDspDStore(THINKPAD_BD_DATA * pBDData, unsigned int uOpcode,
                               void __user *pvBuffer, unsigned int uCount,
                               unsigned long ulDSPAddr);
int tp3780I_ReadWriteDspIStore(THINKPAD_BD_DATA * pBDData, unsigned int uOpcode,
                               void __user *pvBuffer, unsigned int uCount,
                               unsigned long ulDSPAddr);


#endif
