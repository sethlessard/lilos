#!/bin/bash

# build the kernel
make

# build libc
pushd libc
make
popd

# build the iso
make boot.iso
