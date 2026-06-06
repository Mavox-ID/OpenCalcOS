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
set -e

YELLOW='\033[1;33m'
GREEN='\033[0;32m'
NC='\033[0m'
cd ..
echo -e "${YELLOW}Cleaning Ndless...${NC}"
(cd ndless && make clean > /dev/null 2>&1 && cd ndless && make clean > /dev/null 2>&1 && cd ../ndless-sdk && make clean > /dev/null 2>&1 && cd ../..)

echo -e "${YELLOW}Cleaning Ncurses...${NC}"
if [ -d "ndless/ncurses" ] && [ -f "ndless/ncurses/Makefile" ]; then
    (cd ndless/ncurses && make distclean > /dev/null 2>&1 && rm -rf dest && cd ..)
fi

echo -e "${YELLOW}Cleaning Kernel...${NC}"
(cd kernel && make clean && cd ..)

echo -e "${YELLOW}Cleaning Busybox...${NC}"
(cd busybox && make clean && cd ..)

echo -e "${YELLOW}Cleaning Nano...${NC}"
if [ -d "nano" ] && [ -f "nano/Makefile" ]; then
    (cd nano && make distclean > /dev/null 2>&1 && cd ..)
fi

echo -e "${YELLOW}Cleaning Loader...${NC}"
(cd loader && make clean > /dev/null 2>&1 && cd ..)

echo -e "${YELLOW}Clean build...${NC}"
if [ -d "build" ]; then
    rm -rf "build"
fi
if [ -f "zCalc.tns" ]; then
    rm "zCalc.tns"
fi
if [ -f "Loader.tns" ]; then
    rm "Loader.tns"
fi
if [ -f "CalcFS.tns" ]; then
    rm "CalcFS.tns"
fi
if [ -f "calcfs/bin/nano" ]; then
    rm "calcfs/bin/nano"
fi
if [ -f "calcfs/libs/libncurses.a" ]; then
    rm "calcfs/libs/libncurses.a"
fi
if [ -f "calcfs/libs/libform.a" ]; then
    rm "calcfs/libs/libform.a"
fi
if [ -f "calcfs/libs/libpanel.a" ]; then
    rm "calcfs/libs/libpanel.a"
fi
if [ -f "calcfs/libs/libmenu.a" ]; then
    rm "calcfs/libs/libmenu.a"
fi

echo -e "${GREEN}Done.${NC}"
