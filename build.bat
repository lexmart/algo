@echo off
set file_name=%1

cd build
cl %file_name% -Zi

cd ..