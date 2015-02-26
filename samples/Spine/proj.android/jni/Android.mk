LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := app_spine
LOCAL_CFLAGS    := -Werror

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../source \
                    $(LOCAL_PATH)/../../../common \
                    $(LOCAL_PATH)/../../../../source \
                    $(LOCAL_PATH)/../../../../vendor \
                    $(LOCAL_PATH)/../../../../vendor/libSpine/source \


LOCAL_SRC_FILES := main.cpp \
                   ../../../common/BaseApp.cpp \
                   ../../source/SpineApp.cpp \


LOCAL_WHOLE_STATIC_LIBRARIES := spank spine

include $(BUILD_SHARED_LIBRARY)

$(call import-module,proj.android/jni)
$(call import-module,libSpine/proj.android/jni)
