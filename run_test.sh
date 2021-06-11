#!/bin/bash
RED='\033[0;31m'
NC='\033[0m'

cmake -S . -B build
if [ $? -eq 0 ]; then
    echo OK
else
    printf "${RED}Build Failed${NC}\n"
    exit 1
fi
cmake --build build
if [ $? -eq 0 ]; then
    echo OK
else
    printf "${RED}Build Failed${NC}\n"
    exit 1
fi
cd build && ctest