/*
 * File:    PdfReader.java
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   Pdf reader base clas.
 *
 * Copyright (c) 2009 Li XianJing<xianjimli@hotmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2009-09-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */
package org.broncho.pdfreader;

import java.lang.Integer;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.view.LayoutInflater;
import android.content.DialogInterface;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceManager;
import android.provider.MediaStore;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Toast;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.ZoomButtonsController;
import java.io.File;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.res.Resources;

public abstract class PdfReader extends Activity implements View.OnClickListener
{
	protected static final String TAG = "PdfReader";

	protected static final int    DIALOG_SEEK     = 2000;
	protected static final int    DIALOG_OPEN     = 2001;
	protected static final int    DIALOG_ABOUT    = 2002;
	protected static final int    DIALOG_PROGRESS = 2003;
	protected static final int    MENU_SEEK       = 1000; 
	protected static final int    MENU_OPEN       = 1001; 
	protected static final int    MENU_TEXT_MODE  = 1002; 
	protected static final int    MENU_IMAGE_MODE = 1003; 
	protected static final int    MENU_ABOUT      = 1004; 
	protected static final int    MENU_SETTINGS   = 1006; 
	protected static final int    FILE_SELECT_CODE = 1000;

	protected View      mNextImageView;
	protected View      mPrevImageView;
	protected ProgressDialog mProgressDialog;
	protected Animation mHideNextImageViewAnimation = new AlphaAnimation(1F, 0F);
	protected Animation mHidePrevImageViewAnimation = new AlphaAnimation(1F, 0F);
	protected Animation mShowNextImageViewAnimation = new AlphaAnimation(0F, 1F);
	protected Animation mShowPrevImageViewAnimation = new AlphaAnimation(0F, 1F);
	protected boolean   mFullScreenInNormalMode = true;

	protected SharedPreferences     mPrefs;
	protected ZoomButtonsController mZoomButtonsController;
	protected Runnable              mDismissOnScreenControlsRunnable;

	protected Uri         mUri;
	protected float       mScale = 1.0f;
	protected int         mCurrentPosition;
	protected PdfDecoder  mDecoder;	
	
	abstract protected boolean onOpen(String fileName);
	abstract protected void    setPage(int pageIndex);
	abstract protected void    setupZoomButtonController();
	abstract protected void    updateZoomButtonsEnabled();

	protected LocalHandler     mHandler = new LocalHandler();

	protected void moveNextOrPrevious(int delta) 
	{
		int nextPagePos = mCurrentPosition + delta;

		if ((0 <= nextPagePos) && (nextPagePos < mDecoder.getPageCount())) 
		{
			setPage(nextPagePos);
		}

		return;
	}

	public void onClick(View v) 
	{
		switch (v.getId()) 
		{
    	    case R.id.next_image: 
			{
            	moveNextOrPrevious(1);
	        }
    	    break;
	        case R.id.prev_image: 
			{
            	moveNextOrPrevious(-1);
				break;
			}
        }

		return;
	}

