#region License

// Copyright (c) 2007 - 2014, Northwestern University, Vladimir Kleper, Skip Talbot
// and Pattanasak Mongkolwat.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
//   Neither the name of the National Cancer Institute nor Northwestern University
//   nor the names of its contributors may be used to endorse or promote products
//   derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

using System;
using System.Collections.Generic;
using System.Text;

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Dicom;
using ClearCanvas.ImageViewer.Common.StudyManagement;
using ClearCanvas.ImageViewer.Common.WorkItem;
using ClearCanvas.ImageViewer.Explorer.Dicom;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.Tools
{

	[MenuAction("importAimXml", "global-menus/MenuAnnotation/AimXmlImportMenu", "ImportAimXml")]
	[ButtonAction("importAimXml", "dicomstudybrowser-toolbar/AimXmlImportButton", "ImportAimXml")]
	[Tooltip("importAimXml", "TooltipImportAimXml")]
	[IconSet("importAimXml", "Icons.AimXmlImportToolSmall.png", "Icons.AimXmlImportToolMedium.png", "Icons.AimXmlImportToolLarge.png")]
	[EnabledStateObserver("importAimXml", "Enabled", "EnabledChanged")]

	[ExtensionOf(typeof(StudyBrowserToolExtensionPoint))]
	public class AimXmlImportTool : StudyBrowserTool
	{
		private IWorkItemActivityMonitor _workItemActivityMonitor;
		private string _lastFolder = string.Empty;

		public AimXmlImportTool()
		{
		}

		public override void Initialize()
		{
			base.Initialize();

			_workItemActivityMonitor = WorkItemActivityMonitor.Create();
			_workItemActivityMonitor.IsConnectedChanged += OnConnectionChanged;

			this.Enabled = _workItemActivityMonitor.IsConnected;
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				_workItemActivityMonitor.IsConnectedChanged -= OnConnectionChanged;
				_workItemActivityMonitor.Dispose();
				_workItemActivityMonitor = null;
			}

			base.Dispose(disposing);
		}

		private void OnConnectionChanged(object sender, EventArgs e)
		{
			this.Enabled = _workItemActivityMonitor.IsConnected;
		}

		protected override void OnSelectedServerChanged(object sender, EventArgs e)
		{
			// NOOP
		}

		protected override void OnSelectedStudyChanged(object sender, EventArgs e)
		{
			// NOOP
		}

		public void ImportAimXml()
		{
			// 1. Pick AIM XML documents to import
			FileDialogCreationArgs fileDialogCreationArgs =
				new FileDialogCreationArgs(string.Empty, _lastFolder, null, new List<FileExtensionFilter>
				                                                            	{
				                                                            		new FileExtensionFilter("*.xml", "XML Files (*.xml)"),
				                                                            		new FileExtensionFilter("*.*", "All Files (*.*)")
				                                                            	});
			fileDialogCreationArgs.Title = "Select AIM XML documents";

			IEnumerable<string> aimFiles = Utilities.ExtendedOpenFilesDialog.GetFiles(fileDialogCreationArgs);

			// 2. Import selection
			if (aimFiles != null)
				DoImportAimXml(new List<string>(aimFiles));
		}

		private void DoImportAimXml(List<string> aimFiles)
		{
			string errorMsg = null;
			List<string> invalidFiles = new List<string>();
			bool isCanceled = false;
			BackgroundTask task = new BackgroundTask(
				delegate(IBackgroundTaskContext context)
					{
						// TODO VK: add try catch to conversion and try to store individual converted files later
						List<string> tempDcmFiles = AimManager.AimManager.ConvertAnnotationsFromXmlToDicomFiles(AimManager.AimManager.DefaultAimVersion, aimFiles, context, out invalidFiles);

						if (context.CancelRequested)
						{
							foreach (var file in tempDcmFiles)
							{
								try
								{
									System.IO.File.Delete(file);
								}
								catch
								{
								}
							}
							context.Cancel();
							isCanceled = true;
							return;
						}

						context.ReportProgress(new BackgroundTaskProgress(80, "Storing local annotations"));

						try
						{
							var cnt = 0;
							foreach (var tempDcmFile in tempDcmFiles)
							{
								var dicomFile = new DicomFile(tempDcmFile);
								dicomFile.Load();

								Platform.GetService((IPublishFiles w) => w.PublishLocal(new List<DicomFile> {dicomFile}));

								var progressPercent = (int)Math.Floor((cnt++) / (float)tempDcmFiles.Count * 100) / 5; // this is our last 20% 
								var progressMessage = String.Format("Storing file {0} of {1}", cnt, tempDcmFiles.Count);
								context.ReportProgress(new BackgroundTaskProgress(80 + progressPercent, progressMessage));

							}
						}
						catch (Exception ex)
						{
							Platform.Log(LogLevel.Error, ex);
							errorMsg = "Failed to import your annotation(s)";
						}
						finally
						{
							// Delete temp files
							foreach (var tempDcmFile in tempDcmFiles)
							{
								try
								{
									System.IO.File.Delete(tempDcmFile);
								}
								catch (Exception)
								{
								}
							}
							tempDcmFiles.Clear();
						}

						context.Complete();
					}, true);

			ProgressDialog.Show(task, this.Context.DesktopWindow, true, ProgressBarStyle.Continuous);

			if (isCanceled)
				return;

			// Report errors
			var sb = new StringBuilder();
			if (!string.IsNullOrEmpty(errorMsg))
				sb.AppendLine(errorMsg);
			if (invalidFiles.Count > 0)
				sb.AppendFormat("The following files had issues while being imported:{0}{1}", Environment.NewLine, StringUtilities.Combine(invalidFiles, ", "));
			if (sb.Length > 0)
				this.Context.DesktopWindow.ShowMessageBox(sb.ToString(), MessageBoxActions.Ok);
		}
	}
}
