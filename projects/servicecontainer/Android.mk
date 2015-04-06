LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
         $(call all-subdir-java-files)
LOCAL_SRC_FILES += src/org/broncho/servicecontainer/IFakeInput.aidl 
LOCAL_CERTIFICATE := platform
LOCAL_PACKAGE_NAME := ServiceContainer 

include $(BUILD_PACKAGE)

