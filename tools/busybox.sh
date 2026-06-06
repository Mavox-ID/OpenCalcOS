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

cd ..
set -euo pipefail

cd busybox && make clean && make -j"$(nproc)"
rm -rf ../calcfs/bin && mkdir ../calcfs/bin
cp busybox ../calcfs/bin/busybox
cd ../calcfs/bin && ./busybox --install -s . && cd ../..

echo -e "\033[1;33mBuilding nano...\033[0m"
(
    cd busybox/nano
    if [ ! -f configure ]; then
        ./autogen.sh
    fi
    
    CC=arm-linux-gnueabi-gcc \
    CFLAGS="-I$(pwd)/../../ndless/ncurses/dest/include -I$(pwd)/../../ndless/ncurses/dest/include/ncurses" \
    CPPFLAGS="-I$(pwd)/../../ndless/ncurses/dest/include -I$(pwd)/../../ndless/ncurses/dest/include/ncurses" \
    ./configure \
        --host=arm-linux-gnueabi \
        --prefix=/ \
        --bindir=/bin \
        --sysconfdir=/conf \
        --disable-nls \
        --disable-libmagic \
        --disable-utf8 \
        --with-ncurses

    make -j"$(nproc)" \
        LDFLAGS="-L$(pwd)/../../ndless/ncurses/dest/libs -Wl,-rpath,/libs -Wl,-dynamic-linker=/libs/ld-linux-armhf.so.3" \
        LIBS="-lncurses"
    
    cp src/nano ../../calcfs/bin/nano
)

NC='\033[0m'
GREEN='\033[0;32m'
echo -e "${GREEN}Done. All in calcfs/bin (busybox + sl + nano)${NC}"
