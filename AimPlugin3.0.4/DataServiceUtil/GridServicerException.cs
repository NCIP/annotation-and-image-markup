//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;

namespace DataServiceUtil
{
	[Serializable]
	public class GridServicerException : Exception
	{
		public GridServicerException(string errorMessage) : base(errorMessage) { }

		public GridServicerException(string errorMessage, Exception innerEx) : base(errorMessage, innerEx) { }

		public override string Message
		{
			get { return string.Format("caGrid error message: {0}", base.Message); }
		}
	}
}
