@rem                  Copyright (C) 2012 Josh Heitzman
@rem Distributed under the Boost Software License, Version 1.0.
@rem See accompanying file LICENSE_1_0.txt or online copies at:
@rem * http://www.boost.org/LICENSE_1_0.txt
@rem * http://opensource.org/licenses/BSL-1.0
@rem * http://directory.fsf.org/wiki/License:Boost1.0
@rem * http://en.wikipedia.org/wiki/Boost_Software_License

@if not "%grail42_cmd_verbose_logging"=="2" echo off
setlocal ENABLEDELAYEDEXPANSION

if "%1"=="" goto Usage
call "%~dp0\ensure_argument_not_usage_request.cmd" %1
if ERRORLEVEL 1 goto Usage

goto ArgsValidated

:Usage
echo Waits the specified number of seconds before exiting.
echo.
echo SLEEP seconds
echo.
echo seconds         Number of seconds to wait.
echo.
echo For example:
echo.
echo SLEEP 3
endlocal & CMD /C EXIT 1
goto :EOF

:ArgsValidated

set /a retries=%1+1

rem Wait specified number of seconds via a mechanism that works on XP
rem When Win 7 can be the minimum target then can instead do:
rem waitFor /T %1 %RANDOM%%RANDOM%%RANDOM%%RANDOM% >nul 2>&1
ping -n %retries% 127.0.0.1 > nul

rem REVIEW The author has not observed ping set ERRORLEVEL to other than 0 when
rem succssful, so not overriding here.  That said testing has been limited.