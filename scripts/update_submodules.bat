@echo off

echo [INFO] updating submodules...
git submodule update --remote --merge --recursive

echo [INFO] submodules updated.
pause
