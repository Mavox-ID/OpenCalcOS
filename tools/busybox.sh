#!/usr/bin/env bash
cd ..
set -euo pipefail

cd busybox && make clean && make -j"$(nproc)"
rm -rf ../calcfs/bin && mkdir ../calcfs/bin
cp busybox ../calcfs/bin/busybox
pwd
cd ../calcfs/bin && ./busybox --install -s . && cd ../..
pwd
NC='\033[0m'
GREEN='\033[0;32m'
echo -e "${GREEN}Done. All in calcfs/bin (busybox + sl)${NC}"
