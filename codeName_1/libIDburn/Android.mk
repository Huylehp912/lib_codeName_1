# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# the purpose of this sample is to demonstrate how one can
# generate two distinct shared libraries and have them both
# uploaded in
#

LOCAL_PATH:= $(call my-dir)

# shared lib, which will be built shared

include $(CLEAR_VARS)

LOCAL_MODULE    := libIDburn_d

LOCAL_SRC_FILES := IDburner.c

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \
        libnativehelper/include_jni/


LOCAL_SHARED_LIBRARIES += \
    libcutils \
    libutils \
	liblog \
	libi2c_d

LOCAL_CFLAGS += -Wno-unused-parameter \
    -Wno-pointer-sign \
	-Wno-missing-field-initializers \
	-Wno-format \
	-Wno-uninitialized \
	-Wno-parentheses \
	-Wno-incompatible-pointer-types-discards-qualifiers \
	-Wno-sign-compare

ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 26 && echo OK),OK)
LOCAL_PROPRIETARY_MODULE := true
endif


include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libIDburn_s

LOCAL_SRC_FILES := IDburner.c

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \
        libnativehelper/include_jni/


LOCAL_STATIC_LIBRARIES += \
    libcutils \
    libutils \
	liblog \
	libi2c_s

LOCAL_CFLAGS += -Wno-unused-parameter \
    -Wno-pointer-sign \
	-Wno-missing-field-initializers \
	-Wno-format \
	-Wno-uninitialized \
	-Wno-parentheses \
	-Wno-incompatible-pointer-types-discards-qualifiers \
	-Wno-sign-compare

ifeq ($(shell test $(PLATFORM_SDK_VERSION) -ge 26 && echo OK),OK)
LOCAL_PROPRIETARY_MODULE := true
endif	

include $(BUILD_STATIC_LIBRARY)
