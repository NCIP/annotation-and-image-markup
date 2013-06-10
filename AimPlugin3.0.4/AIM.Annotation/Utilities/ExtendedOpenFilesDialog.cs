#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections.Generic;
using ClearCanvas.Common;
using ClearCanvas.Desktop;

namespace AIM.Annotation.Utilities
{
	[ExtensionPoint]
	public sealed class ExtendedOpenFilesDialog : ExtensionPoint<IExtendedOpenFilesDialogProvider>
	{
		private ExtendedOpenFilesDialog()
		{}

		public static IEnumerable<string> GetFiles(FileDialogCreationArgs args)
		{
			var xp = new ExtendedOpenFilesDialog();
			var provider = xp.CreateExtension() as IExtendedOpenFilesDialogProvider;
			if (provider == null)
				throw new NotSupportedException();
			return provider.GetFiles(args);
		}
	}

	public interface IExtendedOpenFilesDialogProvider
	{
		IEnumerable<string> GetFiles(FileDialogCreationArgs args);
	}
}
