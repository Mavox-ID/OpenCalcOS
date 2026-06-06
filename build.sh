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

set -Eeuo pipefail

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

CURRENT_STEP="startup"
ROOT_DIR="$(pwd)"

trap 'echo -e "\n${RED}Error:${NC} Step: ${YELLOW}${CURRENT_STEP}${NC} failed (line $LINENO)"; exit 1' ERR

step() {
    CURRENT_STEP="$1"
    echo -e "\n${GREEN}==>${NC} $CURRENT_STEP"
}

step "Preparation to build"
cd tools
echo -e "${GREEN}Done.${NC}"

export PATH="$ROOT_DIR/ndless/ndless-sdk/toolchain/install/bin:$ROOT_DIR/ndless/ndless-sdk/bin:$PATH"

step "Cleaning all"
bash clean.sh

step "Building Ndless"
bash ndless.sh

step "Building Kernel"
bash kernel.sh

step "Building Busybox"
bash busybox.sh

step "Building CalcFS"
bash calcfs.sh

step "Building Loader"
bash loader.sh

step "Commit"

cd ..
mkdir -p build
echo -e "${GREEN}Starting commit...${NC}"
mv zCalc.tns build/zCalc.tns
echo -e "${GREEN}Moved zCalc${NC}"
mv CalcFS.tns build/CalcFS.tns
echo -e "${GREEN}Moved CalcFS${NC}"
cp -r ndless/ndless/calcbin build/NDless
echo -e "${GREEN}Copyed NDless${NC}"
mv Loader.tns build/Loader.tns
echo -e "${GREEN}Moved Loader${NC}"
echo -e "\n${GREEN}Done. All in build folder${NC}"
