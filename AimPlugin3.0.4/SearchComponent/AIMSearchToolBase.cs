//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;

namespace SearchComponent
{
	public class AIMSearchToolBase : SearchBaseTool
	{
		public AIMSearchToolBase()
		{
		}

		protected void RetrieveAnnotationsFromAimService(object[] searchResults)
		{
			string errorMsg = null;
			BackgroundTask task = new BackgroundTask(
				delegate(IBackgroundTaskContext context)
				{
					try
					{
						int cnt = 0;
						BackgroundTaskProgress progress;
						List<string> tmpAnnotations = new List<string>();
						aim_dotnet.DcmModel dcmModel = new aim_dotnet.DcmModel();
						foreach (AIMSearchResult result in searchResults)
						{
							cnt++;

							if (result.RetrievedAnnotation == null)
								continue;

							progress = new BackgroundTaskProgress(cnt, searchResults.Length + 1, "Saving Annotation " + cnt);
							context.ReportProgress(progress);

							string tmpFileName = System.IO.Path.GetTempFileName();
							dcmModel.WriteAnnotationToFile(result.RetrievedAnnotation, tmpFileName);
							tmpAnnotations.Add(tmpFileName);
						}
						dcmModel = null;

						if (tmpAnnotations.Count > 0)
						{
							progress = new BackgroundTaskProgress(searchResults.Length, searchResults.Length + 1, "Importing Annotations");
							context.ReportProgress(progress);

							this.ImportDicomFiles(tmpAnnotations);
						}
					}
					catch (Exception ex)
					{
						errorMsg = ex.Message;
						Platform.Log(LogLevel.Error, ex, "Failed to import annotation(s)");
					}

					context.Complete(null);

				}, true);

			ProgressDialog.Show(task, this.Context.DesktopWindow, true, ProgressBarStyle.Blocks);

			if (!string.IsNullOrEmpty(errorMsg))
				this.Context.DesktopWindow.ShowMessageBox(errorMsg, MessageBoxActions.Ok);
		}
	}
}
