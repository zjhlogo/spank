LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hello_gles3
LOCAL_CFLAGS    := -Werror

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../source \
                    $(LOCAL_PATH)/../../../../source \


LOCAL_SRC_FILES := main.cpp \
                   ../../source/HelloGLES3App.cpp \


LOCAL_WHOLE_STATIC_LIBRARIES := spank

include $(BUILD_SHARED_LIBRARY)

$(call import-module,proj.android/jni)
