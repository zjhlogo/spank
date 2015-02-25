@echo off

cd ..\..\..\bin
emcc libSpineApp.bc libPvr.bc libSpank.bc libTinyxml2.bc libSpine.bc -o Spine.html --preload-file data/
