@echo off

set LOCAL_CFLAGS=-Werror -std=c++11 -DEMSCRIPTEN_BUILD

set LOCAL_C_INCLUDES=-I ../source/ -I ../vendor/

set LOCAL_SRC_FILES=utils/esUtil.cpp ^
utils/FileUtilHtml5.cpp ^
utils/ImageUtilHtml5.cpp ^
utils/LogUtilHtml5.cpp ^
utils/TimeUtilHtml5.cpp ^
../source/base/IMgr.cpp ^
../source/font/BitmapFont.cpp ^
../source/font/FontMgr.cpp ^
../source/font/IFont.cpp ^
../source/model/MeshData.cpp ^
../source/model/ModelMgr.cpp ^
../source/input/TouchDelegateMgr.cpp ^
../source/render/IRenderer.cpp ^
../source/render/RenderBuffer.cpp ^
../source/render/RendererGl2.cpp ^
../source/render/RendererGl3.cpp ^
../source/render/RenderObject.cpp ^
../source/render/RenderTarget.cpp ^
../source/render/Shader.cpp ^
../source/render/Texture.cpp ^
../source/render/VertexAttributes.cpp ^
../source/ui/Label.cpp ^
../source/utils/BufferStream.cpp ^
../source/utils/FileUtil.cpp ^
../source/utils/ImageUtil.cpp ^
../source/utils/StringBuilder.cpp ^
../source/utils/StringUtil.cpp ^
../source/Framework.cpp ^
../source/IApp.cpp


emcc %LOCAL_CFLAGS% %LOCAL_C_INCLUDES% %LOCAL_SRC_FILES% -o ../bin/libSpank.bc

