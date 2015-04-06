modprobe uinput
modprobe memfb
mknod /dev/uinput c 10 223
./vlcd
