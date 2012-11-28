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
if "%android_sdk_root%"=="" goto Usage
if "%grail42_core_cmd%"=="" goto Usage
call "%grail42_core_cmd%\ensure_argument_not_usage_request.cmd" %1
if ERRORLEVEL 1 goto Usage

goto ArgsValidated

:Usage
echo Starts the activity for an Android faux console app on the current emulator
echo or device, waits for execution to complete, and displays the stdout and 
echo stderr from the app on the local command line.
echo.
echo RUN_APP package activity
echo.
echo package       The identity of the package containing the activity to start.
echo.
echo activity      The identity of the faux console activity to start.
echo.
echo The activity specified must fulfill the requirements of a faux console
echo activity.
echo.
echo Prior to execution:
echo   * The adb server should be running and connected to a single emulator or
echo     device prior to execution.
echo   * The android_sdk_root environment variable must be set the root to the
echo     Android SDK.
echo   * The grail42_core_cmd environment variable echo is required to be set
echo     by running set_env_core.cmd.
echo.
echo If the grail42_cmd_verbose_logging environment variable is set then 
echo additional diagnostic output will be emitted.
echo.
echo For example:
echo.
echo set android_sdk_root=C:\adt-bundle-windows-x86\sdk
echo RUN_APP com.example.plasma .Plasma
endlocal & CMD /C EXIT 1
goto :EOF

:ArgsValidated
rem Clear the current log state
"%android_sdk_root%\platform-tools\adb.exe" logcat -c
rem Start the activity in the package
"%android_sdk_root%\platform-tools\adb.exe" shell am start -n %1/%2
if ERRORLEVEL 1 endlocal & CMD /C EXIT 1 & goto :EOF

:WaitForLogToHaveEntries
if defined grail42_cmd_verbose_logging echo WaitForLogToHaveEntries
"%android_sdk_root%\platform-tools\adb.exe" logcat -g | findstr /C:"0Kb consumed" > nul
if ERRORLEVEL 1 goto LogHasEntries
call "%grail42_core_cmd%\sleep.cmd" 1
goto WaitForLogToHaveEntries
:LogHasEntries
if defined grail42_cmd_verbose_logging echo LogHasEntries


set iterations=1
:WaitForRemoteAppExecutionToStart
if defined grail42_cmd_verbose_logging echo WaitForRemoteAppExecutionToStart
rem These identifiers are emitted by the FauxConsoleActivity included in the template and are used to determine that app has actually started.
rem It is possible for the app to start and not emit these identifier due to a preceding error.
"%android_sdk_root%\platform-tools\adb.exe" logcat -d -v raw 13380324612F4E3184624E7AD706141A:I *:S | findstr "4D85BA47C2364027A09FBF016A5C2C2A" > nul
if not ERRORLEVEL 1 goto RemoteAppExecutionStarted
if /i %iterations% GEQ 4 (
	echo.
    echo ERROR - app execution start was not detected after %iterations% attempts.  Dumping log data.
	echo.
	if defined grail42_cmd_verbose_logging ("%android_sdk_root%\platform-tools\adb.exe" logcat -d) else ("%android_sdk_root%\platform-tools\adb.exe" logcat -d -v raw stderr:I stdout:I *:S)
	endlocal & CMD /C EXIT 1 & goto :EOF
)
call "%grail42_core_cmd%\sleep.cmd" 1
set /a iterations=%iterations%+1
goto WaitForRemoteAppExecutionToStart
:RemoteAppExecutionStarted
if defined grail42_cmd_verbose_logging echo RemoteAppExecutionStarted


:WaitForRemoteAppExecutionToComplete
if defined grail42_cmd_verbose_logging echo WaitForRemoteAppExecutionToComplete
rem These identifiers are emitted by the FauxConsoleActivity included in the template and are used to determine that app has finished execution.
rem It is possible for the app to terminate and not emit these identifier due to a preceding error.
"%android_sdk_root%\platform-tools\adb.exe" logcat -d -v raw 13380324612F4E3184624E7AD706141A:I *:S | findstr "DAB25FDC5A974392AA39ED7928A31561" > nul
if not ERRORLEVEL 1 goto RemoteAppExecutionComplete
call "%grail42_core_cmd%\sleep.cmd" 1
goto WaitForRemoteAppExecutionToComplete
:RemoteAppExecutionComplete
if defined grail42_cmd_verbose_logging echo RemoteAppExecutionComplete

rem Scan through the log lines and only emit the lines between the start and end markers.
set enable_stdout_echo=
set remote_exit_code=0
for /f "delims=" %%i in ('"%android_sdk_root%\platform-tools\adb.exe" logcat -d -v raw 13380324612F4E3184624E7AD706141A:I stderr:I stdout:I *:S') do (call "%grail42_core_cmd%\if_equ_set.cmd" %%i ECD3B7A023654F9D99F2EF3D4AA33925 enable_stdout_echo) && (if "!enable_stdout_echo!"=="1" echo %%i) && (call "%grail42_core_cmd%\if_equ_set.cmd" %%i 4D85BA47C2364027A09FBF016A5C2C2A enable_stdout_echo 1) && (for /f "tokens=1,2 delims=:" %%r in ("%%i") do call "%grail42_core_cmd%\if_equ_set.cmd" %%r DAB25FDC5A974392AA39ED7928A31561 remote_exit_code %%s)
endlocal & CMD /C EXIT %remote_exit_code%
