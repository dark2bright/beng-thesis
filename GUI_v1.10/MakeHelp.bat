@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by THESIS.HPJ. >"hlp\Thesis.hm"
echo. >>"hlp\Thesis.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Thesis.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Thesis.hm"
echo. >>"hlp\Thesis.hm"
echo // Prompts (IDP_*) >>"hlp\Thesis.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Thesis.hm"
echo. >>"hlp\Thesis.hm"
echo // Resources (IDR_*) >>"hlp\Thesis.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Thesis.hm"
echo. >>"hlp\Thesis.hm"
echo // Dialogs (IDD_*) >>"hlp\Thesis.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Thesis.hm"
echo. >>"hlp\Thesis.hm"
echo // Frame Controls (IDW_*) >>"hlp\Thesis.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Thesis.hm"
REM -- Make help for Project THESIS


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Thesis.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Thesis.hlp" goto :Error
if not exist "hlp\Thesis.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Thesis.hlp" Debug
if exist Debug\nul copy "hlp\Thesis.cnt" Debug
if exist Release\nul copy "hlp\Thesis.hlp" Release
if exist Release\nul copy "hlp\Thesis.cnt" Release
echo.
goto :done

:Error
echo hlp\Thesis.hpj(1) : error: Problem encountered creating help file

:done
echo.
