@echo off
setlocal

cd /d "%~dp0"

echo ================================================
echo  FAB ACADEMY - AUTO PUSH
echo ================================================

:: ── 1. Build site ───────────────────────────────
echo.
echo [1/6] Building Hugo site...
hugo --minify
if errorlevel 1 (
    echo ERROR: Hugo build failed. Aborting.
    exit /b 1
)
echo       Build complete.

:: ── 2. Backup original .gitignore ───────────────
echo.
echo [2/6] Backing up .gitignore...
copy /y ".gitignore" ".gitignore.bak" >nul
echo       Backed up to .gitignore.bak

:: ── 3. Write GitHub .gitignore ──────────────────
echo.
echo [3/6] Switching to GitHub .gitignore...
(
    echo node_modules/
    echo resources/
    echo .hugo_build.lock
    echo error_log*.txt
    echo tmp_local*.html
) > .gitignore
echo       GitHub .gitignore written.

:: ── 4. Push to GitHub ───────────────────────────
echo.
echo [4/6] Pushing to GitHub...
git add .
git commit -m "auto backup github - %date% %time%"
git push github main
if errorlevel 1 (
    echo WARNING: GitHub push failed. Continuing...
)
echo       GitHub push done.

:: ── 5. Write GitLab .gitignore ──────────────────
echo.
echo [5/6] Switching to GitLab .gitignore...
(
    echo # Ignore everything
    echo *
    echo.
    echo # Allow public folder
    echo !public/
    echo !public/**
    echo.
    echo # Allow themes
    echo !themes/
    echo !themes/**
    echo.
    echo # Allow CI and README
    echo !.gitlab-ci.yml
    echo !README.md
    echo.
    echo # Allow directories to be traversed
    echo !*/
) > .gitignore
echo       GitLab .gitignore written.

:: ── 6. Push to GitLab ───────────────────────────
echo.
echo [6/6] Pushing to GitLab (origin)...
git add .
git commit -m "auto push gitlab - %date% %time%"
git push origin main
if errorlevel 1 (
    echo WARNING: GitLab push failed. Continuing...
)
echo       GitLab push done.

:: ── 7. Restore original .gitignore ──────────────
echo.
echo Restoring original .gitignore...
copy /y ".gitignore.bak" ".gitignore" >nul
del ".gitignore.bak" >nul
echo       .gitignore restored.

echo.
echo ================================================
echo  All done.
echo ================================================
endlocal
