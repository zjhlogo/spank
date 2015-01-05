@echo off

cd ..\..\..\bin
emcc libHelloGLES3.bc libPvr.bc libSpank.bc libTinyxml2.bc -o Mandelbrot.html --preload-file data/
