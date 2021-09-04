
:
:	FileName:		Win_ClearRm.bat
:	Author:			Liam.Nurx
:	Date:			2021.08.28
:

:@ECHO OFF

:make -f win_makefile clean
make -f win_makefile rm 

rm -rf ReviewC.exe

@ECHO OFF
PAUSE