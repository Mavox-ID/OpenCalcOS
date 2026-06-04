#!/bin/bash

NC='\033[0m'
GREEN='\033[0;32m'
RED='\033[0;31m'
set -e
cd ..
echo -e "${GREEN}Done. All in rootfs/bin (busybox + sl)${NC}"
echo -e "${GREEN}Building CalcFS...${NC}"

if [ ! -f calcfs/bin/busybox ]; then
    echo -e "${RED}Error:${NC} ${GREEN}calcfs/bin/busybox${NC} ${RED}not found!${NC}"
    exit 1
fi

echo -e "${GREEN}Cleaning...${NC}"
rm -rf calcfs.tns
echo -e "${GREEN}Packing TNS...${NC}"
cd calcfs && find . | cpio -o -H newc 2>/dev/null | gzip -9 > ../calcfs.tns
cd ..
echo -e "${GREEN}Done: calcfs.tns${NC} ($(du -h calcfs.tns | cut -f1))"
