@echo off
pushd %~dp0\..\
mkdir Build
pushd Build
cmake ..
popd
popd
pause
