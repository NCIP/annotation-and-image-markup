How to Build AIM Plugins:

1. Add AIM plugins and their WinForms projects to your ImageViewer solution file.
2. Make Desktop.Executable project dependent on the newly added plugins.
3. Either change post-build routines to copy new plugin executables to the "plugins" folder or copy the plugin executables there manually when the build completes.
3. Build Desktop.Executable. During an initial build, there may be errors related to visibility of some of the ClearCanvas classes. Make the classes in question public and build again.
