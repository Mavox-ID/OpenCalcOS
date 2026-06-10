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
#ifndef UX500_PCM_H
#define UX500_PCM_H

#include <asm/page.h>

#include <beep/workqueue.h>

#define UX500_PLATFORM_MIN_RATE_PLAYBACK 8000
#define UX500_PLATFORM_MAX_RATE_PLAYBACK 48000
#define UX500_PLATFORM_MIN_RATE_CAPTURE	8000
#define UX500_PLATFORM_MAX_RATE_CAPTURE	48000

#define UX500_PLATFORM_MIN_CHANNELS 1
#define UX500_PLATFORM_MAX_CHANNELS 8

#define UX500_PLATFORM_PERIODS_BYTES_MIN	128
#define UX500_PLATFORM_PERIODS_BYTES_MAX	(64 * PAGE_SIZE)
#define UX500_PLATFORM_PERIODS_MIN		2
#define UX500_PLATFORM_PERIODS_MAX		48
#define UX500_PLATFORM_BUFFER_BYTES_MAX		(2048 * PAGE_SIZE)

int ux500_pcm_register_platform(struct platform_device *pdev);
int ux500_pcm_unregister_platform(struct platform_device *pdev);

#endif
