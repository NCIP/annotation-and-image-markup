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

using System.Text;

namespace AIM.Annotation.TemplateTree
{
	public static class AimTemplateTreeUtilities
	{
		public static bool IsNullCodeSequence(StandardCodeSequence codeSequence)
		{
			if (codeSequence == null)
				return true;
			if (codeSequence.CodeMeaning == AimAnnotationComponent.NullCodeValue.CodeMeaning &&
				codeSequence.CodeValue == AimAnnotationComponent.NullCodeValue.CodeValue)
				return true;

			return false;
		}

		public static bool IsNullStandardTerm(StandardValidTerm validTerm)
		{
			return validTerm == null || IsNullCodeSequence(validTerm.StandardCodeSequence);
		}

		/// <summary>
		/// Recursively traverses given <paramref name="validTerm"/> and appends Code Meanings to the given <paramref name="sb"/>.
		/// This effectively flattens <paramref name="validTerm"/> to a string.
		/// </summary>
		/// <param name="validTerm">Standard Valid Term to traverse</param>
		/// <param name="sb">String Builder that receives the values</param>
		public static StringBuilder ToStringBuilder(StandardValidTerm validTerm, StringBuilder sb)
		{
			if (validTerm == null || sb == null)
				return sb;

			if (sb.Length > 0)
				sb.Append(" ");
			sb.Append(validTerm.StandardCodeSequence.CodeMeaning);
			// Traverse the tree in-order
			foreach (StandardValidTerm standardValidTerm in validTerm.StandardValidTerms)
				ToStringBuilder(standardValidTerm, sb);

			return sb;
		}
	}
}
