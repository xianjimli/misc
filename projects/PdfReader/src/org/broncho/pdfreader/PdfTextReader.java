/*
 * File:    PdfTextReader.java
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   Pdf text mode reader.
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
import android.view.GestureDetector;
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
import android.content.res.Resources;

public class PdfTextReader extends PdfReader implements View.OnClickListener
{
	
	private TextView     mTextView;
	private float        mTextSize;
	private final float  mMaxScale   = 3.0f;

	protected void updateZoomButtonsEnabled() 
	{
		mZoomButtonsController.setZoomInEnabled(mScale < mMaxScale);
		mZoomButtonsController.setZoomOutEnabled(mScale > 0.5f);

		return;
	}

	@Override
	protected void onDestroy() 
	{
		super.onDestroy();

		return;
	}

	protected void setupZoomButtonController() 
	{
		View rootView = findViewById(R.id.scroll_view);
		mZoomButtonsController = new ZoomButtonsController(rootView);
		mZoomButtonsController.setAutoDismissed(false);
		mZoomButtonsController.setOnZoomListener(
		new ZoomButtonsController.OnZoomListener() 
		{
			public void onVisibilityChanged(boolean visible) 
			{
				if (visible) 
				{
					updateZoomButtonsEnabled();
				}
			}

			public void onZoom(boolean zoomIn) 
			{
				if (zoomIn) 
				{
					mScale = mScale * 1.25f;
				} 
				else 
				{
					mScale = mScale * 0.75f;
				}
				float size = mTextSize * mScale;
				mTextView.setTextSize(size);
			}
		});

		return;
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) 
	{
		super.onCreateOptionsMenu(menu);

		MenuItem item = menu.add(Menu.CATEGORY_SECONDARY, MENU_OPEN, 0, R.string.open);
		item.setIcon(R.drawable.open);
		
		item = menu.add(Menu.CATEGORY_SECONDARY, 203, 0, R.string.share);
		item.setOnMenuItemClickListener(new MenuItem.OnMenuItemClickListener() 
		{
			public boolean onMenuItemClick(MenuItem item) 
			{
				if(!mDecoder.isOpen())
				{
					return true;
				}
				Intent intent = new Intent();
				intent.setAction(Intent.ACTION_SEND);
				intent.setType("text/plain");
				intent.putExtra(Intent.EXTRA_TEXT, mTextView.getText());

				try 
				{
					startActivity(Intent.createChooser(intent, getText(R.string.send_text)));
				}
				catch (android.content.ActivityNotFoundException ex) 
				{
				}
				return true;
			}
		});
		item.setIcon(R.drawable.share);
		
		item = menu.add(Menu.CATEGORY_SECONDARY, MENU_IMAGE_MODE, 0, R.string.image_mode);
		item.setIcon(R.drawable.image_mode);

		item = menu.add(Menu.CATEGORY_SECONDARY, MENU_SETTINGS, 0, R.string.settings);
		item.setIcon(R.drawable.settings);

		item = menu.add(Menu.CATEGORY_SECONDARY, MENU_SEEK, 0, R.string.seek);
		item.setIcon(R.drawable.seek);

		item = menu.add(Menu.CATEGORY_SECONDARY, MENU_ABOUT, 0, R.string.about);
		item.setIcon(R.drawable.about);

		return true;
	}
	
	protected boolean onOpen(String fileName)
	{
		boolean ret = false;
		if(mDecoder.open(fileName, getCacheDir().getPath()))
		{
			mUri = Uri.parse("file://"+fileName);
			ret = true;
		}

		Log.v(TAG, "Open " + fileName);

		return ret;
	}

	protected void setPage(int pos) 
	{
		if(pos >= mDecoder.getPageCount())
		{
			return;
		}

		if(pos > 0)
		{
			Toast.makeText(this, pos+"/"+mDecoder.getPageCount(), Toast.LENGTH_SHORT).show();
		}

		mCurrentPosition = pos;
		showOnScreenControls();
		scheduleDismissOnScreenControls();
		updateZoomButtonsEnabled();
	
		float size = mTextSize * mScale;
		mTextView.setTextSize(size);
		mTextView.setText(mDecoder.decodeText(mCurrentPosition, 0));
	
		return;
	}

	@Override
	public void onCreate(Bundle instanceState) 
	{
		super.onCreate(instanceState);

		Init(instanceState, R.layout.viewtext);

		mTextView = (TextView)findViewById(R.id.text_view);
		mTextSize = mTextView.getTextSize();

		setPage(mCurrentPosition);

		return;
	}

	@Override
	public void onSaveInstanceState(Bundle b) 
	{
		super.onSaveInstanceState(b);

		return;
	}

	@Override
	public void onResume() 
	{
		super.onResume();

		return;
	}

	@Override
	public void onPause() 
	{
		super.onPause();

		return;
	}

	static class LocalHandler extends Handler 
	{
		@Override
		public void handleMessage(Message message) 
		{
			super.handleMessage(message);
		}
	}
}
