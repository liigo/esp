# Microsoft Developer Studio Project File - Name="esp_core" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=esp_core - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "esp_core.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "esp_core.mak" CFG="esp_core - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "esp_core - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "esp_core - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "esp_core - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "APR_DECLARE_STATIC" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\esp-core.lib"

!ELSEIF  "$(CFG)" == "esp_core - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "LOG4C_ENABLE" /D "APR_DECLARE_STATIC" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\esp-core-debug.lib"

!ENDIF 

# Begin Target

# Name "esp_core - Win32 Release"
# Name "esp_core - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\esp_clientapi.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_dollarexpr.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_errors.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_globals.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_internal.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_log.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_managers.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_objects.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_prop.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_serverapi.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_session.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_template.cpp
# End Source File
# Begin Source File

SOURCE=.\esp_utils.cpp
# End Source File
# Begin Source File

SOURCE="..\other\html-parser\HtmlParser.cpp"
# End Source File
# Begin Source File

SOURCE=.\md5.cpp
# End Source File
# Begin Source File

SOURCE=.\string_util.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\esp.h
# End Source File
# Begin Source File

SOURCE=.\esp_clientapi.h
# End Source File
# Begin Source File

SOURCE=.\esp_dollarexpr.h
# End Source File
# Begin Source File

SOURCE=.\esp_errors.h
# End Source File
# Begin Source File

SOURCE=.\esp_globals.h
# End Source File
# Begin Source File

SOURCE=.\esp_internal.h
# End Source File
# Begin Source File

SOURCE=.\esp_log.h
# End Source File
# Begin Source File

SOURCE=.\esp_managers.h
# End Source File
# Begin Source File

SOURCE=.\esp_objects.h
# End Source File
# Begin Source File

SOURCE=.\esp_prop.h
# End Source File
# Begin Source File

SOURCE=.\esp_serverapi.h
# End Source File
# Begin Source File

SOURCE=.\esp_session.h
# End Source File
# Begin Source File

SOURCE=.\esp_template.h
# End Source File
# Begin Source File

SOURCE=.\esp_utils.h
# End Source File
# Begin Source File

SOURCE="..\other\html-parser\HtmlParser.h"
# End Source File
# Begin Source File

SOURCE=.\md5.h
# End Source File
# Begin Source File

SOURCE=.\requestinfoindex.h
# End Source File
# Begin Source File

SOURCE=.\stl_hash_map.h
# End Source File
# Begin Source File

SOURCE=.\string_util.h
# End Source File
# End Group
# End Target
# End Project
