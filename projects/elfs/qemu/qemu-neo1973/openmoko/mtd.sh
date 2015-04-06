if [ `id -u` != 0 ] ; then
    echo "run this as root"
    exit
fi
if [ $# -lt 2 ] ; then
    echo $0 image.jffs2 directory
    exit
fi
LOOPDEV=`losetup -f`
losetup $LOOPDEV $1
modprobe block2mtd block2mtd=$LOOPDEV,131072
modprobe jffs2
modprobe mtdblock
sleep 1
[ -d $2 ] || mkdir $2
mount -t jffs2  /dev/mtdblock0 $2
