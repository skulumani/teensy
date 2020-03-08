#!/bin/bash

# script to download the appropriate version of nanopb for platform (linux or windows)

NANOPB_VERSION=0.4.1
WORK_DIR=$(mktemp -d)

# make sure tmp dir was actually created
if [[ ! -d "$WORK_DIR" ]]; then
    echo "Could not create temp directory"
    exit 1
fi

# delete temp dir
cleanup () {
    rm -rf "$WORK_DIR"
    echo "Deleted temp working directory: $WORK_DIR"
}

set +e
trap cleanup exit

# determine OS
if [[ "$OSTYPE" == "linux-gnu" ]]; then
    NANOPB_RELEASE_URL ='https://jpa.kapsi.fi/nanopb/download/nanopb-'${NANOPB_VERSION}'-linux-x86.tar.gz'
elif [[ "$OSTYPE" == "darwin"* ]]; then
    NANOPB_RELEASE_URL ='https://jpa.kapsi.fi/nanopb/download/nanopb-'${NANOPB_VERSION}'-macosx-x86.tar.gz'
else
    echo "Error: Uknown OS"
    exit
fi
# download the latest release
cd ${WORK_DIR}
wget ${NANOPB_REASE_URL} ${WORK_DIR}
tar -xvf nanopb-*.tar.gz

# extract to tools directory
# need generator-bin directory
