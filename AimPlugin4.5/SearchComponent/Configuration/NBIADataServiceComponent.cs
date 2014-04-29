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

using System.Collections.Specialized;
using ClearCanvas.Common;
using ClearCanvas.Desktop.Configuration;
using ClearCanvas.Desktop;

namespace SearchComponent.Configuration
{
	/// <summary>
	/// Extension point for views onto <see cref="NBIADataServiceComponent"/>.
	/// </summary>
	[ExtensionPoint]
	public sealed class NBIADataServiceComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
	{
	}

	/// <summary>
	/// NBIADataServiceComponent class.
	/// </summary>
	[AssociateView(typeof(NBIADataServiceComponentViewExtensionPoint))]
	public class NBIADataServiceComponent : ConfigurationApplicationComponent
	{
		public static readonly string Path = "NBIA";

		private string _nbiaDataServiceUrl;
		private StringCollection _nbiaDataServiceUrlList;
		private string _nbiaDataServiceTransferUrl;
		private StringCollection _nbiaDataServiceTransferUrlList;

		private bool _saveRequested;

		public string NbiaDataServiceUrl
		{
			get { return _nbiaDataServiceUrl; }
			set
			{
				if (_nbiaDataServiceUrl == value)
					return;

				_nbiaDataServiceUrl = value;
				Modified = true;
				NotifyPropertyChanged("NbiaDataServiceUrl");
			}
		}

		public StringCollection NbiaDataServiceUrlList
		{
			get
			{
				if (_nbiaDataServiceTransferUrlList == null)
					return new StringCollection();
				return _nbiaDataServiceUrlList;
			}
			set
			{
				if (IsEqual(_nbiaDataServiceUrlList, value))
					return;

				_nbiaDataServiceUrlList = value;
				//Modified = true;
				NotifyPropertyChanged("NbiaDataServiceUrlList");
			}
		}

		public string NbiaDataServiceTransferUrl
		{
			get { return _nbiaDataServiceTransferUrl; }
			set
			{
				if (_nbiaDataServiceTransferUrl == value)
					return;

				_nbiaDataServiceTransferUrl = value;
				Modified = true;
				NotifyPropertyChanged("NbiaDataServiceTransferUrl");
			}
		}

		public StringCollection NbiaDataServiceTransferUrlList
		{
			get { return _nbiaDataServiceTransferUrlList; }
			set
			{
				if (IsEqual(_nbiaDataServiceTransferUrlList, value))
					return;

				_nbiaDataServiceTransferUrlList = value;
				//Modified = true;
				NotifyPropertyChanged("NbiaDataServiceTransferUrlList");
			}
		}

		public bool SaveRequested
		{
			get { return _saveRequested; }
			set
			{
				if (_saveRequested == value)
					return;

				_saveRequested = value;
			}
		}

		/// <summary>
		/// Called by the host to initialize the application component.
		/// </summary>
		public override void Start()
		{
			base.Start();

			_nbiaDataServiceUrl = SearchSettings.Default.NBIADataServiceUrl;
			_nbiaDataServiceTransferUrl = SearchSettings.Default.NBIADataServiceTransferUrl;
		}

		public override void Save()
		{
			SearchSettings.Default.NBIADataServiceUrl = _nbiaDataServiceUrl;
			SearchSettings.Default.NBIADataServiceTransferUrl = _nbiaDataServiceTransferUrl;
			SearchSettings.Default.Save();
		}

		private static bool IsEqual(StringCollection collOne, StringCollection collTwo)
		{
			if (collOne != collTwo)
			{
				if (collOne == null || collTwo == null || collOne.Count != collTwo.Count)
					return false;

				for (int i = 0; i < collOne.Count; i++)
				{
					if (collOne[i] != collTwo[i])
						return false;
				}
			}

			return true;
		}
	}
}
