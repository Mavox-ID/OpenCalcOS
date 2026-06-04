#!/bin/bash

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
set -e && cd .. && echo -e "${YELLOW}set's error logs${NC}"
echo -e "${GREEN}Cleaning build...${NC}"
cd kernel && make clean
echo -e "${GREEN}Building kernel...${NC}"
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-
echo -e "${GREEN}Exported ARCH && CROSS${NC}"
make -j$(nproc) zCalc
echo -e "${GREEN}Maked zCalc${NC}"
cp arch/arm/boot/zCalc ../zCalc.tns && cd ..
echo -e "${GREEN}Done: zCalc.tns${NC} ($(du -h zCalc.tns | cut -f1))"
