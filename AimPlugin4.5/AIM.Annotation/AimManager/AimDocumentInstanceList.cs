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

namespace AIM.Annotation.AimManager
{
	/// <summary>
	/// Collection to hold cached <code>IAimDocumentInstance</code> objects in the AIM Cache
	/// </summary>
	public class AimDocumentInstanceList : List<IAimDocumentInstance>
	{
		public AimDocumentInstanceList()
		{
		}

		public AimDocumentInstanceList(IEnumerable<IAimDocumentInstance> aimDocumentInstances)
		{
			AddRange(aimDocumentInstances);
		}

		public new void Add(IAimDocumentInstance aimDocumentInstance)
		{
			if (aimDocumentInstance == null)
				throw new ArgumentNullException("aimDocumentInstance");

			aimDocumentInstance.ParentDocumentInstanceList = this;

			base.Add(aimDocumentInstance);
		}

		public new void AddRange(IEnumerable<IAimDocumentInstance> aimDocumentInstances)
		{
			if (aimDocumentInstances == null)
				throw new ArgumentNullException("aimDocumentInstances");

			var documentInstances = aimDocumentInstances as ICollection<IAimDocumentInstance>;
			if (documentInstances != null)
			{
				foreach (var aimDocumentInstance in documentInstances)
				{
					aimDocumentInstance.ParentDocumentInstanceList = this;
				}
				base.AddRange(documentInstances);
			}
		}

		public new void Insert(int index, IAimDocumentInstance item)
		{
			if (item == null)
				throw new ArgumentNullException("item");

			if ((uint) index >= (uint) Count)
				throw new ArgumentOutOfRangeException("index");

			item.ParentDocumentInstanceList = this;
			base.Insert(index, item);
		}

		public new void InsertRange(int index, IEnumerable<IAimDocumentInstance> collection)
		{
			if (collection == null)
				throw new ArgumentNullException("collection");

			if ((uint) index >= (uint) Count)
				throw new ArgumentOutOfRangeException("index");

			var documentInstances = collection as ICollection<IAimDocumentInstance>;
			if (documentInstances != null)
			{
				foreach (var aimDocumentInstance in documentInstances)
				{
					aimDocumentInstance.ParentDocumentInstanceList = this;
				}
				base.InsertRange(index, documentInstances);
			}
		}

		public new bool Remove(IAimDocumentInstance aimDocumentInstance)
		{
			if (aimDocumentInstance != null)
			{
				aimDocumentInstance.ParentDocumentInstanceList = null;
				return base.Remove(aimDocumentInstance);
			}
			return false;
		}

		public void Remove(IEnumerable<IAimDocumentInstance> items)
		{
			if (items == null)
				return;

			var documentInstances = items as ICollection<IAimDocumentInstance>;
			if (documentInstances != null)
			{
				foreach (var aimDocumentInstance in documentInstances)
					Remove(aimDocumentInstance);
			}
		}

		public new void RemoveAt(int index)
		{
			if ((uint) index >= (uint) Count)
				throw new ArgumentOutOfRangeException("index");

			this[index].ParentDocumentInstanceList = null;
			base.RemoveAt(index);
		}

		public new int RemoveAll(Predicate<IAimDocumentInstance> match)
		{
			throw new NotSupportedException("RemoveAll");
		}

		public new void RemoveRange(int index, int count)
		{
			throw new NotSupportedException("RemoveRange");
		}

		public new void Clear()
		{
			foreach (var aimDocumentInstance in this)
				aimDocumentInstance.ParentDocumentInstanceList = null;

			base.Clear();
		}
	}
}
