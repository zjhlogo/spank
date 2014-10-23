@echo off

cd ..\..\..\bin
emcc libModelView.bc libPvr.bc libSpank.bc libTinyxml2.bc -o ModelView.html --preload-file data/
