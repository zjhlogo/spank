@echo off

set NDK_MODULE_PATH=../../..
echo %NDK_MODULE_PATH%
ndk-build.cmd -C .
