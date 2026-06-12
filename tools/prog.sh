#!/bin/bash
#    Mavox-ID | https://ye-a.pp.ua
#    Copyright (C) 2026  Mavox-ID
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

set -e && cd ../kernel
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BEEP_BIN_DIR="$PROJECT_ROOT/.local_bin"
unset CROSS_COMPILE
unset ARCH
export PATH="$BEEP_BIN_DIR:/usr/bin:/bin:/usr/sbin:/sbin"

echo -e "${YELLOW}Starting Beep...${NC}"
arm-beep-gnueabi-gcc -Os -marm prog/beep.c -o prog/build/beep \
    -Wl,-dynamic-linker=/libs/ld-beep-armhf.so.3 -Wl,-rpath,/libs
arm-beep-gnueabi-strip --strip-all prog/build/beep
cp prog/build/beep ../calcfs/bin/beep
chmod +x ../calcfs/bin/beep
echo -e "${GREEN}Done beep programm in${NC} ${YELLOW}calcfs/bin/beep${NC}"

echo -e "${YELLOW}Starting Calc...${NC}"
arm-beep-gnueabi-gcc -Os -marm -I../ndless/ncurses/dest/include -I../ndless/ncurses/dest/include/ncurses \
prog/calc.c -o prog/build/calc \
-L../ndless/ncurses/dest/libs -lncurses -lm \
-Wl,-dynamic-linker=/libs/ld-beep-armhf.so.3 -Wl,-rpath,/libs
arm-beep-gnueabi-strip --strip-all prog/build/calc
cp prog/build/calc ../calcfs/bin/calc
chmod +x ../calcfs/bin/calc
echo -e "${GREEN}Done calc programm in${NC} ${YELLOW}calcfs/bin/calc${NC}"

echo -e "${YELLOW}Starting Pipes...${NC}"
cp prog/pipes ../calcfs/bin/pipes
chmod +x ../calcfs/bin/pipes
echo -e "${GREEN}Done pipes programm in${NC} ${YELLOW}calcfs/bin/pipes${NC}"
