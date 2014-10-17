LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := spank

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../source \
                    $(LOCAL_PATH)/../../vendor \


LOCAL_CFLAGS    := -Werror

LOCAL_SRC_FILES := utils/FileUtilAndroid.cpp \
                   utils/ImageUtilAndroid.cpp \
                   utils/LogUtilAndroid.cpp \
                   utils/TimeUtilAndroid.cpp \
                   ../../source/base/IMgr.cpp \
                   ../../source/input/TouchDelegateMgr.cpp \
                   ../../source/render/IRenderer.cpp \
                   ../../source/render/RenderBuffer.cpp \
                   ../../source/render/RendererGl2.cpp \
                   ../../source/render/RendererGl3.cpp \
                   ../../source/render/RenderObject.cpp \
                   ../../source/render/RenderTarget.cpp \
                   ../../source/render/Shader.cpp \
                   ../../source/render/Texture.cpp \
                   ../../source/render/VertexAttributes.cpp \
                   ../../source/utils/BufferStream.cpp \
                   ../../source/utils/FileUtil.cpp \
                   ../../source/utils/ImageUtil.cpp \
                   ../../source/utils/StringBuilder.cpp \
                   ../../source/utils/StringUtil.cpp \
                   ../../source/Framework.cpp \
                   ../../source/IApp.cpp \


LOCAL_EXPORT_LDLIBS := -llog -lGLESv2 -lEGL -landroid

LOCAL_WHOLE_STATIC_LIBRARIES := pvr
LOCAL_WHOLE_STATIC_LIBRARIES += tinyxml2
LOCAL_WHOLE_STATIC_LIBRARIES += png


include $(BUILD_STATIC_LIBRARY)

$(call import-module,libPvr/proj.android/jni)
$(call import-module,libTinyxml2/proj.android/jni)
$(call import-module,libPng/proj.android/jni)
