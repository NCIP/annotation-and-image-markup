#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

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
