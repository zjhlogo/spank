LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := spank

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../source \
                    $(LOCAL_PATH)/../../vendor \


LOCAL_CFLAGS    := -Werror

LOCAL_SRC_FILES := utils/FileUtilAndroid.cpp \
                   utils/LogUtilAndroid.cpp \
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
                   ../../source/Framework.cpp \
                   ../../source/IApp.cpp \


LOCAL_EXPORT_LDLIBS := -llog -lGLESv3 -lEGL -landroid

LOCAL_WHOLE_STATIC_LIBRARIES := pvr


include $(BUILD_STATIC_LIBRARY)

$(call import-module,libPvr/proj.android/jni)
