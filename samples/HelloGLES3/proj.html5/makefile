CC=emcc

SOURCES=main.cpp \
../../common/BaseApp.cpp \
../source/HelloGLES3App.cpp

EXPORTS_FILE=makefile_exprots.txt

LOCAL_C_FLAGS=-Werror -std=c++11

LOCAL_C_INCLUDES=-I ../source/ -I ../../common/ -I ../../../source/ -I ../../../vendor/  -I ../../../proj.html5/

OUTPUT=libHelloGLES3.bc

$(OUTPUT): $(SOURCES)
	$(CC) $(SOURCES) -s EXPORTED_FUNCTIONS=@$(EXPORTS_FILE) $(LOCAL_C_FLAGS) $(LOCAL_C_INCLUDES) -o ../../../bin/$(OUTPUT)

libPvr: ../../../bin/libPvr.bc
	cd ../../../vendor/libPvr/proj.html5 && $(MAKE) all

libSpank: ../../../bin/libSpank.bc
	cd ../../../proj.html5 && $(MAKE) all

libTinyxml2: ../../../bin/libTinyxml2.bc
	cd ../../../vendor/libTinyxml2/proj.html5 && $(MAKE) all

all: $(OUTPUT) libPvr libSpank libTinyxml2
	cd ../../../bin && $(CC) $(OUTPUT) libPvr.bc libSpank.bc libTinyxml2.bc -o HelloGLES3.html --preload-file data/

