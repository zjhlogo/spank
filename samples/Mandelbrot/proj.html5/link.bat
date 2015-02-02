@echo off

cd ..\..\..\bin
emcc libMandelbrot.bc libPvr.bc libSpank.bc libTinyxml2.bc -o Mandelbrot.html --preload-file data/
