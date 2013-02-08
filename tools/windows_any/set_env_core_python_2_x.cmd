@rem                  Copyright (C) 2012 Josh Heitzman
@rem Distributed under the Boost Software License, Version 1.0.
@rem See accompanying file LICENSE_1_0.txt or online copies at:
@rem * http://www.boost.org/LICENSE_1_0.txt
@rem * http://opensource.org/licenses/BSL-1.0
@rem * http://directory.fsf.org/wiki/License:Boost1.0
@rem * http://en.wikipedia.org/wiki/Boost_Software_License

@if not "%grail42_cmd_verbose_logging"=="2" echo off
if "%grail42_core_root%"=="" call "%~dp0\set_env_core.cmd"
setlocal ENABLEDELAYEDEXPANSION

if "%1"=="" goto Usage
if "%grail42_core_root%"=="" goto Usage
call "%~dp0\ensure_argument_not_usage_request.cmd" %1
if ERRORLEVEL 1 goto Usage

if not exist "%1" (echo The specified Python executable does not exist at "%1") & goto Usage

goto ArgsValidated

:Usage
echo Sets environment variables for the core project.
echo.
echo SET_ENV_CORE_PYTHON_2_X path_to_python
echo.
echo path_to_python    The path of a Python 2.x interpreter executable.
echo.
echo set_env_core.cmd should be run prior to execution.
echo.
echo For example:
echo.
echo set grail42_root=c:\grail42
echo SET_ENV_CORE
echo SET_ENV_CORE_PYTHON_2_X c:\python27\python.exe
endlocal & CMD /C EXIT 1
goto :EOF

:ArgsValidated
endlocal

set grail42_python2_x_exe=%1
if defined PYTHONPATH (set PYTHONPATH=%PYTHONPATH%;%grail42_core_root%\library\python_2_x) else (set PYTHONPATH=%grail42_core_root%\library\python_2_x)

