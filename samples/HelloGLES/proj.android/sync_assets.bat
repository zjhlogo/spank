@echo off

rmdir /S /Q assets
mkdir assets
mkdir assets\data
xcopy ..\..\..\bin\data\*.* assets\data\ /s /e
