//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Collections.Generic;
using System.Windows.Forms;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using AIM.Annotation.Utilities;

namespace AIM.Annotation.View.WinForms
{
	[ExtensionOf(typeof(ExtendedOpenFilesDialog))]
	public class ExtendedOpenFilesDialogProvider : IExtendedOpenFilesDialogProvider
	{
		public IEnumerable<string> GetFiles(FileDialogCreationArgs args)
		{
			var dialog = new OpenFileDialog();
			PrepareFileDialog(dialog, args);
			dialog.CheckFileExists = true;
			dialog.ShowReadOnly = true;
			dialog.Multiselect = true;

			var dr = dialog.ShowDialog();
			return dr == DialogResult.OK ? dialog.FileNames : null;
		}

		private static void PrepareFileDialog(FileDialog dialog, FileDialogCreationArgs args)
		{
			dialog.AddExtension = !string.IsNullOrEmpty(args.FileExtension);
			dialog.DefaultExt = args.FileExtension;
			dialog.FileName = args.FileName;
			dialog.InitialDirectory = args.Directory;
			dialog.RestoreDirectory = true;
			dialog.Title = args.Title;

			dialog.Filter = StringUtilities.Combine(args.Filters, "|",
													delegate(FileExtensionFilter f) { return f.Description + "|" + f.Filter; });
		}
	}
}
