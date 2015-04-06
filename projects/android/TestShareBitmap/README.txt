基于共享内存的Bitmap使用方法：

1.把extra/frameworks.tar.gz解开，里面有两个文件：
./frameworks/base/core/jni/android/graphics/Bitmap.cpp
./frameworks/base/graphics/java/android/graphics/Bitmap.java

这两个文件在原有的Bitmap上实现了基于共享内存的Bitmap，让位于两个进程内的Bitmap共享同一块内存区域。用这两个文件替换android中原来的文件，然后重新编译。

2.调用方法如下：

o 创建一个内存文件（完整代码请参考：ShareBitmapService.java）：
  mMemoryFile = new MemoryFile(mFileName, mSize);

  mFileName没有特别的规定，取一个有意义的名字即可。
  mSize是Bitmap所需的内存的大小。可以这样计算:width * height * bpp + 16。

o 创建基于共享内存的Bitmap（完整代码请参考：ShareBitmapService.java）：
  FileDescriptor fd = mMemoryFile.getFileDescriptor();
  mBitmap = Bitmap.createShareBitmap(fd, mSize, mWidth, mHeight, Bitmap.Config.ARGB_8888);

  mSize和前面的mSize是一样的。

o 提供一个Service让另外一个进程能够获得内存文件的文件描述符（完整代码请参考：ShareBitmapService.java）：

        public  ParcelFileDescriptor getShareBitmap(){
            try {
                return mMemoryFile.getParcelFileDescriptor();
            }
            catch(IOException ex){
                Log.i(TAG, ex.toString());
            }

            return null;
        }

o 在客户端创建基于共享内存的Bitmap（完整代码请参考：ClientActivity.java):

        ParcelFileDescriptor pFd = mShareBitmapService.getShareBitmap();
        FileDescriptor fd = pFd.getFileDescriptor();
        mBitmap = Bitmap.createShareBitmap(fd, mSize, 0, 0, Bitmap.Config.ARGB_8888);

 mSize和前面的保持一致，在实际使用时，最好从服务端获取。Bitmap创建一次即可，两个Bitmap共享的同一块内存区域，对一个Bitmap的更新会实时反应到另个一个Bitmap上。


