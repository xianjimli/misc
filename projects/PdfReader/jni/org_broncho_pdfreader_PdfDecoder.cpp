/*
 * File:    org_broncho_pdfreader_PdfDecoder.cpp
 * Author:  Li XianJing <xianjimli@hotmail.com>
 * Brief:   Pdf JNI
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
#define LOG_TAG "PdfDecoder"

#include <stdlib.h>
#include <assert.h>
#include <utils/Log.h>
#include <jni.h>
#include <utils/String8.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "GooString.h"
#include "gmem.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Stream.h"
#include "Array.h"
#include "Dict.h"
#include "XRef.h"
#include "Catalog.h"
#include "Page.h"
#include "PDFDoc.h"
#include "TextOutputDev.h"
#include "CharTypes.h"
#include "UnicodeMap.h"
#include "Error.h"
#include "config.h"
#include "PdfFacade.h"
#include "GraphicsJNI.h"

static jint pdfOpen(JNIEnv *env, jobject thiz, jstring filename, jstring cacheDir)
{
	jint ret = 0;	
	const char *pdf_file = env->GetStringUTFChars(filename, NULL);
	const char* cache_dir = env->GetStringUTFChars(cacheDir, NULL);

	ret = PdfOpen(pdf_file, cache_dir, NULL, NULL);

	env->ReleaseStringUTFChars(filename, pdf_file);
	env->ReleaseStringUTFChars(cacheDir, cache_dir);

	return ret;
}

static jint pdfGetPageCount(JNIEnv* env, jobject thiz, jint docPtr)
{
	return PdfGetPageCount(docPtr);
}

static jstring pdfDecodeText(JNIEnv *env, jobject thiz, jint docPtr, jint pageIndex, jint flags)
{
	jstring str;
	char* utf8 = NULL;
	
	utf8 = PdfDecodeText(docPtr, pageIndex+1, flags);

	if(utf8 != NULL)
	{
		str = env->NewStringUTF(utf8); 
		free(utf8);
	}
	else
	{
		str = env->NewStringUTF("No content");
	}

	return str;
}

static jobject pdfDecodeImage(JNIEnv *env, jobject thiz, jint docPtr, jint pageIndex, jint flags)
{
	jstring str;
	char* utf8 = NULL;
	
	utf8 = PdfDecodeImage(docPtr, pageIndex+1, flags);

	if(utf8 != NULL)
	{
		str = env->NewStringUTF(utf8); 
		free(utf8);
	}
	else
	{
		str = NULL;
	}

	return str;
}

static void pdfClose(JNIEnv* env, jobject thiz, jint docPtr)
{
	PdfClose(docPtr);

	return;
}

static jboolean pdfIsPdf(JNIEnv *env, jobject thiz, jstring filename)
{
	jint ret = 0;	
	const char *pdf_file = env->GetStringUTFChars(filename, NULL);

	if((ret = PdfOpen(pdf_file, NULL, NULL, NULL))) 
	{
		PdfClose(ret);
	}

	env->ReleaseStringUTFChars(filename, pdf_file);

	return ret != 0;
}


static const JNINativeMethod gMethods[] = 
{
    {"pdfIsPdf",         "(Ljava/lang/String;)Z",                    (void*)pdfIsPdf},
    {"pdfOpen",          "(Ljava/lang/String;Ljava/lang/String;)I",  (void*)pdfOpen},
    {"pdfGetPageCount",  "(I)I",                                     (void*)pdfGetPageCount},
    {"pdfDecodeText",    "(III)Ljava/lang/String;",                  (void*)pdfDecodeText},
    {"pdfDecodeImage",   "(III)Ljava/lang/String;",                  (void*)pdfDecodeImage},
    {"pdfClose",         "(I)V",                                     (void*)pdfClose},
};

static int registerMethods(JNIEnv* env) 
{
    static const char* const kClassName =
        "org/broncho/pdfreader/PdfDecoder";
    jclass clazz;

    clazz = env->FindClass(kClassName);
    if (clazz == NULL) 
    {
        LOGE("Can't find class %s!\n", kClassName);
        return JNI_FALSE;
    }

    if (env->RegisterNatives(clazz, gMethods,
            sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK)
    {
        LOGE("Failed registering methods for %s!\n", kClassName);
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) 
{
    JNIEnv* env = NULL;
    jint result = -1;

    LOGI("PdfDecoder:JNI_OnLoad1\n");
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) 
    {
        LOGE("ERROR: GetEnv failed!\n");
        goto bail;
    }
    assert(env != NULL);

    if (registerMethods(env) != JNI_TRUE) {
        LOGE("ERROR: PdfDecoder native registration failed!\n");
        goto bail;
    }

    /* success -- return valid version number */
    result = JNI_VERSION_1_4;

    LOGI("PdfDecoder:JNI_OnLoad2\n");
bail:
    return result;
}

