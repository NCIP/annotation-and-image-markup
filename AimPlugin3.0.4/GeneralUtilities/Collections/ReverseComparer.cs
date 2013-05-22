//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;

namespace GeneralUtilities.Collections
{
	public class ReverseComparer<T> : IComparer<T> where T : IComparable
	{
		public int Compare(T x, T y)
		{
			return -1*Comparer<T>.Default.Compare(x, y);
		}
	}
}
