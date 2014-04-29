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
using System.Collections.Generic;
using System.Linq;

namespace GeneralUtilities.Collections
{
	public static class GeneralCollectionUtils
	{
		public static IList<T> DeepCopy<T>(IList<T> orignalCollection) //where T : class, new()
		{
			if (orignalCollection == null)
				return null;

			Type genType = typeof (T);
			var isValueType = genType.IsValueType;

			// NOTE: use copy constructor directly because some lists (ReadOnlyCollection<T>) may not have a default constructor

			if (isValueType)
				return (IList<T>) Activator.CreateInstance(orignalCollection.GetType(), orignalCollection);

			// It's assumed that the type has a copy constructor
			var tempList = orignalCollection.Select(elem => (T) Activator.CreateInstance(genType, elem)).ToList();

			return (IList<T>)Activator.CreateInstance(orignalCollection.GetType(), tempList);
		}

		public static bool DeepEqual<T>(IEnumerable<T> source, IEnumerable<T> destination)
		{
			if (source == null)
				return destination == null;

			if (ReferenceEquals(source, destination))
				return true;

			// Should we care about this? Data Contracts can give us default types after deserialization
			//if (source.GetType() != destination.GetType())
			//    return false;

			return source.SequenceEqual(destination);
		}

		public static bool IsNullOrEmpty<T>(this IEnumerable<T> enumerable)
		{
			return enumerable == null || !enumerable.Any();
		}
	}
}
