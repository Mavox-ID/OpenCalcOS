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
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

__asm__(
    ".section .rodata\n"
    ".global beep_raw_start\n"
    "beep_raw_start:\n"
    ".incbin \"Beep.raw\"\n"
    "beep_raw_end:\n"
);

extern const char beep_raw_start[];

int main(void) {
    int fb = open("/dev/fb0", O_WRONLY);
    if (fb < 0) {
        printf("Error: Cannot open /dev/fb0\n");
        return 1;
    }

    printf("\e[?25l");
    fflush(stdout);

    size_t screensize = 320 * 240 * 2; // 153600b
    lseek(fb, 0, SEEK_SET);
    write(fb, beep_raw_start, screensize);

    close(fb);
    getchar();
    printf("\e[?25h");
    fflush(stdout);

    return 0;
}
