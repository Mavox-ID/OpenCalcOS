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
#ifndef _BEEP_VIRTIO_CONSOLE_H
#define _BEEP_VIRTIO_CONSOLE_H

#include <uapi/beep/virtio_console.h>

int __init virtio_cons_early_init(int (*put_chars)(u32, const char *, int));
#endif /* _BEEP_VIRTIO_CONSOLE_H */
