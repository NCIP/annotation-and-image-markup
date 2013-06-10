#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using ClearCanvas.Common;

namespace AIM.Annotation
{
	[ExtensionPoint]
	public sealed class AimAnnotationExtensionPoint : ExtensionPoint<IAimAnnotationExtension>
	{
	}

	public interface IAimAnnotationExtension
	{
		AimAnnotationComponent Component { set; }
		string ButtonText { get; }
		void OnButtonClick(object sender, EventArgs e);
	}
}
