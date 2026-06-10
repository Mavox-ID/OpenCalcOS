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
#include "csr_wifi_hip_unifi.h"

void __attribute__((weak)) CsrSdioFunctionIdle(CsrSdioFunction *function)
{
}

void __attribute__((weak)) CsrSdioFunctionActive(CsrSdioFunction *function)
{
}

CsrResult __attribute__((weak)) CsrSdioPowerOn(CsrSdioFunction *function)
{
    return CSR_RESULT_SUCCESS;
}

void __attribute__((weak)) CsrSdioPowerOff(CsrSdioFunction *function)
{
}

CsrResult __attribute__((weak)) CsrSdioHardReset(CsrSdioFunction *function)
{
    return CSR_SDIO_RESULT_NOT_RESET;
}

CsrResult __attribute__((weak)) CsrSdioBlockSizeSet(CsrSdioFunction *function,
                                                   u16 blockSize)
{
    return CSR_RESULT_SUCCESS;
}

CsrResult __attribute__((weak)) CsrSdioSuspend(CsrSdioFunction *function)
{
    return CSR_RESULT_SUCCESS;
}

CsrResult __attribute__((weak)) CsrSdioResume(CsrSdioFunction *function)
{
    return CSR_RESULT_SUCCESS;
}

int __attribute__((weak)) csr_sdio_beep_install_irq(CsrSdioFunction *function)
{
    return 0;
}

int __attribute__((weak)) csr_sdio_beep_remove_irq(CsrSdioFunction *function)
{
    return 0;
}

void __attribute__((weak)) CsrSdioInsertedAcknowledge(CsrSdioFunction *function, CsrResult result)
{
}

void __attribute__((weak)) CsrSdioRemovedAcknowledge(CsrSdioFunction *function)
{
}

void __attribute__((weak)) CsrSdioSuspendAcknowledge(CsrSdioFunction *function, CsrResult result)
{
}

void __attribute__((weak)) CsrSdioResumeAcknowledge(CsrSdioFunction *function, CsrResult result)
{
}


