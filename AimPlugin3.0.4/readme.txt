This is release of AIM 3.0.4 source code plugins compatible with ClearCanvas Workstation 2.0 SP1.

All rights reserved. The source code and the workstation are licensed under the terms specified in file license.txt.


Technical Details:

1. Precompiled binaries are located in the "binaries" folder. To test on ClearCanvas Workstation 2.0 SP1, copy the content of the "binaries/release" folder into "plugins" folder of the workstation. The workstation has to be run with Administrative privileges on Windows Vista or above.

2. AIM plugins are 32-bit only.

3. You must have a 32-bit version of workstation to run AIM, even on a 64-bit Windows.

   NOTE: While any managed application can be run in the 32-bit mode on 64-bit machines, native 32-bit components for the workstation cannot be changed. Just in case you need this, below is a command to set workstation into 32-bit mode. The command must be run at the Command Prompt. "CorFlags.exe" is included in the "bin" folder:

   corflag.exe ClearCanvas.Desktop.Executable.exe /32BIT+

4. If you are building workstation plugins yourself (32-bit only), copy the resulting dlls to "plugins" folder of your workstation installation.

5. ClearCanvas SDK 2.0 SP1 source code can be downloaded at http://www.ClearCanvas.ca

6. AIM Toolkit 3.0 source code can be downloaded from the NCI's AIM Tools page at https://cabig.nci.nih.gov/community/tools/AIM

7. Complete AIM Workstation 3.0.4 can be downloaded from the NCI's AIM Tools page at https://cabig.nci.nih.gov/community/tools/AIM

