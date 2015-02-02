@echo off

cd ..\..\..\bin
emcc libHelloGLES.bc libPvr.bc libSpank.bc libTinyxml2.bc -o HelloGLES.html --preload-file data/
