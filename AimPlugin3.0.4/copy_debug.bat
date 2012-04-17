@SET BUILD_TARGET=debug

@SET AIM_FLDR=.
@SET AIM_BIN_DEST=.\binaries\%BUILD_TARGET%

@ECHO ================================================
@ECHO Copying files.
@ECHO build_target: %BUILD_TARGET%
@ECHO aim_folder:%AIM_FLDR%
@ECHO destination_folder: %AIM_BIN_DEST%
@ECHO ================================================

@IF NOT EXIST %AIM_BIN_DEST% MKDIR %AIM_BIN_DEST%

@copy /B /Y "%AIM_FLDR%\AIMReferences\%BUILD_TARGET%\AIMLib.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIMReferences\%BUILD_TARGET%\AIMLib.NET.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIMReferences\%BUILD_TARGET%\AIMLibModel.NET.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIMReferences\%BUILD_TARGET%\AimTmplUtil1923.dll" "%AIM_BIN_DEST%\*"
@REM Only one of these two will be found
@copy /B /Y "%AIM_FLDR%\AIMReferences\%BUILD_TARGET%\xerces-c_3_1.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIMReferences\%BUILD_TARGET%\xerces-c_3_1D.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIMReferences\ICSharpCode.SharpZipLib.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIM.Annotation\bin\%BUILD_TARGET%\AIM.Annotation.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIM.Annotation\bin\%BUILD_TARGET%\AIM.Annotation.dll.config" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIM.Annotation\View\WinForms\bin\%BUILD_TARGET%\AIM.Annotation.View.WinForms.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIMTCGAService\bin\%BUILD_TARGET%\AIMTCGAService.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIMTCGAService\bin\%BUILD_TARGET%\AIMTCGAService.dll.config" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\AIMTCGAService\View\WinForms\bin\%BUILD_TARGET%\AIMTCGAService.View.WinForms.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\DataServiceUtil\bin\%BUILD_TARGET%\DataServiceUtil.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\GeneralUtilities\bin\%BUILD_TARGET%\GeneralUtilities.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\NBIAService\bin\%BUILD_TARGET%\NBIAService.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\NBIAService\bin\%BUILD_TARGET%\NBIAService.dll.config" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\SearchComponent\bin\%BUILD_TARGET%\SearchComponent.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\SearchComponent\bin\%BUILD_TARGET%\SearchComponent.dll.config" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\SearchComponent\View\WinForms\bin\%BUILD_TARGET%\SearchComponent.View.WinForms.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\TCGA\bin\%BUILD_TARGET%\TCGA.dll" "%AIM_BIN_DEST%\*"
@copy /B /Y "%AIM_FLDR%\TCGA\View\WinForms\bin\%BUILD_TARGET%\TCGA.View.WinForms.dll" "%AIM_BIN_DEST%\*"


@ECHO Done.
@pause

