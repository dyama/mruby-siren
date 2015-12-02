@echo off
title "siren viewer"
SET "SCRIPTPATH=%~dp0"

IF "%1"=="" (
echo No file specified.
echo Please drop a BRep file to BAT file icon.
pause
) else (
%SCRIPTPATH%\..\..\siren %SCRIPTPATH%\brep2js.rb "%1"
start %SCRIPTPATH%\siren-viewer.html
)