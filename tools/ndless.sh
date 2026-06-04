#!/bin/bash
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
        (cd ndless/ndless-sdk/toolchain && rm -rf .built_* download install && ./toolchain.sh)
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

echo -e "${GREEN}Done.${NC} ${YELLOW}Installer: ndless/ndless/calcbin/${NC}"
echo -e "${GREEN}Choose version${NC}   ${YELLOW}>>>>>>>>>>>>>>>>>>>>>>${NC}"
