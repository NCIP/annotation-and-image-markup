//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
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
