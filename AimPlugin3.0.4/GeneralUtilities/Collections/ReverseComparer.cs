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
