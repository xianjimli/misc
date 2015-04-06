export ARCH=$1
export GDK_TARGET=$2

if [ "$ARCH" = "" ]
then
	export ARCH=arm
	echo "set default arch to arm"
fi

case "$GDK_TARGET" in
	x11) export GDK_TARGET=x11;;
	directfb) export GDK_TARGET=directfb;;
	*) export GDK_TARGET=x11;;
esac

export BUILD_DIR=$PWD/$ARCH/$BOARD_NAME
export PREFIX=$BUILD_DIR/usr
export PKG_CONFIG_PATH=$PREFIX/lib/pkgconfig/
export LDFLAGS="-L$PREFIX/lib"
export CFLAGS="-I$PREFIX/include"
export PATH=$PWD/patches/bin:$PATH

if [ "$ARCH" = "i386" ]
then
	unset HOST_PARAM
	unset TARGET_PLATFORM
	unset WITH_ARCH
	export LD_LIBRARY_PATH=$PREFIX/lib
else
	if [ "$TOOLCHAIN_PREFIX" = "" ]
	then
		export HOST_PARAM=--host=$ARCH-linux
		export TARGET_PLATFORM=$ARCH-linux-
	else
		export HOST_PARAM=--host=$TOOLCHAIN_PREFIX
		export TARGET_PLATFORM=$TOOLCHAIN_PREFIX-
	fi	
	export WITH_ARCH=--with-arch=$ARCH-linux
	export PATH=$TOOLCHAIN/bin:$PATH
fi
export TARGET_CC="$TARGET_PLATFORM"gcc

rm -f pkg-all.ini
./tools/elfs-merger pkg-all.ini pkg-$GDK_TARGET.ini pkg-$ARCH.ini pkg-$BOARD_NAME.ini pkg-$BOARD_NAME-$GDK_TARGET.ini
tools/elfs-gen pkg-all.ini >Makefile.$BOARD_NAME.$GDK_TARGET

echo "=================================================================="
echo "exported the following vars:"
echo "=================================================================="
echo "ARCH=$ARCH"
echo "GDK_TARGET="$GDK_TARGET
echo "WITH_ARCH=$WITH_ARCH"
echo "HOST_PARAM=$HOST_PARAM"
echo "TARGET_CC=$TARGET_CC"
echo "TARGET_PLATFORM=$TARGET_PLATFORM"
echo "PREFIX=$PREFIX"
echo "CFLAGS=$CFLAGS"
echo "LDFLAGS=$LDFLAGS"
echo "PKG_CONFIG_PATH=$PKG_CONFIG_PATH"
echo "PATH=$PATH"
echo "=================================================================="
echo "to build:"
echo "make -f Makefile.$BOARD_NAME.$GDK_TARGET all"
echo "=================================================================="