    @Override
    protected Dialog onCreateDialog(int id) 
	{
		LayoutInflater factory = LayoutInflater.from(this);
        switch (id) 
		{
            case DIALOG_SEEK: 
			{
			  	final int pageCount = mDecoder.getPageCount();
				final View view = factory.inflate(R.layout.seek_dialog, null);
				TextView tv = (TextView)view.findViewById(R.id.prompt_text);
				tv.setText(String.format(getString(R.string.seek_prompt), pageCount));
				
	            return new AlertDialog.Builder(PdfReader.this)
    	        	.setIcon(R.drawable.icon)
	        	    .setTitle(R.string.seek)
            		.setView(view)
                	.setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() 
					{
	                    public void onClick(DialogInterface dialog, int whichButton) 
						{
							EditText editor = (EditText)view.findViewById(R.id.input);
							CharSequence str = editor.getText();
							if(str != null && str.length() > 0)
							{
								int pageIndex = Integer.parseInt(str.toString());
								if(pageIndex >= 0 && pageIndex < pageCount)
								{
									setPage(pageIndex);	
								}
							}
                    	}
	                })
					.setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() 
					{
                   	 public void onClick(DialogInterface dialog, int whichButton) {}
	                })
    	            .create();
            }
            case DIALOG_OPEN: 
			{
				final View view = factory.inflate(R.layout.open_dialog, null);
				return new AlertDialog.Builder(PdfReader.this)
				.setIcon(R.drawable.icon)
				.setTitle(R.string.open_prompt)
				.setView(view)
				.setNeutralButton(R.string.file_browse, new DialogInterface.OnClickListener()
				{
                    public void onClick(DialogInterface dialog, int whichButton) 
					{
						Uri uri = Uri.parse("file:///sdcard");
						Intent intent = new Intent(PdfReader.this, FileSelect.class);  
						intent.setAction(Intent.ACTION_PICK);
						intent.setDataAndType(uri, "application/pdf");  
						startActivityForResult(intent, FILE_SELECT_CODE);
					}
				})
				.setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() 
				{
                    public void onClick(DialogInterface dialog, int whichButton) 
					{
						EditText editor = (EditText)view.findViewById(R.id.input);
						CharSequence str = editor.getText();
						if(str != null && str.length() > 0 
							&& PdfDecoder.isPdf(str.toString()))
						{
							if(onOpen(str.toString()))
							{
								setPage(0);
							}
						}
						else
						{
							Toast.makeText(PdfReader.this, 
								String.format(getString(R.string.open_fail), str.toString()),
								Toast.LENGTH_SHORT).show();
						}
                    }
                })
                .setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {}
                })
                .create();
            }
            case DIALOG_ABOUT: 
			{
				final View view = factory.inflate(R.layout.about_dialog, null);
				TextView tv = (TextView)view.findViewById(R.id.author);
				tv.setText("Author: Li XianJing");

				tv = (TextView)view.findViewById(R.id.poppler);
				tv.setText("This software is base on poppler(http://poppler.freedesktop.org/).");

				tv = (TextView)view.findViewById(R.id.broncho);
				tv.setText("This software is developed by broncho team(http://www.broncho.cn/).");

				tv = (TextView)view.findViewById(R.id.source);
				tv.setText("This software is released under GPLv2, you can download source code from http://www.limodev.cn.");

				return new AlertDialog.Builder(PdfReader.this)
				  .setIcon(R.drawable.icon)
				  .setTitle(R.string.about)
				  .setView(view)
				  .setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() 
				  {
					public void onClick(DialogInterface dialog, int whichButton) 
					{}
				   }).create();
			}
			case DIALOG_PROGRESS:
			{
    			mProgressDialog = new ProgressDialog(this);
    			mProgressDialog.setIcon(R.drawable.icon);
    			mProgressDialog.setTitle(R.string.loading);

    			return mProgressDialog;
			}
		}
		return null;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) 
	{
    	switch(item.getItemId())
		{
			case MENU_OPEN:
			{
				showDialog(DIALOG_OPEN);
				break;
			}
			case MENU_SEEK: 
			{
				if(mDecoder.isOpen())
					showDialog(DIALOG_SEEK);
				break;
			}
			case MENU_ABOUT:
			{
				showDialog(DIALOG_ABOUT);
				break;
			}
			case MENU_TEXT_MODE:
			{
				mDecoder.close();
				Intent intent = new Intent(this, PdfTextReader.class);  
				intent.setAction(Intent.ACTION_VIEW);
				intent.setDataAndType(mUri, "application/pdf");  
				intent.putExtra("pageIndex", String.valueOf(mCurrentPosition));  
				startActivityForResult(intent, 0);
				finish();

				break;
			}
			case MENU_IMAGE_MODE:
			{
				mDecoder.close();
				Intent intent = new Intent(this, PdfImageReader.class);  
				intent.setAction(Intent.ACTION_VIEW);
				intent.setDataAndType(mUri, "application/pdf");  
				intent.putExtra("pageIndex", String.valueOf(mCurrentPosition));  
				startActivityForResult(intent, 0);
				finish();

				break;
			}
		}

		return true;
	}
	
	public void Init(Bundle instanceState, int id) 
	{
		Intent intent = getIntent();
		mFullScreenInNormalMode = intent.getBooleanExtra(MediaStore.EXTRA_FULL_SCREEN, true);

		mPrefs = PreferenceManager.getDefaultSharedPreferences(this);

		setDefaultKeyMode(DEFAULT_KEYS_SHORTCUT);
		requestWindowFeature(Window.FEATURE_NO_TITLE);

		setContentView(id);

		mCurrentPosition = 0;
		mNextImageView = findViewById(R.id.next_image);
		mPrevImageView = findViewById(R.id.prev_image);
		
		mNextImageView.setOnClickListener(this);
		mPrevImageView.setOnClickListener(this);

        Uri uri = getIntent().getData();
		if (instanceState != null) 
		{
			if (instanceState.containsKey("uri")) 
			{
				uri = Uri.parse(instanceState.getString("uri"));
			}
		}
		
		mDecoder = new PdfDecoder();

		if(uri != null)
		{
			mUri = uri;
			onOpen(uri.getPath());
			Log.v(TAG, "onCreate: path="+uri.getPath());
			String str       = (String)intent.getExtra("pageIndex");
			if(str != null)
			{
				mCurrentPosition = Integer.parseInt(str);
			}
			Log.v(TAG, "onCreate: mCurrentPosition="+mCurrentPosition);
		}

		if(!mDecoder.isOpen())
		{
			Toast.makeText(this, getString(R.string.open_null), Toast.LENGTH_SHORT).show();
		}

		if (mFullScreenInNormalMode) 
		{
			getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
		}

		setupZoomButtonController();
		setupDismissOnScreenControlRunnable();

		return;
	}

	protected void updateNextPrevControls() 
	{
		boolean showPrev = mCurrentPosition > 0;
		boolean showNext = mCurrentPosition < mDecoder.getPageCount() - 1;

		boolean prevIsVisible = mPrevImageView.getVisibility() == View.VISIBLE;
		boolean nextIsVisible = mNextImageView.getVisibility() == View.VISIBLE;

		Log.v(TAG, "updateNextPrevControls mCurrentPosition="+mCurrentPosition+" showPrev" + showPrev);
		if (showPrev && !prevIsVisible) 
		{
			Animation a = mShowPrevImageViewAnimation;
			a.setDuration(500);
			a.startNow();
			mPrevImageView.setAnimation(a);
			mPrevImageView.setVisibility(View.VISIBLE);
		}
		else if (!showPrev && prevIsVisible) 
		{
			Animation a = mHidePrevImageViewAnimation;
			a.setDuration(500);
			a.startNow();
			mPrevImageView.setAnimation(a);
			mPrevImageView.setVisibility(View.GONE);
		}

		if (showNext && !nextIsVisible) 
		{
			Animation a = mShowNextImageViewAnimation;
			a.setDuration(500);
			a.startNow();
			mNextImageView.setAnimation(a);
			mNextImageView.setVisibility(View.VISIBLE);
		}
		else if (!showNext && nextIsVisible) 
		{
			Animation a = mHideNextImageViewAnimation;
			a.setDuration(500);
			a.startNow();
			mNextImageView.setAnimation(a);
			mNextImageView.setVisibility(View.GONE);
		}

		return;
	}

	protected void showOnScreenControls() 
	{
		mHandler.removeCallbacks(mDismissOnScreenControlsRunnable);
		updateNextPrevControls();
		updateZoomButtonsEnabled();
		mZoomButtonsController.setVisible(true);

		return;
	}
	
	@Override
	public boolean dispatchTouchEvent(MotionEvent m) 
	{
		boolean sup = super.dispatchTouchEvent(m);

		switch (m.getAction()) 
		{
			case MotionEvent.ACTION_DOWN:
				showOnScreenControls();
				sup = true;
				break;
			case MotionEvent.ACTION_UP:
				scheduleDismissOnScreenControls();
				sup = true;
				break;
		}

		return sup;
	}

	protected void scheduleDismissOnScreenControls() 
	{
		mHandler.removeCallbacks(mDismissOnScreenControlsRunnable);
		mHandler.postDelayed(mDismissOnScreenControlsRunnable, 1500);

		return;
	}


	@Override
	protected void onDestroy() 
	{
		if (mZoomButtonsController != null) 
		{
			mZoomButtonsController.setVisible(false);
		}
	
		if(mDecoder != null)
		{
			mDecoder.close();
		}

		super.onDestroy();
	}

	protected void setupDismissOnScreenControlRunnable() 
	{
		mDismissOnScreenControlsRunnable = new Runnable() 
		{
			public void run() 
			{
				if (mNextImageView.getVisibility() == View.VISIBLE) 
				{
					Animation a = mHideNextImageViewAnimation;
					a.setDuration(500);
					a.startNow();
					mNextImageView.setAnimation(a);
					mNextImageView.setVisibility(View.INVISIBLE);
				}
				if (mPrevImageView.getVisibility() == View.VISIBLE) 
				{
					Animation a = mHidePrevImageViewAnimation;
					a.setDuration(500);
					a.startNow();
					mPrevImageView.setAnimation(a);
					mPrevImageView.setVisibility(View.INVISIBLE);
				}
				mZoomButtonsController.setVisible(false);

				return;
			}
		};
	}

	static class LocalHandler extends Handler 
	{
		private static final int RUN_RUNNABLE = 1;

		@Override
		public void handleMessage(Message message) 
		{
			switch(message.what) {
			case RUN_RUNNABLE:
				((Runnable) message.obj).run();
			}
		}
	}

	private class OpenRunnable implements Runnable	
	{
		public void run()
		{
			onOpen(mUri.getPath());			
		}
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) 
	{
		Log.v(TAG, "onActivityResult resultCode="+requestCode + " requestCode=" + requestCode + " data="+data);
		if(requestCode == FILE_SELECT_CODE && resultCode == RESULT_OK) 
		{
			Uri uri = data.getData();
			if(uri != null)
			{
				mUri = uri;
				mHandler.post(new OpenRunnable());
			}
			Log.v(TAG, "onActivityResult uri="+uri);

			return;
		}

		return;
	}

}
