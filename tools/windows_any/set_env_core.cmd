@rem                  Copyright (C) 2012 Josh Heitzman
@rem Distributed under the Boost Software License, Version 1.0.
@rem See accompanying file LICENSE_1_0.txt or online copies at:
@rem * http://www.boost.org/LICENSE_1_0.txt
@rem * http://opensource.org/licenses/BSL-1.0
@rem * http://directory.fsf.org/wiki/License:Boost1.0
@rem * http://en.wikipedia.org/wiki/Boost_Software_License

@if not "%grail42_cmd_verbose_logging"=="2" echo off

if "%grail42_root%"=="" set grail42_root=%~dp0
set grail42_root=%grail42_root:\core\tools\windows_any\=%
if not exist %grail42_root% set grail42_root=
if not exist %grail42_root%\core\tools\windows_any\ set grail42_root=

setlocal ENABLEDELAYEDEXPANSION

if "%grail42_root%"=="" goto Usage
call "%~dp0\ensure_argument_not_usage_request.cmd" %1
if ERRORLEVEL 1 goto Usage

goto ArgsValidated

:Usage
echo Sets environment variables for the core project.
echo.
echo SET_ENV_CORE
echo.
echo The environment variable grail42_root may need to be explicilty set prior to execution, 
echo although it can usually be inferred.
echo.
echo For example:
echo.
echo set grail42_root=c:\grail42
echo SET_ENV_CORE
endlocal & CMD /C EXIT 1
goto :EOF

:ArgsValidated
endlocal
set grail42_core_root=%grail42_root%\core
set grail42_core_cmd=%grail42_core_root%\tools\windows_any
