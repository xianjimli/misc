LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= gcu.c  m2d_lib.c  m2dtest.c
LOCAL_MODULE := m2dtest
LOCAL_C_INCLUDES := vendor/marvell/generic/include vendor/marvell/littleton/m2d
LOCAL_STATIC_LIBRARIES :=libcutils libc
#LOCAL_SHARED_LIBRARIES :=libMrvlm2d

include $(BUILD_EXECUTABLE)
