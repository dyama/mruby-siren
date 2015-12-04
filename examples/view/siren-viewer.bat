@echo off
title siren viewer
SET "SCRIPTPATH=%~dp0"

IF "%1"=="" (
echo No file specified.
echo Please drop a BRep file to BAT file icon.
pause
) else (
echo Convert BRep file to JavaScript code for three.js.
%SCRIPTPATH%\..\..\siren %SCRIPTPATH%\brep2js.rb "%1"
echo Opening WWW browser.
start %SCRIPTPATH%\siren-viewer.html
)