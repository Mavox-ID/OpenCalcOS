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
#ifndef CSR_WIFI_RESULT_H__
#define CSR_WIFI_RESULT_H__

#include "csr_result.h"

/* THIS FILE SHOULD CONTAIN ONLY RESULT CODES */

/* Result Codes */
#define CSR_WIFI_HIP_RESULT_INVALID_VALUE    ((CsrResult) 1) /* Invalid argument value */
#define CSR_WIFI_HIP_RESULT_NO_DEVICE        ((CsrResult) 2) /* The specified device is no longer present */
#define CSR_WIFI_HIP_RESULT_NO_SPACE         ((CsrResult) 3) /* A queue or buffer is full */
#define CSR_WIFI_HIP_RESULT_NO_MEMORY        ((CsrResult) 4) /* Fatal error, no memory */
#define CSR_WIFI_HIP_RESULT_RANGE            ((CsrResult) 5) /* Request exceeds the range of a file or a buffer */
#define CSR_WIFI_HIP_RESULT_NOT_FOUND        ((CsrResult) 6) /* A file (typically a f/w patch) is not found */

#endif /* CSR_WIFI_RESULT_H__ */

