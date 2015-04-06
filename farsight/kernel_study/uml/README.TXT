试玩UML(User Mode Linux)

这里的UML并非指统一建模语言，而指用户模式的linux。顾名思义，就是让linux系统作为一个用户进程运行。为什么要这样做呢？大家都知道调试linux 内核是件麻烦的事情，虽然可以使用kdb、gdb或者虚拟机来调试内核，但这些本身方法都有一些限制，而且我总感觉使用很麻烦，几次尝试失败后，没有再去调试过linux内核。

Linux内核对调试支持力度不够，并非是因为实现起来很困难，而是因为他们认为调试器有害软件的健康。这是有道理的，软件的质量是认认真真的设计出来的，扎扎实实的写出来的，而不是靠辛辛苦苦调试出来的。使用调试器常常导致一种不彻底的BUG修改，治标不治本，让BUG长时间潜伏在代码中，从长远利害关系来看，它会造成更严重的损害。

调试器只是一种工具，用得好不好或者恰不恰当，是我们自己的事，不能因为自己的过错而责怪工具。实际上，调试器对于我们研究内核代码，是很有帮助，运行内核代码的，观察它的效果，远远比只看代码印象更深刻。

UML为研究linux内核代码提供一种便利的方式，整个linux系统完全是一个用户进程，你可以像调试普通用户进程一样调试它。UML的实现也比较巧妙，linux内核把不同平台称之一个ARCH(architectur)，每个ARCH实现依赖于特定硬件平台的功能，UML作为一个ARCH来实现，用软件模拟了硬件功能。

Linux内核2.6以及后续版本已经集成了UML，但我试了几个版本都编译不过去，直到在linux-2.6.16上尝试才成功。使用UML要先选择一个好的内核版本，否则会浪费不少时间。使用UML的具体过程如下：

1. 解开内核源码包。
[root@localhost src]# tar zxvf /mnt/hgfs/linux/linux-2.6.16.tar.gz

2. 编译内核。
[root@localhost linux-2.6.16]# make ARCH=um defconfig
[root@localhost linux-2.6.16]# make ARCH=um menuconfig
[root@localhost linux-2.6.16]# make ARCH=um


3. 安装内核。
[root@localhost linux-2.6.16]# cp linux /usr/local/bin/

4. 制作根文件系统。
[root@localhost cvs]# dd if=/dev/zero of=root_fs seek=500 count=1 bs=1M
[root@localhost um]# mkfs.ext2 ./root_fs
[root@localhost um]# mkdir /mnt/rootfs
[root@localhost um]# mount -o loop root_fs /mnt/rootfs/

(拷贝你需要的文件：因为只是研究内核，拷贝一些基本的运行库、可执行文件和配置文件就行了)

[root@localhost um]# umount /mnt/rootfs/

网上有很多制作好的根文件系统，如果目的只是研究内核，从网上下载根文件系统最方便的选择。

5. 制作交换分区
[root@localhost um]# dd if=/dev/zero of=swap_fs seek=500 count=1 bs=1M
[root@localhost um]# mkswap ./swap_fs

6. 正常运行。
[root@localhost um]# linux ubd0=root_fs ubd1=swap_fs

7. 调试运行。
gdb linux
(gdb) b start_kernel
(gdb) r ubd0=root_fs ubd1=swap_fs
