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

set -e && cd ..
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m'
TOOLCHAIN_BIN="ndless/ndless-sdk/toolchain/install/bin"
COMPILER_CHECK="$TOOLCHAIN_BIN/arm-none-eabi-gcc"

echo -e "${GREEN}Cleaning Ndless SDK...${NC}"
(cd ndless/ndless-sdk && make clean > /dev/null 2>&1 && cd ../..)

echo -e "${GREEN}Cleaning Ndless...${NC}"
(cd ndless && make -C ndless clean > /dev/null 2>&1 && rm -rf ndless/ndless/calcbin/* && cd ../..)

echo -e "${GREEN}Building toolchain...${NC}"
if [ -f "$COMPILER_CHECK" ]; then
    echo -e "${GREEN}Toolchain already compiled. Skip${NC}"
else
    echo -e "${YELLOW}Toolchain not found.${NC} ${GREEN}Building${NC}"
    
    if ! (
	export CXXFLAGS="$CXXFLAGS -fno-char8_t"
	export CFLAGS="$CFLAGS -fno-char8_t"
        (cd ndless/ndless-sdk/toolchain && rm -rf .built_* install && ./toolchain.sh)
    ); then
        echo -e "${RED}Error: Toolchain compilation failed!${NC}"
        exit 1
    fi
    
    if [ ! -f "$COMPILER_CHECK" ]; then
        echo -e "${RED}Error: Compiler file is missing!${NC}"
        exit 1
    fi
fi

export PATH="$(pwd)/ndless/ndless-sdk/toolchain/install/bin:$(pwd)/ndless/ndless-sdk/bin:$PATH"
echo -e "${GREEN}Toolchain PATH added to terminal${NC}"

echo -e "${GREEN}Building luna...${NC}"
(cd ndless/ndless-sdk/tools/luna && make -j"$(nproc)" && cd ../../../..)

echo -e "${GREEN}Building SDK...${NC}"
(cd ndless/ndless-sdk && make -j"$(nproc)" && cd ../..)

echo -e "${GREEN}Building libc...${NC}"
(cd ndless/ndless-sdk && make -j"$(nproc)" build-libsyscalls && make -j"$(nproc)" build-libsyscalls && cd ../..)

echo -e "${GREEN}Building Ndless...${NC}"
(cd ndless && make -j"$(nproc)" -C ndless && cd ..)

echo -e "${GREEN}Building ncurses...${NC}"
(
    cd ndless/ncurses
    ABS_DEST="$(pwd)/dest"

    if [ ! -f Makefile ]; then
        export CC=arm-linux-gnueabi-gcc
        export CXX=arm-linux-gnueabi-g++
        export AR=arm-linux-gnueabi-ar
        export RANLIB=arm-linux-gnueabi-ranlib
        export LDFLAGS="-Wl,-rpath,/libs -Wl,-dynamic-linker,/libs/ld-linux-armhf.so.3"

        ./configure \
            --host=arm-linux-gnueabi \
            --prefix="$ABS_DEST" \
            --libdir="$ABS_DEST/libs" \
            --with-shared \
            --without-debug \
            --without-ada \
            --without-tests \
            --disable-stripping
    fi
    
    make -j"$(nproc)"
    make install.libs install.includes install.progs
    
    echo -e "${GREEN}Deploying ncurses libraries...${NC}"
    cp -d "$ABS_DEST/libs/"lib*.so* ../../calcfs/libs/
    cp -d "$ABS_DEST/libs/"lib*.a ../../calcfs/libs/

    echo -e "${GREEN}Deploying system dependencies (libc, ld-linux)...${NC}"
    cp -L $(arm-linux-gnueabi-gcc -print-file-name=ld-linux-armhf.so.3) ../../calcfs/libs/ld-linux-armhf.so.3
    cp -L $(arm-linux-gnueabi-gcc -print-file-name=libc.so.6) ../../calcfs/libs/libc.so.6
    
    echo -e "${GREEN}Deploying cterm and gterm...${NC}"
    cp "$ABS_DEST/bin/tic" ../../calcfs/bin/cterm
    cp "$ABS_DEST/bin/infocmp" ../../calcfs/bin/gterm
    echo -e "${GREEN}Ncurses done. All in $ABS_DEST${NC}"
)

echo -e "${GREEN}Done.${NC} ${YELLOW}Installer: ndless/ndless/calcbin/${NC}"
echo -e "${GREEN}Choose version${NC}   ${YELLOW}>>>>>>>>>>>>>>>>>>>>>>${NC}"
