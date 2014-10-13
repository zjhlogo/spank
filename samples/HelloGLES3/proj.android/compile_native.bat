@echo off

set NDK_MODULE_PATH=../../..;../../../vendor
echo %NDK_MODULE_PATH%
ndk-build.cmd -C .
