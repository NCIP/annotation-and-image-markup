#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;

namespace AIM.Annotation.Utilities
{
	public class ValidationResult
	{
		public bool Validated { get; set; }
		public string ValidatedVersion { get; set; }
		public Exception Exception { get; set; }
	}
}
