#!/bin/bash
mkdir elfs
mkdir elfs/packages
cp -f *.sh elfs
cp -f *.ini elfs
cp -rf tools elfs
cp -rf patches elfs

tar czf elfs.tar.gz elfs

