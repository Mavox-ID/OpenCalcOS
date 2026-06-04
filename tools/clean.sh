#!/bin/bash
set -e

YELLOW='\033[1;33m'
GREEN='\033[0;32m'
NC='\033[0m'
cd ..
echo -e "${YELLOW}Cleaning Ndless...${NC}"
(cd ndless && make clean > /dev/null 2>&1 && cd ..)

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

echo -e "${GREEN}Done.${NC}"
