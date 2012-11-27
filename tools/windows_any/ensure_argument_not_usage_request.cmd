@rem                  Copyright (C) 2012 Josh Heitzman
@rem Distributed under the Boost Software License, Version 1.0.
@rem See accompanying file LICENSE_1_0.txt or online copies at:
@rem * http://www.boost.org/LICENSE_1_0.txt
@rem * http://opensource.org/licenses/BSL-1.0
@rem * http://directory.fsf.org/wiki/License:Boost1.0
@rem * http://en.wikipedia.org/wiki/Boost_Software_License

@if not "%grail42_cmd_verbose_logging"=="2" echo off
setlocal ENABLEDELAYEDEXPANSION

if /I "%1"=="-h" goto IsUsageRequest
if /I "%1"=="--h" goto IsUsageRequest
if /I "%1"=="-?" goto IsUsageRequest
if /I "%1"=="--?" goto IsUsageRequest
if /I "%1"=="/h" goto IsUsageRequest
if /I "%1"=="/?" goto IsUsageRequest
if /I "%1"=="/help" goto IsUsageRequest
if /I "%1"=="-help" goto IsUsageRequest
if /I "%1"=="--help" goto IsUsageRequest

endlocal & CMD /C EXIT 0
goto :EOF

:IsUsageRequest
endlocal & CMD /C EXIT 1

