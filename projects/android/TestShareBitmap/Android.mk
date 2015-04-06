LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_SRC_FILES += src/com/lxj/IShareBitmapService.aidl
LOCAL_PACKAGE_NAME := TestShareBitmap 

include $(BUILD_PACKAGE)

