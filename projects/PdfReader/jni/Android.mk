LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
	poppler/FontInfo.cpp \
	poppler/CMap.cpp \
	poppler/UnicodeTypeTable.cpp \
	poppler/Movie.cpp \
	poppler/PDFDoc.cpp \
	poppler/Form.cpp \
	poppler/SecurityHandler.cpp \
	poppler/Sound.cpp \
	poppler/Array.cpp \
	poppler/SplashOutputDev.cpp \
	poppler/JPXStream.cpp \
	poppler/NameToCharCode.cpp \
	poppler/Decrypt.cpp \
	poppler/FileSpec.cpp \
	poppler/CharCodeToUnicode.cpp \
	poppler/JBIG2Stream.cpp \
	poppler/PSTokenizer.cpp \
	poppler/Gfx.cpp \
	poppler/Link.cpp \
	poppler/GlobalParams.cpp \
	poppler/XpdfPluginAPI.cpp \
	poppler/OutputDev.cpp \
	poppler/Stream.cpp \
	poppler/TextOutputDev.cpp \
	poppler/Object.cpp \
	poppler/Dict.cpp \
	poppler/ProfileData.cpp \
	poppler/Parser.cpp \
	poppler/UnicodeMap.cpp \
	poppler/PreScanOutputDev.cpp \
	poppler/Lexer.cpp \
	poppler/Page.cpp \
	poppler/PopplerCache.cpp \
	poppler/XRef.cpp \
	poppler/GfxFont.cpp \
	poppler/Annot.cpp \
	poppler/Error.cpp \
	poppler/FlateStream.cpp \
	poppler/Catalog.cpp \
	poppler/PDFDocEncoding.cpp \
	poppler/GfxState.cpp \
	poppler/DCTStream.cpp \
	poppler/Function.cpp \
	poppler/BuiltinFontTables.cpp \
	poppler/PageTransition.cpp \
	poppler/BuiltinFont.cpp \
	poppler/OptionalContent.cpp \
	poppler/FontEncodingTables.cpp \
	poppler/Outline.cpp \
	poppler/JArithmeticDecoder.cpp \
	poppler/DateInfo.cpp \
	poppler/PageLabelInfo.cpp \
	goo/gmempp.cpp \
	goo/GooList.cpp \
	goo/GooString.cpp \
	goo/PNGWriter.cpp \
	goo/GooTimer.cpp \
	goo/gfile.cpp \
	goo/GooHash.cpp \
	goo/gmem.cpp \
	goo/FixedPoint.cpp \
	fofi/FoFiType1.cpp \
	fofi/FoFiType1C.cpp \
	fofi/FoFiBase.cpp \
	fofi/FoFiTrueType.cpp \
	fofi/FoFiEncodings.cpp \
	splash/SplashBitmap.cpp \
	splash/SplashFTFontFile.cpp \
	splash/SplashFont.cpp \
	splash/SplashFontFile.cpp \
	splash/SplashXPathScanner.cpp \
	splash/SplashFTFontEngine.cpp \
	splash/SplashPattern.cpp \
	splash/SplashFontEngine.cpp \
	splash/SplashState.cpp \
	splash/SplashFTFont.cpp \
	splash/SplashClip.cpp \
	splash/SplashT1FontEngine.cpp \
	splash/SplashT1FontFile.cpp \
	splash/SplashFontFileID.cpp \
	splash/SplashT1Font.cpp \
	splash/SplashPath.cpp \
	splash/SplashScreen.cpp \
	splash/Splash.cpp \
	splash/SplashXPath.cpp 

#
MY_INCLUDES=external/zlib external/jpeg external/freetype/include \
	frameworks/base/core/jni/android/graphics  external/skia/include/core \
	external/libpng external/expat/lib

MY_CFLAGS=-I$(LOCAL_PATH) -I$(LOCAL_PATH)/fc -I$(LOCAL_PATH)/goo \
	-I$(LOCAL_PATH)/fofi \
    -I$(LOCAL_PATH)/splash -I$(LOCAL_PATH)/poppler -O3

LOCAL_MODULE := libpdf
LOCAL_C_INCLUDES += $(MY_INCLUDES)
LOCAL_CFLAGS += $(MY_CFLAGS) -DHAVE_CONFIG_H -DFONTCONFIG_PATH="\"/etc/fonts\"" \
	-DFC_CACHEDIR="\"\"" -DFC_DEFAULT_FONTS="\"\""

include $(BUILD_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_SRC_FILES:=utils/pdftotext.cpp
#LOCAL_MODULE := pdftotext
#LOCAL_C_INCLUDES += $(MY_INCLUDES)
#LOCAL_CFLAGS += $(MY_CFLAGS)
#LOCAL_STATIC_LIBRARIES:= libpdf libjpeg libft2 
#LOCAL_SHARED_LIBRARIES:= libz libc libcorecg libsgl libandroid_runtime
#include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:=PdfFacade.cpp
LOCAL_C_INCLUDES += $(MY_INCLUDES)
LOCAL_CFLAGS += $(MY_CFLAGS) -DPDF_FACADE_TEST
LOCAL_MODULE := pdffacade_test
LOCAL_STATIC_LIBRARIES:= libpdf libjpeg libft2 
LOCAL_SHARED_LIBRARIES:= libz libc libcorecg libsgl libandroid_runtime
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_MODULE := libjni_pdf
LOCAL_SRC_FILES := org_broncho_pdfreader_PdfDecoder.cpp PdfFacade.cpp
LOCAL_C_INCLUDES += $(MY_INCLUDES)
LOCAL_CFLAGS += $(MY_CFLAGS)
LOCAL_C_INCLUDES += $(JNI_H_INCLUDE)
LOCAL_SHARED_LIBRARIES := libcutils	libutils libz libc libcorecg libsgl libandroid_runtime  libexpat
LOCAL_STATIC_LIBRARIES:= libpdf libjpeg libft2
LOCAL_WHOLE_STATIC_LIBRARIES := libpdf libjpeg
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

