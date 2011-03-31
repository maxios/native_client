rem Copyright (c) 2011 The Native Client Authors. All rights reserved.
rem Use of this source code is governed by a BSD-style license that can be
rem found in the LICENSE file.

echo on

set GYP_MSVS_VERSION=2008

REM Blow away path for now if on the bots (to be more hermetic).
if %BUILDBOT_SLAVENAME% equ "" goto SkipPathReset
set PATH=e:\b\depot_tools;e:\b\depot_tools\python_bin
set PATH=%PATH%;C:\WINDOWS\system32;C:\WINDOWS\system32\WBEM
set PATH=%PATH%;e:\b\build_internal\tools
:SkipPathReset

rem Adding in both the 32-bit on 64-bit program files install location for both
rem MSVS2008 and MSVS2005 including the team tools.

set MSVS8=c:\Program Files\Microsoft Visual Studio 8.0
set MSVS8_X86=c:\Program Files (x86)\Microsoft Visual Studio 8.0
set MSVS9=c:\Program Files\Microsoft Visual Studio 9.0
set MSVS9_X86=c:\Program Files (x86)\Microsoft Visual Studio 9.0

set PATH=%PATH%;%MSVS9%\VC
set PATH=%PATH%;%MSVS9_X86%\VC
set PATH=%PATH%;%MSVS9%\Common7\Tools
set PATH=%PATH%;%MSVS9_X86%\Common7\Tools
set PATH=%PATH%;%MSVS9%\Team Tools\Performance Tools
set PATH=%PATH%;%MSVS9_X86%\Team Tools\Performance Tools

set PATH=%PATH%;%MSVS8%\VC
set PATH=%PATH%;%MSVS8_X86%\VC
set PATH=%PATH%;%MSVS8%\Common7\Tools
set PATH=%PATH%;%MSVS8_X86%\Common7\Tools
set PATH=%PATH%;%MSVS8%\Team Tools\Performance Tools
set PATH=%PATH%;%MSVS8_X86%\Team Tools\Performance Tools
