LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := pvr

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../source \
                    $(LOCAL_PATH)/../../../../source \


LOCAL_CFLAGS    := -Werror -DBUILD_OGLES3

LOCAL_SRC_FILES := ../../source/PVRTDecompress.cpp \
                   ../../source/PVRTError.cpp \
                   ../../source/PVRTFixedPoint.cpp \
                   ../../source/PVRTgles3Ext.cpp \
                   ../../source/PVRTMatrixF.cpp \
                   ../../source/PVRTMatrixX.cpp \
                   ../../source/PVRTMisc.cpp \
                   ../../source/PVRTTexture.cpp \
                   ../../source/PVRTTextureAPI.cpp \


LOCAL_EXPORT_LDLIBS := -lGLESv3 -lEGL


include $(BUILD_STATIC_LIBRARY)
