#!/bin/bash

# build libc
pushd libc
make
popd

# build the kernel
make
make boot.iso
