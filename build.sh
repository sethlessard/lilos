#!/bin/bash

# build the kernel
echo
echo "========================================="
echo "Building the Kernel"
echo "========================================="
echo
make

# build libc
echo
echo
echo "========================================="
echo "Building user-land libc"
echo "========================================="
echo
pushd libc
make
popd

echo
echo
echo "========================================="
echo "Building the ISO"
echo "========================================="
echo
make boot.iso
