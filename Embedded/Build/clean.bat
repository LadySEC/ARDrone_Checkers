@echo off
mingw32-make clean
del CMakeCache.txt cmake_install.cmake Makefile
rmdir /S /Q CMakeFiles