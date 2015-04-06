LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= MyService.cpp  MyService.h  main.cpp IMyService.cpp
LOCAL_SHARED_LIBRARIES :=  libui libcutils libutils 
LOCAL_MODULE := myservice
LOCAL_STATIC_LIBRARIES := libc
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= IMyService.cpp MyTest.cpp test.cpp
LOCAL_SHARED_LIBRARIES :=  libui libcutils libutils 
LOCAL_MODULE := mytest
LOCAL_STATIC_LIBRARIES := libc
include $(BUILD_EXECUTABLE)

