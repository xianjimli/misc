package com.lxj;

import android.util.Log;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Process;
import java.io.IOException;
import android.app.Service;
import java.io.InputStream;
import java.io.OutputStream;
import android.widget.Toast;
import android.os.MemoryFile;
import android.content.Intent;
import java.io.FileDescriptor;
import android.os.SystemClock;
import android.graphics.Bitmap;
import android.app.PendingIntent;
import android.os.RemoteException;
import android.graphics.BitmapFactory;
import android.os.ParcelFileDescriptor;

public class ShareBitmapService extends Service {
  
    private Bitmap mBitmap;
    private MemoryFile mMemoryFile;
    private int mColorIndex = 0;
    private static final int  mWidth = 800;
    private static final int  mHeight = 600;
    private static final int  mHeaderSize = 16;
    private static final int  mSize = mWidth * mHeight * 4 + mHeaderSize;

    private static String TAG = "ShareBitmapService";
    private static final String mFileName = "ScreenShot.png";

    @Override
    public void onCreate() {
        try {
            long begin = SystemClock.uptimeMillis();
            /*Create memory file and share bitmap.*/
            mMemoryFile = new MemoryFile(mFileName, mSize);
            FileDescriptor fd = mMemoryFile.getFileDescriptor();
            mBitmap = Bitmap.createShareBitmap(fd, mSize, mWidth, mHeight, Bitmap.Config.ARGB_8888);
            mBitmap.eraseColor(0xFFFF0000);
            long cost = SystemClock.uptimeMillis() - begin;

            Log.i(TAG, "Create mBitmap = " + mBitmap + " cost " + cost);

            Toast.makeText(this, "IShareBitmapService start", 
                Toast.LENGTH_SHORT).show();
        }
        catch (Exception ex) {
            Toast.makeText(this, "IShareBitmapService fail:" 
                + ex.toString(), Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public void onDestroy() {
        Toast.makeText(this, "IShareBitmapService stop", Toast.LENGTH_SHORT).show();
    }
    
    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    private final IShareBitmapService.Stub mBinder = new IShareBitmapService.Stub() {
	    public int updateBitmap(){
	        mColorIndex = (mColorIndex + 1)%3;
            int color = 0xFF000000 | (0xFF << (mColorIndex * 8));
           
            mBitmap.eraseColor(color);
            
            Log.i(TAG, "mColorIndex=" + mColorIndex + " color=" + color);

	        return 0;
	    }

        public  ParcelFileDescriptor getShareBitmap(){
            try {
                return mMemoryFile.getParcelFileDescriptor();
            }
            catch(IOException ex){
                Log.i(TAG, ex.toString());
            }

            return null;
        }
    };
}

