LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := model_view
LOCAL_CFLAGS    := -Werror

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../source \
                    $(LOCAL_PATH)/../../../common \
                    $(LOCAL_PATH)/../../../../source \
                    $(LOCAL_PATH)/../../../../vendor \


LOCAL_SRC_FILES := main.cpp \
                   ../../../common/BaseApp.cpp \
                   ../../source/ModelViewApp.cpp \


LOCAL_WHOLE_STATIC_LIBRARIES := spank

include $(BUILD_SHARED_LIBRARY)

$(call import-module,proj.android/jni)
