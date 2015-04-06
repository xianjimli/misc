/*
 * File:    PdfDecoder.java
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   Pdf Decoder
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

import android.util.Log;
import android.graphics.Bitmap;

public class PdfDecoder
{
	private int nativeDoc = 0;
	private boolean mIsOpen = false;
	private static final String TAG = "PdfDecoder";

    static 
    {
    	try 
    	{
    		System.loadLibrary ("jni_pdf");
    	} 
    	catch (UnsatisfiedLinkError ule) 
    	{
    		Log.e (TAG, "Could not load jni_pdf natives");
    	}
    }

	PdfDecoder()
	{
		
	}

	public boolean isOpen()
	{
		return mIsOpen;
	}

	public boolean open(String filename, String cacheDir)
	{
		close();
		nativeDoc = pdfOpen(filename, cacheDir);
		mIsOpen = nativeDoc != 0;

		return mIsOpen;
	}

	public int     getPageCount()
	{
		return pdfGetPageCount(nativeDoc);
	}

	public String  decodeText(int pageIndex, int flags)
	{
		return pdfDecodeText(nativeDoc, pageIndex, flags);
	}
	
	public String decodeImage(int pageIndex, int flags)
	{
		String fileName = pdfDecodeImage(nativeDoc, pageIndex, flags);
		return fileName;
	}

	public void    close()
	{
		if(mIsOpen)
		{
			mIsOpen = false;
			pdfClose(nativeDoc);
			nativeDoc = 0;
		}

		return;
	}

	static public boolean isPdf(String fileName)
	{
		return pdfIsPdf(fileName);
	}

	static private native  boolean pdfIsPdf(String filename);
	private native int     pdfOpen(String filename, String cacheDir);
	private native int     pdfGetPageCount(int docPtr);
	private native String  pdfDecodeText(int docPtr, int pageIndex, int flags);
	private native String  pdfDecodeImage(int docPtr, int pageIndex, int flags);
	private native void    pdfClose(int docPtr);
}

