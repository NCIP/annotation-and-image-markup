//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;

namespace TCGA
{
	public interface ITcgaLoginDialog : IDisposable
	{
		bool Show();

		string UserName { get; set; }
		string LoginName { get; set; }
		string RoleInTrial { get; set; }
		int NumberWithinRoleOfClinicalTrial { get; set; }
	}
}
