LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := burner.cpp

LOCAL_SHARED_LIBRARIES := libIDburn_d liblog 
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../libIDburn 

LOCAL_MODULE    := libidburnerjni

ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 26 && echo OK),OK)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_CFLAGS += -Wno-unused-parameter \
    -Wno-format

LOCAL_C_INCLUDES += \
	libnativehelper/include_jni/ 

include $(BUILD_SHARED_LIBRARY)
