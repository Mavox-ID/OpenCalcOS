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

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
set -e && cd ..
export PATH="$(pwd)/ndless/ndless-sdk/toolchain/install/bin:$PATH"
echo -e "${GREEN}Cleaning build...${NC}"
cd kernel && make clean && rm -rf arch/arm/boot/Calc arch/arm/boot/zCalc arch/arm/boot/compressed/vmbeep
echo -e "${GREEN}Building kernel...${NC}"
export ARCH=arm
export CROSS_COMPILE=arm-none-eabi-
echo -e "${GREEN}Exported ARCH && CROSS${NC}"
make -j"$(nproc)" KCFLAGS="-w" zCalc

echo -e "${GREEN}Building progs...${NC}"
mkdir -p prog/build
cd ../tools && bash prog.sh && cd ../kernel

echo -e "${GREEN}Maked zCalc${NC}"
cp arch/arm/boot/zCalc ../zCalc.tns && cd ..
echo -e "${GREEN}Done: zCalc.tns${NC} ($(du -h zCalc.tns | cut -f1))"
