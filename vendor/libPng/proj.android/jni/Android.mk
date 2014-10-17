LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := png

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../source

LOCAL_CFLAGS    := -Werror

LOCAL_SRC_FILES :=../../source/png.c \
                   ../../source/pngerror.c \
                   ../../source/pngget.c \
                   ../../source/pngmem.c \
                   ../../source/pngpread.c \
                   ../../source/pngread.c \
                   ../../source/pngrio.c \
                   ../../source/pngrtran.c \
                   ../../source/pngrutil.c \
                   ../../source/pngset.c \
                   ../../source/pngtrans.c \
                   ../../source/pngwio.c \
                   ../../source/pngwrite.c \
                   ../../source/pngwtran.c \
                   ../../source/pngwutil.c \


LOCAL_EXPORT_LDLIBS := -lz


include $(BUILD_STATIC_LIBRARY)
