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
using ClearCanvas.Dicom;
using ClearCanvas.Dicom.Iod;

namespace Segmentation.DICOM.Iods
{
	/// <summary>
	/// Convenience extension methods for working with DICOM IODs
	/// </summary>
	public static class IodUtils
	{
		/// <summary>
		/// Retrieves a single value from the specified sequence or null when the value is absent.
		/// </summary>
		/// <typeparam name="T">Type of the module to get the sequence value from</typeparam>
		/// <typeparam name="TVt">Type of the return value</typeparam>
		/// <param name="myModule">The current module to retrieve the value from</param>
		/// <param name="dicomTag">DICOM Tag to get the sequence value from</param>
		/// <returns>Value of the first sequence item or null</returns>
		public static TVt GetSingleValueFromSequence<T, TVt>(this T myModule, uint dicomTag)
			where T : IodBase
			where TVt : SequenceIodBase, new()
		{
			var dicomAttribute = myModule.DicomAttributeProvider[dicomTag];
			if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
			{
				return null;
			}
			return (TVt)Activator.CreateInstance(typeof(TVt), ((DicomSequenceItem[])dicomAttribute.Values)[0]);
		}

		/// <summary>
		/// Sets a single value in the specified sequence.
		/// </summary>
		/// <typeparam name="T">Type of the module to set the sequence value in</typeparam>
		/// <typeparam name="TVt">Type of the sequence value</typeparam>
		/// <param name="myModule">The current module to set the value in</param>
		/// <param name="dicomTag">DICOM Tag to set the sequence value for</param>
		/// <param name="value">The value to be stored in the <paramref name="dicomTag"/> sequence</param>
		public static void SetSingleValueInSequence<T, TVt>(this T myModule, uint dicomTag, TVt value)
			where T : IodBase
			where TVt : SequenceIodBase
		{
			var dicomAttribute = myModule.DicomAttributeProvider[dicomTag];
			if (value == null)
				myModule.DicomAttributeProvider[dicomTag] = null;
			else
				dicomAttribute.Values = new[] { value.DicomSequenceItem };
		}

		/// <summary>
		/// Retrieves specified sequence values from the module
		/// </summary>
		/// <typeparam name="T">Type of the module to get the sequence value from</typeparam>
		/// <typeparam name="TVt">Type of the return values</typeparam>
		/// <param name="myModule">The current module to retrieve the values from</param>
		/// <param name="dicomTag">DICOM Tag to get the sequence values from</param>
		/// <returns>An array of sequence values or null</returns>
		public static TVt[] GetSequenceValues<T, TVt>(this T myModule, uint dicomTag)
			where T : IodBase
			where TVt : SequenceIodBase, new()
		{
			var dicomAttribute = myModule.DicomAttributeProvider[dicomTag];
			if (dicomAttribute.IsNull || dicomAttribute.Count == 0)
			{
				return null;
			}

			var result = new TVt[dicomAttribute.Count];
			var items = (DicomSequenceItem[])dicomAttribute.Values;
			for (int n = 0; n < items.Length; n++)
				result[n] = (TVt)Activator.CreateInstance(typeof(TVt), items[n]);

			return result;
		}

		/// <summary>
		/// Sets given sequence values in the module
		/// </summary>
		/// <typeparam name="T">Type of the module to set the sequence values in</typeparam>
		/// <typeparam name="TVt">Type of the sequence values</typeparam>
		/// <param name="myModule">The current module to set the values in</param>
		/// <param name="dicomTag">DICOM Tag to set the sequence values for</param>
		/// <param name="value">The values to be stored in the <paramref name="dicomTag"/> sequence</param>
		/// <param name="requireValue">If true, sequence is Type 1 and must have at least one value.
		/// If false - empty sequence or null value is acceptable</param>
		public static void SetSequenceValues<T, TVt>(this T myModule, uint dicomTag, TVt[] value, bool requireValue = false)
			where T : IodBase
			where TVt : SequenceIodBase
		{
			if (value == null || value.Length == 0)
			{
				if (requireValue)
					throw new ArgumentNullException("value", typeof (TVt).Name + " is Type 1 Required.");

				myModule.DicomAttributeProvider[dicomTag] = null;
				return;
			}

			var result = new DicomSequenceItem[value.Length];
			for (int n = 0; n < value.Length; n++)
				result[n] = value[n].DicomSequenceItem;

			myModule.DicomAttributeProvider[dicomTag].Values = result;
		}
	}
}
