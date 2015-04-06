#!/bin/bash
export PATH=/sbin:$PATH
modprobe mtdram total_size=40189952
modprobe mtdchar
dd if=openmoko-image-fic-gta01.org.jffs2 of=/dev/mtd0
modprobe mtdblock
modprobe jffs2
mount -t jffs2 /dev/mtdblock0 /mnt/jffs2
