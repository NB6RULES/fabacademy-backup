@echo off
setlocal EnableExtensions

echo ============================================
echo  Casey Rogers Dogbone Add-In Installer
echo  Source: https://github.com/caseycrogers/Dogbone
echo  (redirects to DVE2000/Dogbone - same lineage)
echo ============================================
echo.

set "ADDINS_DIR=%APPDATA%\Autodesk\Autodesk Fusion 360\API\AddIns"
set "PLUGIN_DIR=%ADDINS_DIR%\Dogbone"
set "ZIP_URL=https://github.com/caseycrogers/Dogbone/archive/refs/heads/master.zip"
set "TMP_ZIP=%TEMP%\dogbone-master.zip"
set "TMP_EXTRACT=%TEMP%\dogbone-extract"

echo IMPORTANT: Close Autodesk Fusion 360 before continuing.
pause

if not exist "%ADDINS_DIR%" (
    echo Creating AddIns directory: "%ADDINS_DIR%"
    mkdir "%ADDINS_DIR%"
    if errorlevel 1 (
        echo ERROR: Could not create AddIns directory.
        goto :fail
    )
)

if exist "%PLUGIN_DIR%" (
    echo Removing previous install at "%PLUGIN_DIR%"...
    rmdir /s /q "%PLUGIN_DIR%"
)

if exist "%TMP_EXTRACT%" rmdir /s /q "%TMP_EXTRACT%"
if exist "%TMP_ZIP%"     del   /q     "%TMP_ZIP%"

echo Downloading Dogbone master.zip ...
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
    "[Net.ServicePointManager]::SecurityProtocol=[Net.SecurityProtocolType]::Tls12;" ^
    "Invoke-WebRequest -Uri '%ZIP_URL%' -OutFile '%TMP_ZIP%' -UseBasicParsing -MaximumRedirection 5"
if errorlevel 1 (
    echo ERROR: Download failed.
    goto :fail
)

echo Extracting to temp...
mkdir "%TMP_EXTRACT%"
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
    "Expand-Archive -Path '%TMP_ZIP%' -DestinationPath '%TMP_EXTRACT%' -Force"
if errorlevel 1 (
    echo ERROR: Extraction failed.
    goto :fail
)

echo Locating Dogbone.manifest inside extracted archive...
set "SRC_DIR="
for /d %%D in ("%TMP_EXTRACT%\*") do (
    if exist "%%~fD\Dogbone.manifest" set "SRC_DIR=%%~fD"
)
if not defined SRC_DIR (
    echo ERROR: Could not find Dogbone.manifest in the archive.
    goto :fail
)
echo Found source: "%SRC_DIR%"

echo Installing to "%PLUGIN_DIR%" ...
mkdir "%PLUGIN_DIR%"
xcopy /e /i /h /y "%SRC_DIR%\*" "%PLUGIN_DIR%\" >nul
if errorlevel 1 (
    echo ERROR: Copy failed.
    goto :fail
)

if not exist "%PLUGIN_DIR%\Dogbone.manifest" (
    echo ERROR: Dogbone.manifest not present at "%PLUGIN_DIR%\Dogbone.manifest" after copy.
    goto :fail
)

echo Cleaning up temp files...
del /q "%TMP_ZIP%" >nul 2>&1
rmdir /s /q "%TMP_EXTRACT%" >nul 2>&1

echo.
echo ============================================
echo  Install complete.
echo  Manifest: %PLUGIN_DIR%\Dogbone.manifest
echo.
echo  Next steps in Fusion 360:
echo    1. Launch Fusion 360.
echo    2. Press Shift+S  (or Tools/Utilities ^> ADD-INS ^> Scripts and Add-Ins).
echo    3. Add-Ins tab -^> select "Dogbone" -^> Run.
echo       Tick "Run on Startup" if you want it auto-loaded.
echo.
echo  To remove: delete the folder
echo    %PLUGIN_DIR%
echo ============================================
echo.
pause
exit /b 0

:fail
echo.
echo Installation FAILED. See messages above.
pause
exit /b 1
