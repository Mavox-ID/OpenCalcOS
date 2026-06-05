#!/bin/bash
set -e

YELLOW='\033[1;33m'
GREEN='\033[0;32m'
NC='\033[0m'
cd ..
echo -e "${YELLOW}Cleaning Ndless...${NC}"
(cd ndless && make clean > /dev/null 2>&1 && cd ndless && make clean > /dev/null 2>&1 && cd ../ndless-sdk && make clean > /dev/null 2>&1 && cd ../..)

echo -e "${YELLOW}Cleaning Kernel...${NC}"
(cd kernel && make clean && cd ..)

echo -e "${YELLOW}Cleaning Busybox...${NC}"
(cd busybox && make clean && cd ..)

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

echo -e "${GREEN}Done.${NC}"
