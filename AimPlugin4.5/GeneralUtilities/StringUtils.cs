#region License

// Copyright (c) 2007 - 2014, Northwestern University, Vladimir Kleper, Skip Talbot
// and Pattanasak Mongkolwat.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
//   Neither the name of the National Cancer Institute nor Northwestern University
//   nor the names of its contributors may be used to endorse or promote products
//   derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

using System;
using System.Globalization;

namespace GeneralUtilities
{
	public static class StringUtils
	{
		public static string TrimStringStartOrSelf(string str, string stringToTrim)
		{
			return TrimStringStartOrSelf(str, stringToTrim, false, null);
		}

		public static string TrimStringStartOrSelf(string str, string stringToTrim, bool ignoreCase, CultureInfo culture)
		{
			if (stringToTrim == null || str == null)
				return str;

			return str.StartsWith(stringToTrim, ignoreCase, culture) ? str.Substring(stringToTrim.Length) : str;
		}

		public static string TrimStringStartOrSelf(string str, string stringToTrim, StringComparison comparison)
		{
			if (stringToTrim == null || str == null)
				return str;

			return str.StartsWith(stringToTrim, comparison) ? str.Substring(stringToTrim.Length) : str;
		}

		public static string NullIfTrimed(string str)
		{
			var s = str == null ? null : str.Trim();
			return string.IsNullOrEmpty(s) ? null : s;
		}
	}
}
