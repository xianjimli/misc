#!/bin/bash

ROOTFS_DIR=rootfs
ELFS_ROOT=$(echo $PWD|sed -e "s/qemu\/qemu-neo1973\/openmoko//g")
BUILD_ROOT=$ELFS_ROOT/arm/openmoko
echo "ELFS_ROOT:$ELFS_ROOT"
echo "BUILD_ROOT:$BUILD_ROOT"

if [ ! -d $ROOTFS_DIR ]
then 
	tar xfv rootfs.tar.gz
fi

function fix_files()
{
	mkdir -p $ROOTFS_DIR/$BUILD_ROOT
	ln -s /usr $ROOTFS_DIR/$BUILD_ROOT
	sed -e "s/<dir>\/usr\/share\/fonts<\/dir>/<dir>\/usr\/share\/fonts<\/dir><dir>\/usr\/share\/X11\/fonts<\/dir>/g" $ROOTFS_DIR/usr/etc/fonts/fonts.conf>$ROOTFS_DIR/usr/etc/fonts/fonts.conf.new
	mv $ROOTFS_DIR/usr/etc/fonts/fonts.conf.new $ROOTFS_DIR/usr/etc/fonts/fonts.conf
}

function clean_files()
{
	rm -rf $ROOTFS_DIR/usr/share/gtk-doc
	rm -rf $ROOTFS_DIR/usr/share/doc
	find $ROOTFS_DIR/usr/ -name \*.a -exec rm -rf {} \;
	find $ROOTFS_DIR/usr/ -name include -exec rm -rf {} \;
	find $ROOTFS_DIR/usr/ -name man -exec rm -rf {} \;
	find $ROOTFS_DIR/usr/ -name info -exec rm -rf {} \;

	for f in $ROOTFS_DIR/usr/share/locale/*;
	do
		if [ ! "$f" = "$ROOTFS_DIR/usr/share/locale/zh_CN" ]
		then
			rm -rf $f
		fi
	done

	return;
}

function create_rcs()
{
	echo "#!/bin/sh"
	echo export DISPLAY=:0
	echo export PATH=/sbin:/bin:/usr/sbin:/usr/bin
	echo export TSLIB_TSDEVICE=/dev/input/event1
	echo export TSLIB_CONFFIL=/usr/etc/ts.conf
	echo export TSLIB_PLUGINDIR=/usr/lib/ts
	echo ifconfig usb0 192.168.0.202
	echo ifconfig usb0
	echo /usr/bin/ts_calibrate
	echo mkdir /usr/etc/pango
	echo "gdk-pixbuf-query-loaders >/usr/etc/gtk-2.0/gdk-pixbuf.loaders"
	echo "pango-querymodules >/usr/etc/pango/pango.modules"

	echo fc-cache
	echo fc-list
	if [ -e rootfs/usr/bin/Xfbdev ]
	then
		echo "/usr/bin/Xfbdev -mouse tslib &"
		echo sleep 3
		echo "/usr/bin/matchbox-window-manager &"
		echo "/usr/bin/matchbox-desktop &"
	fi

	echo "/usr/bin/gtk-demo &"
}

if [ ! -e $ROOTFS_DIR/usr/bin/ts_test ]
then 
	echo "copy files"
	mkdir $ROOTFS_DIR/usr
	echo cp -rf $BUILD_ROOT/usr/* $ROOTFS_DIR/usr/.
	cp -rf $BUILD_ROOT/usr/* $ROOTFS_DIR/usr/.
	clean_files
	fix_files
	create_rcs >rootfs/etc/init.d/rcS
	chmod 775 rootfs/etc/init.d/rcS
fi

	create_rcs >rootfs/etc/init.d/rcS
	chmod 775 rootfs/etc/init.d/rcS
if [ ! -f rootfs.jffs2 ]
then
	echo "make rootfs.jffs2"
	mkfs.jffs2  -d rootfs -o rootfs.jffs2 --eraseblock=0x4000 --pad=0x2800000
fi

