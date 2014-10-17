@echo off

set LOCAL_CFLAGS=-std=c++11

set LOCAL_C_INCLUDES=

set LOCAL_SRC_FILES=../source/tinyxml2.cpp


emcc %LOCAL_CFLAGS% %LOCAL_C_INCLUDES% %LOCAL_SRC_FILES% -o ../../../bin/libTinyxml2.bc
