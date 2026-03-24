@echo off
setlocal

cd /d "%~dp0"

set "MAIN_REPO=C:\Users\nadec\OneDrive\Desktop\FAB Academy - Nadec Biju\Git pushes\nadec-biju"
set "PUSH_REPO=C:\Users\nadec\OneDrive\Desktop\FAB Academy - Nadec Biju\Git pushes\file for pushing\nadec-biju"

echo ================================================
echo  FAB ACADEMY - AUTO PUSH
echo ================================================

:: ── 1. Prompt for commit message ─────────────────
echo.
set /p COMMIT_MSG=Enter commit message:
if "%COMMIT_MSG%"=="" (
    echo ERROR: Commit message cannot be empty. Aborting.
    exit /b 1
)

:: ── 2. Clean public folder ───────────────────────
echo.
echo [1/6] Cleaning public folder...
if exist "%MAIN_REPO%\public" (
    rd /s /q "%MAIN_REPO%\public"
    echo       Public folder deleted.
) else (
    echo       Public folder not found, skipping.
)

:: ── 3. Build site ────────────────────────────────
echo.
echo [2/6] Building Hugo site...
hugo --minify
if errorlevel 1 (
    echo ERROR: Hugo build failed. Aborting.
    exit /b 1
)
echo       Build complete.

:: ── 4. Commit and push to GitHub ─────────────────
echo.
echo [3/6] Staging and committing...
git add .
git commit -m "%COMMIT_MSG%"
echo.
echo [4/6] Pushing to GitHub...
git push github main
if errorlevel 1 (
    echo ERROR: GitHub push failed. Aborting.
    exit /b 1
)
echo       GitHub push done.

:: ── 5. Update file-for-pushing repo ──────────────
echo.
echo [5/6] Updating push repo...

:: Delete existing public folder in push repo
if exist "%PUSH_REPO%\public" (
    rd /s /q "%PUSH_REPO%\public"
    echo       Deleted old public folder in push repo.
)

:: Delete existing README files in push repo
if exist "%PUSH_REPO%\README.md" (
    del /f /q "%PUSH_REPO%\README.md"
    echo       Deleted old README.md in push repo.
)
if exist "%PUSH_REPO%\readme.md" (
    del /f /q "%PUSH_REPO%\readme.md"
)

:: Copy new public folder
xcopy /e /i /q /y "%MAIN_REPO%\public" "%PUSH_REPO%\public"
echo       Copied new public folder to push repo.

:: Copy README if it exists
if exist "%MAIN_REPO%\README.md" (
    copy /y "%MAIN_REPO%\README.md" "%PUSH_REPO%\README.md" >nul
    echo       Copied README.md to push repo.
)

:: ── 6. Commit and push from push repo ────────────
echo.
echo [6/6] Committing and pushing from push repo...
cd /d "%PUSH_REPO%"
git add .
git commit -m "%COMMIT_MSG%"
git push
echo.
echo       Waiting for push to complete...
timeout /t 20 /nobreak >nul

echo.
echo ================================================
echo  All done. Closing in 3 seconds...
echo ================================================
timeout /t 3 /nobreak >nul
endlocal
