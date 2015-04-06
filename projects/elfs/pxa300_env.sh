unset TOOLCHAIN_PREFIX
export BOARD_NAME=pxa300
export TOOLCHAIN=/usr/local/arm-linux-4.1.1

. env.sh arm $1
export CFLAGS=$CFLAGS" -mcpu=xscale -fno-strict-aliasing" 
