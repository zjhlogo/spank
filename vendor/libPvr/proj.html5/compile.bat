@echo off

set LOCAL_CFLAGS=-std=c++11 -DBUILD_OGLES2

set LOCAL_C_INCLUDES=-I ../../../source/

set LOCAL_SRC_FILES=../source/PVRTDecompress.cpp ^
../source/PVRTError.cpp ^
../source/PVRTFixedPoint.cpp ^
../source/PVRTgles2Ext.cpp ^
../source/PVRTMatrixF.cpp ^
../source/PVRTMatrixX.cpp ^
../source/PVRTMisc.cpp ^
../source/PVRTTexture.cpp ^
../source/PVRTTextureAPI.cpp


emcc %LOCAL_CFLAGS% %LOCAL_C_INCLUDES% %LOCAL_SRC_FILES% -o ../../../bin/libPvr.bc
