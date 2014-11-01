CC=emcc

SOURCES=../source/tinyxml2.cpp

EXPORTS_FILE=makefile_exprots.txt

LOCAL_C_FLAGS=-Werror -std=c++11

LOCAL_C_INCLUDES=

OUTPUT=libTinyxml2.bc

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(SOURCES) -s EXPORTED_FUNCTIONS=@$(EXPORTS_FILE) $(LOCAL_C_FLAGS) $(LOCAL_C_INCLUDES) -o ../../../bin/$(OUTPUT)

