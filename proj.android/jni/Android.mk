LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := spank

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../source
LOCAL_CFLAGS    := -Werror

LOCAL_SRC_FILES := utils/LogUtilAndroid.cpp \
                   utils/TimeUtilAndroid.cpp \
                   ../../source/base/IMgr.cpp \
                   ../../source/render/IRenderer.cpp \
                   ../../source/render/RenderBuffer.cpp \
                   ../../source/render/RendererGl2.cpp \
                   ../../source/render/RendererGl3.cpp \
                   ../../source/render/RenderObject.cpp \
                   ../../source/render/RenderTarget.cpp \
                   ../../source/render/Shader.cpp \
                   ../../source/render/Texture.cpp \
                   ../../source/utils/LogUtil.cpp \
                   ../../source/utils/TimeUtil.cpp \
                   ../../source/Framework.cpp \
                   ../../source/IApp.cpp \


include $(BUILD_STATIC_LIBRARY)
