@echo off
copy examples\makefile + jbl\makefile makefile
xcopy jbl %libs%\jbl\ /E /Y /Q