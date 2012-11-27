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
if "%2"=="" goto Usage
if "%3"=="" goto Usage
call "%~dp0\ensure_argument_not_usage_request.cmd" %1
if ERRORLEVEL 1 goto Usage

goto ArgsValidated

:Usage
echo Conditionally set the an environment variable to a value.
echo.
echo IF_EQU_SET lefthand righthand variable [value]
echo.
echo lefthand         Used on the left hand of the equality operator.
echo.
echo righthand        Used on the right hand of the equality operator.
echo.
echo variable         The name of the variable to set
echo.
echo value            Value to set the variable to.  If omitted the
echo                  variable will be unset.
echo.
echo For example:
echo.
echo SET FOO=1
echo IF_EQU_SET 1 %FOO% BAR bell
endlocal & CMD /C EXIT 1
goto :EOF

:ArgsValidated

endlocal
if %1==%2 set %3=%4