#!/bin/bash
# download ARM compiler

# ARM compiler downloaded from here
# https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads

# TODO Instead automatically download and install arduino and teensyduino, then copy the tools over to this directory

WORK_DIR="$(pwd)"
TEMP_DIR="$(mktemp -d)"
INSTALL_DIR="$(pwd)/tools/compiler"

# setup temp dir
echo "This will download the ARM Toolchain and copy to tools/compiler"
read -p "Press Enter to continue"

if [[ ! "$TEMP_DIR" || ! -d "$TEMP_DIR" ]]; then
    echo "Could not create temp dir"
    exit 1
fi

function cleanup () {
    rm -rf "$TEMP_DIR"
    echo "Deleted temp working directory $TEMP_DIR"
}

trap cleanup exit

# download ARM compiler
echo "Downloading ARM tools"
cd ${TEMP_DIR}
mkdir gcc_arm

# logic for OS type
wget ${LINUX_URL} -O ${TEMP_DIR}/gcc_arm.tar.bz2
if ! echo "${LINUX_HASH} gcc_arm.tar.bz2" | md5sum -c; then
    echo "Invalid hash! Aborting"
    exit 1
fi

tar -xjf gcc_arm.tar.bz2 -C ./gcc_arm --strip-components=1

# move to local directory
echo "Now we'll copy the compiler to the local directory"

cd ${WORK_DIR}
cp -r ${TEMP_DIR}/gcc_arm/* ${INSTALL_DIR}

echo "Finished"

# build teensy_loader_cli
