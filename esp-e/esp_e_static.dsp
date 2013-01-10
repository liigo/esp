# Microsoft Developer Studio Project File - Name="esp_e_static" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=esp_e_static - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "esp_e_static.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "esp_e_static.mak" CFG="esp_e_static - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "esp_e_static - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "esp_e_static - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "esp_e_static - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "__E_STATIC_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"C:\Program Files\e\static_lib\esp_static.lib"
# Begin Special Build Tool
TargetPath=C:\Program Files\e\static_lib\esp_static.lib
SOURCE="$(InputPath)"
PostBuild_Desc=resym static lib
PostBuild_Cmds="C:\Program Files\e\sdk\tools\resym.exe" all infile="$(TargetPath)" outfile="$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "esp_e_static - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__E_STATIC_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"C:\Program Files\e\static_lib\esp_static.lib"
# Begin Special Build Tool
TargetPath=C:\Program Files\e\static_lib\esp_static.lib
SOURCE="$(InputPath)"
PostBuild_Desc=resym static lib
PostBuild_Cmds="C:\Program Files\e\sdk\tools\resym.exe" all infile="$(TargetPath)" outfile="$(TargetPath)"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "esp_e_static - Win32 Release"
# Name "esp_e_static - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\esp_e.def
# End Source File
# Begin Source File

SOURCE=.\esp_e.h
# End Source File
# Begin Source File

SOURCE=.\os.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\esp_e.cpp
# End Source File
# Begin Source File

SOURCE=.\Global_functions.hpp
# End Source File
# Begin Source File

SOURCE=.\os.cpp
# End Source File
# End Group
# Begin Group "elib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\elib_h\cmem.c
# End Source File
# Begin Source File

SOURCE=.\elib_h\elib.c
# End Source File
# Begin Source File

SOURCE=.\elib_h\elib.h
# End Source File
# Begin Source File

SOURCE=.\elib_h\fnshare.c
# End Source File
# Begin Source File

SOURCE=.\elib_h\fnshare.h
# End Source File
# Begin Source File

SOURCE=.\elib_h\krnllib.h
# End Source File
# Begin Source File

SOURCE=.\elib_h\lang.h
# End Source File
# Begin Source File

SOURCE=.\elib_h\lib2.h
# End Source File
# Begin Source File

SOURCE=.\elib_h\mtypes.h
# End Source File
# End Group
# End Target
# End Project
