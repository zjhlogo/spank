@echo off

set LOCAL_CFLAGS=-std=c++11

set LOCAL_C_INCLUDES=-I ../source/ -I ../../common/ -I ../../../source/ -I ../../../vendor/  -I ../../../proj.html5/

set LOCAL_SRC_FILES=main.cpp ^
../../common/BaseApp.cpp ^
../source/ModelViewApp.cpp


emcc %LOCAL_CFLAGS% %LOCAL_C_INCLUDES% %LOCAL_SRC_FILES% -o ../../../bin/libModelView.bc
