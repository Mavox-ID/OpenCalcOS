#!/usr/bin/env bash
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
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BEEP_BIN_DIR="$PROJECT_ROOT/.local_bin"

export PATH="$BEEP_BIN_DIR:$PATH"
KERNEL_INC="$PROJECT_ROOT/kernel/include"
cd "$PROJECT_ROOT"

cd busybox && make clean
export CFLAGS="-isystem $KERNEL_INC -w"
export CPPFLAGS="-isystem $KERNEL_INC -w"

make -j"$(nproc)" CROSS_COMPILE=arm-beep-gnueabi- \
    CONFIG_EXTRA_LDLIBS="crypt" \
    CONFIG_EXTRA_LDFLAGS="-Wl,--no-warnings"

cp busybox ../calcfs/bin/busybox
cd ../calcfs/bin && ./busybox --install -s . && cd ../..

echo -e "\033[1;33mBuilding nano...\033[0m"
(
    cd busybox/nano
    if [ -f autogen.sh ]; then
        ./autogen.sh
    else
        autoreconf -vfi
    fi
    export PATH="$PROJECT_ROOT/.local_bin:$PATH"
    
    CC=arm-beep-gnueabi-gcc \
    CFLAGS="-I$(pwd)/../../ndless/ncurses/dest/include -I$(pwd)/../../ndless/ncurses/dest/include/ncurses -w -Os -ffunction-sections -fdata-sections" \
    CPPFLAGS="-I$(pwd)/../../ndless/ncurses/dest/include -I$(pwd)/../../ndless/ncurses/dest/include/ncurses -w -Os -ffunction-sections -fdata-sections" \
    ./configure \
        --build=x86_64-linux-gnu \
        --host=arm-linux-gnueabi \
        --prefix=/ \
        --bindir=/bin \
        --sysconfdir=/conf \
        --disable-nls \
        --disable-libmagic \
        --disable-utf8 \
        --disable-browser \
        --disable-help \
        --disable-histories \
        --disable-justify \
        --disable-operating-dir \
        --disable-speller \
        --disable-syntax \
        --disable-tabcomp \
        --disable-wordcomp \
        --disable-comment \
        --disable-extra \
        --disable-color

    make -j"$(nproc)" \
        LDFLAGS="-L$(pwd)/../../ndless/ncurses/dest/libs -Wl,-rpath,/libs -Wl,-dynamic-linker=/libs/ld-beep-armhf.so.3 -Wl,--no-warnings -Wl,--gc-sections" \
        LIBS="-lncurses"
    
    cp src/nano ../../calcfs/bin/nano
    arm-beep-gnueabi-strip --strip-all ../../calcfs/bin/nano
)

NC='\033[0m'
GREEN='\033[0;32m'
echo -e "${GREEN}Done. All in calcfs/bin (busybox + sl + nano)${NC}"
