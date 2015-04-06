/*
 * File:    FileSelect.java
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   file select.
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

import java.util.Arrays;
import java.util.Comparator;
import android.net.Uri;
import android.app.ListActivity;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;
import android.widget.ImageView;
import android.graphics.BitmapFactory;
import android.graphics.Bitmap;
import java.io.File;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;
import android.widget.AdapterView;
import java.util.ArrayList;
import java.lang.String;
import android.util.Log;
import android.content.Intent;

public class FileSelect extends ListActivity 
{
	private FilesystemAdapter mAdapter;	

    private static class FilesystemAdapter extends BaseAdapter 
	{
		public  File mPath;
		private int mCount;
        private Bitmap mIconFile;
        private Bitmap mIconFolder;
		private String [] mChildren;
        private LayoutInflater mInflater;

		public String getChild(int pos)
		{
			return mChildren[pos];
		}

		public boolean down(String sub)
		{
			mPath = new File(mPath, sub);
			updateList();

			return true;
		}
		
		public boolean up()
		{
			mPath = mPath.getParentFile();
			updateList();

			return true;
		}

		public boolean isRoot()
		{
			return mPath.equals("/");
		}

		private final Comparator<Object> mComparer = new Comparator<Object>() 
		{
			@SuppressWarnings("unchecked")
			public int compare(Object first, Object second) 
			{
				File fileFirst = new File(mPath, (String)first);
				File fileSecond = new File(mPath, (String)second);
				
				if(fileFirst.isDirectory() && !fileSecond.isDirectory())
				{
					return -1;
				}
				else if(!fileFirst.isDirectory() && fileSecond.isDirectory())
				{
					return 1;
				}

				return ((Comparable<Object>)first).compareTo(second);
		    }
		};

		public boolean updateList()
		{
			if(mPath == null)
			{
				mPath = new File("/");
			}

			mChildren = mPath.list();
			mCount    = mChildren.length;
			Arrays.sort(mChildren, 0, mChildren.length, mComparer);

			return true;
		}

		public boolean setPath(String path)
		{
			mPath = new File(path);

			if(!mPath.exists())
			{
				mPath = new File("/");
			}
			else if(!mPath.isDirectory())
			{
				mPath = mPath.getParentFile();
			}

			updateList();

			return true;
		}

        public FilesystemAdapter(Context context) 
		{
            mInflater = LayoutInflater.from(context);

            mIconFolder = BitmapFactory.decodeResource(context.getResources(), R.drawable.folder);
            mIconFile = BitmapFactory.decodeResource(context.getResources(), R.drawable.file);
        }

        public int getCount() 
		{
            return mCount;
        }

        public Object getItem(int position) 
		{
            return position;
        }

        /**
         * Use the array index as a unique id.
         *
         * @see android.widget.ListAdapter#getItemId(int)
         */
        public long getItemId(int position) 
		{
            return position;
        }

        /**
         * Make a view to hold each row.
         *
         * @see android.widget.ListAdapter#getView(int, android.view.View,
         *      android.view.ViewGroup)
         */
        public View getView(int position, View convertView, ViewGroup parent) 
		{
            ViewHolder holder;
            if (convertView == null) 
			{
                convertView = mInflater.inflate(R.layout.list_item_icon_text, null);

                holder = new ViewHolder();
                holder.text = (TextView) convertView.findViewById(R.id.text);
                holder.icon = (ImageView) convertView.findViewById(R.id.icon);
				
                convertView.setTag(holder);
            }
			else 
			{
                holder = (ViewHolder) convertView.getTag();
            }

			File file = new File(mPath, mChildren[position]);

            holder.text.setText(mChildren[position]);
           	holder.icon.setImageBitmap(file.isDirectory() ? mIconFolder : mIconFile);

            return convertView;
        }

        static class ViewHolder {
            TextView text;
            ImageView icon;
        }
    }

    @Override
    public void onCreate(Bundle savedInstanceState) 
	{
        super.onCreate(savedInstanceState);
        Uri uri = getIntent().getData();

		Log.v("FileSelect", "uri="+uri);

		mAdapter = new FilesystemAdapter(this);
		if(uri != null)
		{
			mAdapter.setPath("/");
		}
		else
		{
			mAdapter.setPath(uri.getPath());
		}

        setListAdapter(mAdapter);

		getListView().setOnItemClickListener(new AdapterView.OnItemClickListener()
		{
			public void onItemClick(AdapterView parent, View view, int position, long id)
			{
				String sub = mAdapter.getChild(position);
				File file = new File(mAdapter.mPath, sub);
				if(file.isDirectory())
				{
					mAdapter.down(sub);
        			setListAdapter(mAdapter);
				}
				else if(sub.endsWith(".pdf"))
				{
					String path = file.getAbsolutePath();
					Uri uri = Uri.parse("file://"+path);
					setResult(RESULT_OK, new Intent().setData(uri));

					finish();
				}

				return;
			}
		});
    }

	static final int MENU_SELECT = 1000;
	static final int MENU_BACK   = 1001;

	@Override
	public boolean onCreateOptionsMenu(Menu menu) 
	{
		super.onCreateOptionsMenu(menu);

		MenuItem item = menu.add(Menu.CATEGORY_SECONDARY, MENU_SELECT, 0, R.string.select);
		item = menu.add(Menu.CATEGORY_SECONDARY, MENU_BACK, 0, R.string.back);

		return true;
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) 
	{
    	switch(item.getItemId())
		{
			case MENU_SELECT:
			{
				int position = getSelectedItemPosition();
				String sub = mAdapter.getChild(position);
				File file = new File(mAdapter.mPath, sub);
				if(file.isDirectory())
				{
					mAdapter.down(sub);
        			setListAdapter(mAdapter);
				}
				else if(sub.endsWith(".pdf"))
				{
					String path = file.getAbsolutePath();
					Uri uri = Uri.parse("file://"+path);
					setResult(RESULT_OK, new Intent().setData(uri));

					finish();
				}
				break;
			}
			case MENU_BACK:
			{
				if(mAdapter.isRoot())
				{
					finish();
				}
				else
				{
					mAdapter.up();
	        		setListAdapter(mAdapter);
				}
			}
		}

		return true;
	}
}
