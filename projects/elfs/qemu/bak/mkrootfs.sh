#!/bin/bash
if [ "$TOOLCHAIN" = "" ]
then
cd ..; . env.sh;cd -
fi
echo $TOOLCHAIN
ROOTFS=rootfs
LIBC=`find $TOOLCHAIN -name libc.so`
LIBDIR=`dirname $LIBC`

function copy_files()
{
	rm -rf $ROOTFS
	tar xf rootfs.tar.gz
	cp -rf $PREFIX/* $ROOTFS/usr/.
	cp -rf $LIBDIR $ROOTFS
	cp -arf ../busybox-*/_install/bin/* $ROOTFS/bin

	return;
}

function clean_files()
{
	rm -rf $ROOTFS/usr/share/gtk-doc
	find rootfs -name \*.a -exec rm -rf {} \;
	find rootfs -name include -exec rm -rf {} \;
	find rootfs -name man -exec rm -rf {} \;

	return;
}

copy_files
clean_files

