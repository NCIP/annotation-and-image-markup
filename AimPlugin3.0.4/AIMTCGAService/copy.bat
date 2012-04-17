@SET BUILD_TARGET=debug
copy 
@SET AIM_BIN_DEST=..\..\source_cc\Desktop\Executable\bin\%1\plugins

@ECHO ================================================
@ECHO Copying files.
@ECHO NUWeb Browser
@ECHO destination_folder: %AIM_BIN_DEST%
@ECHO ================================================

@copy /B /Y .\View\WinForms\bin\%1\AIMTCGAService.dll "%AIM_BIN_DEST%\*"
@copy /B /Y .\View\WinForms\bin\%1\DataServiceUtil.dll "%AIM_BIN_DEST%\*"
@copy /B /Y .\View\WinForms\bin\%1\AIMTCGAService.View.WinForms.dll "%AIM_BIN_DEST%\*"

@ECHO Done.
@pause


