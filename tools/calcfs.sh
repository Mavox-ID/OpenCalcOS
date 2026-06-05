#!/bin/bash

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
