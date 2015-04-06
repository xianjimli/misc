echo "Creating 1GB file of zeros in $1.raw"
dd if=/dev/zero of=$1.raw bs=1024 count=1048576

echo "Formating $1.raw with ext3 filesystem"
/sbin/parted $1.raw mklabel msdos
/sbin/parted $1.raw mkpart primary ext2 0 954
/sbin/parted $1.raw mkpart extended 954 1069
/sbin/parted $1.raw mkpart logical linux-swap 954 1069
/sbin/parted $1.raw set 1 boot on
/sbin/parted $1.raw mkfs 1 ext3

echo "Mounting $1.raw on $1.mount"
mkdir -p $1.mount
mount -o loop,offset=16384 -t ext3 $1.raw $1.mount

echo "Installing Etch into $1.mount"
/usr/sbin/debootstrap --arch i386 etch $1.mount http://ftp.us.debian.org/debian

echo "Setting up host networking in $1.mount for apt"
cp /etc/resolv.conf $1.mount/etc
cp /etc/hosts $1.mount/etc

echo "Installing kernel and grub into $1.mount"
#/usr/sbin/chroot $1.mount apt-get update
#/usr/sbin/chroot $1.mount apt-get -y install linux-image-2.6-486 grub
#/sbin/grub-install --root-directory=$1.mount/root $1.raw

