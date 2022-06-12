REM This is not really a make file.  It's a batch file.  I've named it make because I'm so used to using make.
REM This creates a resource file from resource.rc and then compiles

rc resource.rc
cl winmain.c log.c mainwindow.c controlDialogs.c motor.c resource.res /link user32.lib gdi32.lib gdiplus.lib comctl32.lib
winmain.exe