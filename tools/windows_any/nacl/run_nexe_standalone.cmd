@rem                  Copyright (C) 2012 Josh Heitzman
@rem Distributed under the Boost Software License, Version 1.0.
@rem See accompanying file LICENSE_1_0.txt or online copies at:
@rem * http://www.boost.org/LICENSE_1_0.txt
@rem * http://opensource.org/licenses/BSL-1.0
@rem * http://directory.fsf.org/wiki/License:Boost1.0
@rem * http://en.wikipedia.org/wiki/Boost_Software_License

@if not "%grail42_cmd_verbose_logging"=="2" echo off
setlocal ENABLEDELAYEDEXPANSION

if not defined NACLLOG set NACLLOG=%TEMP%\nacllog.txt

if "%1"=="" goto Usage
if "%nacl_sdk_root%"=="" goto Usage
if "%grail42_core_cmd%"=="" goto Usage
call "%grail42_core_cmd%\ensure_argument_not_usage_request.cmd" %1
if ERRORLEVEL 1 goto Usage

if not exist "%1" (echo The specified nexe does not exist at "%1") & goto Usage

goto ArgsValidated

:Usage
echo Starts a Native Client nexe in sel_ldr rather than in Chrome.
echo.
echo RUN_NEXE_STANDALONE native_client_executable
echo.
echo native_client_executable      Native Client nexe file to be executed.
echo.
echo The nexe file must have a main function and currently it must be 64-bit.
echo.
echo Prior to execution:
echo   * The nacl_sdk_root environment variable must be set the root to the
echo     Pepper SDK.
echo   * The grail42_core_cmd environment variable is required to be set by
echo     running set_env_core.cmd.
echo.
echo After execution, logs from the Native Client system binaries can be found 
echo at the file %NACLLOG%.
echo.
echo If the grail42_cmd_verbose_logging environment variable is set then 
echo additional diagnostic output will be emitted.
echo.
echo For example:
echo.
echo set nacl_sdk_root=C:\nacl_sdk\pepper_23
echo RUN_NEXE_STANDALONE hello_world_console_64.nexe
endlocal & CMD /C EXIT 1
goto :EOF

:ArgsValidated

rem Clear the current log state
if exist %NACLLOG% del %NACLLOG%

rem Ensure that stdout and stderr won't be redirected to files
if defined NACL_EXE_STDOUT set NACL_EXE_STDOUT=
if defined NACL_EXE_STDERR set NACL_EXE_STDERR=

if defined grail42_cmd_verbose_logging set NACLLOG=

%nacl_sdk_root%\tools\sel_ldr_x86_64.exe -B %nacl_sdk_root%\tools\irt_core_x86_64.nexe "%1"