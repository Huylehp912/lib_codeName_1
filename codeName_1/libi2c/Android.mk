LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libi2c_s
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := sdi2_i2c.c
LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/../include \
	prebuilts/gcc/linux-x86/host/i686-linux-glibc2.7-4.6/sysroot/usr/include/

LOCAL_STATIC_LIBRARIES := liblog libcutils
LOCAL_CERTIFICATE := platform

LOCAL_CFLAGS += -Wno-pointer-sign \
    -Wno-pointer-sign

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE := libi2c_d
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := sdi2_i2c.c
LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/../include \
	prebuilts/gcc/linux-x86/host/i686-linux-glibc2.7-4.6/sysroot/usr/include/ 

LOCAL_SHARED_LIBRARIES := liblog libcutils
LOCAL_CERTIFICATE := platform
ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 26 && echo OK),OK)
LOCAL_PROPRIETARY_MODULE := true
endif

LOCAL_CFLAGS += -Wno-pointer-sign \
    -Wno-pointer-sign

include $(BUILD_SHARED_LIBRARY)
