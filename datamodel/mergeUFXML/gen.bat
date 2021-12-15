del /q ..\envGenerated\*
del /q ..\sqlGenerated\*
@call amake mergeUFXML.prj
@call nmake
@call nmake -f makefile.gen