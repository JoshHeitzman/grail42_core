@rem                  Copyright (C) 2012 Josh Heitzman
@rem Distributed under the Boost Software License, Version 1.0.
@rem See accompanying file LICENSE_1_0.txt or online copies at:
@rem * http://www.boost.org/LICENSE_1_0.txt
@rem * http://opensource.org/licenses/BSL-1.0
@rem * http://directory.fsf.org/wiki/License:Boost1.0
@rem * http://en.wikipedia.org/wiki/Boost_Software_License

@if not "%grail42_cmd_verbose_logging"=="2" echo off
setlocal ENABLEDELAYEDEXPANSION

if not defined NACL_EXE_STDOUT set NACL_EXE_STDOUT=%temp%\stdout.txt
if not defined NACL_EXE_STDERR set NACL_EXE_STDERR=%temp%\stderr.txt
if not defined NACLLOG set NACLLOG=%temp%\nacllog.txt

if "%nacl_sdk_root%"=="" goto Usage
if "%grail_python2_x_exe%"=="" goto Usage
if "%grail42_core_cmd%"=="" goto Usage
call "%grail42_core_cmd%\ensure_argument_not_usage_request.cmd" %1
if ERRORLEVEL 1 goto Usage

if not "%1"=="" if not exist "%1" (echo The specified directory does not exist at "%1") & goto Usage

goto ArgsValidated

:Usage
echo Starts a Native Client nexe in Chrome after starting a Python web server.
echo.
echo RUN_NEXE_IN_CHROME native_client_executable
echo.
echo native_client_executable      Native Client nexe file to be executed.
echo.
echo The nexe file must have a pp::CreateModule function and it must not have a 
echo main function.  Currently it must be 64-bit.
echo.
echo Prior to execution:
echo   * The nacl_sdk_root environment variable must be set the root to the
echo     Pepper SDK.
echo   * The grail_python2_x_exe environment variable is required to be set to
echo     to a Python 2.x EXE.
echo   * The grail42_core_cmd environment variable is required to be set by
echo     running set_env_core.cmd.
echo.
echo After Chrome closes, stdout and then stderr will emitted to the console.
echo Stdout and stderr are not interleaved as they were orginally output by the
echo nexe, as Chrome redirects each stream to a seperate file without metadata
echo that would allow them to be recombined in order.
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
echo set grail_python2_x_exe=C:\python27\python.exe
echo RUN_NEXE_IN_CHROME hello_world_console_64.nexe
endlocal & CMD /C EXIT 1
goto :EOF

:ArgsValidated

rem Start the Python web server supplied with the NaCl SDK examples.
start %grail_python2_x_exe% %nacl_sdk_root%\examples\httpd.py --no_dir_check

rem Clear the current log state
if exist %NACL_EXE_STDOUT% del %NACL_EXE_STDOUT%
if exist %NACL_EXE_STDERR% del %NACL_EXE_STDERR%
if exist %NACLLOG% del %NACLLOG%

rem Start Chrome and after it exits dump the stdout then stderr.
start /wait C:\Users\Josh\AppData\Local\Google\Chrome\Application\chrome.exe --no-sandbox --user-data-dir="./chrome_data" --enable-nacl http://localhost:5103/
if exist %NACL_EXE_STDOUT% type %NACL_EXE_STDOUT%
set NACL_EXE_STDOUT_SIZE=0
set NACL_EXE_STDERR_SIZE=0
if exist %NACL_EXE_STDOUT% (call :setfilesize %NACL_EXE_STDOUT%) & (set NACL_EXE_STDOUT_SIZE=!filesize!)
if exist %NACL_EXE_STDERR% (call :setfilesize %NACL_EXE_STDERR%) & (set NACL_EXE_STDERR_SIZE=!filesize!)
if %NACL_EXE_STDOUT_SIZE% GTR 0 if %NACL_EXE_STDERR_SIZE% GTR 0  echo Extra line
if exist %NACL_EXE_STDERR% type %NACL_EXE_STDERR%

if defined grail42_cmd_verbose_logging if exist %NACLLOG% type %NACLLOG%
rem TODO pick the exit code logged by the nexe once it is logging

%grail_python2_x_exe% -c "import urllib2;urllib2.urlopen('http://localhost:5103?quit=1')"

goto :EOF

:setfilesize
  set filesize=%~z1
  exit /b 0