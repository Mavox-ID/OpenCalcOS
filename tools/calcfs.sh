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

NC='\033[0m'
GREEN='\033[0;32m'
RED='\033[0;31m'
set -e
cd ..
echo -e "${GREEN}Done. All in calcfs/bin (busybox + sl)${NC}"
echo -e "${GREEN}Building CalcFS...${NC}"

if [ ! -f calcfs/bin/busybox ]; then
    echo -e "${RED}Error:${NC} ${GREEN}calcfs/bin/busybox${NC} ${RED}not found!${NC}"
    exit 1
fi

echo -e "${GREEN}Cleaning...${NC}"
rm -rf CalcFS.tns
echo -e "${GREEN}Packing TNS...${NC}"
cd calcfs && find . | cpio -o -H newc 2>/dev/null | gzip -9 > ../CalcFS.tns
cd ..
echo -e "${GREEN}Done: CalcFS.tns${NC} ($(du -h CalcFS.tns | cut -f1))"
