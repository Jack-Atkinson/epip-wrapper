#!/bin/bash

set -e

ESDK=${EPIPHANY_HOME}
ELIBS=${ESDK}/tools/host/lib
EINCS=${ESDK}/tools/host/include
ELDF=${ESDK}/bsps/current/legacy.ldf

# Create the binaries directory
mkdir -p bin/

# Build HOST side application
g++ src/main.cpp src/epiphany.cpp -o bin/main.elf -I ${EINCS} -L ${ELIBS} -le-hal

# Build DEVICE side program
e-g++ -O3 -T ${ELDF} src/etest.cpp -o bin/etest.elf -le-lib -ffast-math

# Convert ebinary to SREC file
e-objcopy --srec-forceS3 --output-target srec bin/etest.elf bin/etest.srec