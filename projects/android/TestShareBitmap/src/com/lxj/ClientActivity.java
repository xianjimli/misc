package com.lxj;

import android.util.Log;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.Button;
import android.widget.TextView;
import android.view.View.OnClickListener;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.RemoteException;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Process;
import android.content.ComponentName;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import android.os.MemoryFile;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.SystemClock;
import android.os.ParcelFileDescriptor;
import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.io.FileDescriptor;

public class ClientActivity extends Activity
{
    private Bitmap mBitmap;
    private MemoryFile mMemoryFile;
    private Button mUpdateButton;
    private Button mConnectButton;
    private final String TAG = "ClientActivity";
    private IShareBitmapService mShareBitmapService;

    private static final int  mWidth = 800;
    private static final int  mHeight = 600;
    private static final int  mHeaderSize = 16;
    private static final int  mSize = mWidth * mHeight * 4 + mHeaderSize;

    
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.main);
       
        mConnectButton = (Button)findViewById(R.id.connect);
        mConnectButton.setOnClickListener(mConnectListener);
        
        mUpdateButton = (Button)findViewById(R.id.update);
        mUpdateButton.setOnClickListener(mUpdateListener);
        mUpdateButton.setEnabled(false);
    }

    private ServiceConnection mShareBitmapServiceConnection = new ServiceConnection() {
        public void onServiceConnected(ComponentName className,
                IBinder service) {
            mShareBitmapService = IShareBitmapService.Stub.asInterface(service);
            mUpdateButton.setEnabled(true);
        }

        public void onServiceDisconnected(ComponentName className) {
            mShareBitmapService = null;
            mUpdateButton.setEnabled(false);
        }
    };
    
    private OnClickListener mConnectListener = new OnClickListener() {
        public void onClick(View v) {
            bindService(new Intent(IShareBitmapService.class.getName()),
                    mShareBitmapServiceConnection, Context.BIND_AUTO_CREATE);
        }
    };

    private OnClickListener mUpdateListener = new OnClickListener() {
        public void onClick(View v) {
            try {
                long begin = SystemClock.uptimeMillis();
                if(mBitmap == null){
                    /*Get share bitmap FileDescriptor and create bitmap.*/
                    ParcelFileDescriptor pFd = mShareBitmapService.getShareBitmap();
                    FileDescriptor fd = pFd.getFileDescriptor();
                    mBitmap = Bitmap.createShareBitmap(fd, mSize, 0, 0, Bitmap.Config.ARGB_8888);
                }
                else
                {
                    mShareBitmapService.updateBitmap();
                }
                ImageView image_view = (ImageView)findViewById(R.id.imageview);
                image_view.setImageBitmap(mBitmap);
                long cost = SystemClock.uptimeMillis() - begin;
                Log.i("ClientActivity", "Update bitmap=" + mBitmap + " cost = " + cost);
            }catch(Exception ex)
            {
                Log.e("ClientActivity", ex.toString());
            }
        }
    };
}

