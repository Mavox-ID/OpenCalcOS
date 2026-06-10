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
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    FILE *f_in = fopen("/data/Beep.raw", "rb");
    if (!f_in) {
        printf("Error: Cannot open /data/Beep.raw\n");
        return 1;
    }

    int fb = open("/dev/fb0", O_WRONLY);
    if (fb < 0) {
        printf("Error: Cannot open /dev/fb0\n");
        fclose(f_in);
        return 1;
    }

    size_t screensize = 320 * 240 * 2;
    
    char *buffer = malloc(screensize);
    if (!buffer) {
        printf("Error: Memory allocation failed\n");
        close(fb);
        fclose(f_in);
        return 1;
    }

    size_t read_bytes = fread(buffer, 1, screensize, f_in);
    
    if (read_bytes > 0) {
        write(fb, buffer, read_bytes);
    }

    free(buffer);
    fclose(f_in);
    close(fb);

    getchar();

    return 0;
}

