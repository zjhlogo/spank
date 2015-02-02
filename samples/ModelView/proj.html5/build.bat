@echo off
cd ..\..\..\
set ROOT_PATH=%cd%

@echo "start compile ModelView"
cd %ROOT_PATH%\samples\ModelView\proj.html5
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

@echo "start link ModelView"
cd %ROOT_PATH%\samples\ModelView\proj.html5
call link.bat

@echo "build end"
cd %ROOT_PATH%\samples\ModelView\proj.html5
