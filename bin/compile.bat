@echo off

emcc libHelloGLES3.bc libPvr.bc libSpank.bc libTinyxml2.bc -o HelloGLES3.html --preload-file data/
