@echo off
cd ..\..\..\
set ROOT_PATH=%cd%

@echo "start compile Spine"
cd %ROOT_PATH%\samples\Spine\proj.html5
call compile.bat

@echo "start compile spank"
cd %ROOT_PATH%\proj.html5
call compile.bat

@echo "start compile libPvr"
cd %ROOT_PATH%\vendor\libPvr\proj.html5
call compile.bat

@echo "start compile libTinyxml2"
cd %ROOT_PATH%\vendor\libTinyxml2\proj.html5
call compile.bat

@echo "start compile libSpine"
cd %ROOT_PATH%\vendor\libSpine\proj.html5
call compile.bat

@echo "start link Spine"
cd %ROOT_PATH%\samples\Spine\proj.html5
call link.bat

@echo "build end"
cd %ROOT_PATH%\samples\Spine\proj.html5
