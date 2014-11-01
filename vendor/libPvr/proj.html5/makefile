CC=emcc

SOURCES=../source/PVRTDecompress.cpp \
../source/PVRTError.cpp \
../source/PVRTFixedPoint.cpp \
../source/PVRTgles2Ext.cpp \
../source/PVRTMatrixF.cpp \
../source/PVRTMatrixX.cpp \
../source/PVRTMisc.cpp \
../source/PVRTTexture.cpp \
../source/PVRTTextureAPI.cpp

EXPORTS_FILE=makefile_exprots.txt

LOCAL_C_FLAGS=-Werror -std=c++11 -DBUILD_OGLES2

LOCAL_C_INCLUDES=-I ../../../source/

OUTPUT=libPvr.bc

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(SOURCES) -s EXPORTED_FUNCTIONS=@$(EXPORTS_FILE) $(LOCAL_C_FLAGS) $(LOCAL_C_INCLUDES) -o ../../../bin/$(OUTPUT)

