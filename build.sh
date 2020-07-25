#!/bin/bash

# build the kernel
make
make boot.iso

# build libc
pushd libc
make
popd
