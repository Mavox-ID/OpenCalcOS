#!/bin/bash

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'
set -e
cd .. && cd loader
echo -e "${GREEN}Building Loader...${NC}"
echo -e "${GREEN}Cleaning...${NC}"
(make clean)
echo -e "${GREEN}Building TNS...${NC}"
(make -j"$(nproc)" && cp loader.tns ../loader.tns)
pwd
echo -e "${GREEN}Done:${NC} ${YELLOW}loader.tns${NC}"
