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
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows.Forms;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.View.WinForms
{
	/// <summary>
	/// Generic control to display a list of TemplateTree.StandardValidTerm items
	/// </summary>
	public partial class AimCodeSequenceDetailsControl : UserControl, INotifyPropertyChanged
	{
		private readonly AimAnnotationDetailsComponent _component;

		//private IList<TemplateTree.StandardValidTerm> _codeSequenceList;
		private IList<CodeBindingItem> _codeSequenceList;
		private readonly string _bindingCollectionName;

		public class CodeBindingItem
		{
			public string CodeValue { get; set; }
			public string CodeMeaning { get; set; }
			public string CodingSchemeDesignator { get; set; }
		}

		public AimCodeSequenceDetailsControl(AimAnnotationDetailsComponent component, string bindingCollectionName)
		{
			Platform.CheckForNullReference(bindingCollectionName, "bindingCollectionName");

			InitializeComponent();

			_component = component;
			_bindingCollectionName = bindingCollectionName;

			BindingSource bindingSource = new BindingSource();
			bindingSource.DataSource = _component;

			this.DataBindings.Add("SetupCodeSequenceList", bindingSource, _bindingCollectionName, true, DataSourceUpdateMode.OnPropertyChanged);

			_dgvCodeSequenceDetails.AutoGenerateColumns = false;
			_dgvCodeSequenceDetails.DataBindings.Add("DataSource", this, "CodeSequenceList", true, DataSourceUpdateMode.OnPropertyChanged);
			_codeValue.DataPropertyName = "CodeValue";
			_codeMeaning.DataPropertyName = "CodeMeaning";
			_codingSchemeDesignator.DataPropertyName = "CodingSchemeDesignator";
		}

		// This method sets internal collection of binding items via reflection
		public IEnumerable SetupCodeSequenceList
		{
			get { return null; }
			set
			{
				System.Reflection.PropertyInfo propInfo = _component.GetType().GetProperty(_bindingCollectionName);
				if (propInfo != null)
				{
					try
					{
						//this.CodeSequenceList = propInfo.GetValue(_component, null) as IList<TemplateTree.StandardValidTerm>;
						var codeList = propInfo.GetValue(_component, null) as IList<TemplateTree.StandardValidTerm>;
						this.CodeSequenceList = codeList == null
													? null
													: codeList.ToList().ConvertAll(svt =>
																				   new CodeBindingItem
																					   {
																						   CodeMeaning = svt.StandardCodeSequence.CodeMeaning,
																						   CodeValue = svt.StandardCodeSequence.CodeValue,
																						   CodingSchemeDesignator = svt.StandardCodeSequence.CodingSchemeDesignator
																					   });
					}
					catch (Exception)
					{
						this.CodeSequenceList = null;
					}
				}
			}
		}

		//public IList<TemplateTree.StandardValidTerm> CodeSequenceList
		public IList<CodeBindingItem> CodeSequenceList
		{
			get
			{
				return _codeSequenceList;
			}
			set
			{
				if (_codeSequenceList == value)
					return;

				_codeSequenceList = value;
				EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs("CodeSequenceList"));
			}
		}

		#region INotifyPropertyChanged Members

		public event PropertyChangedEventHandler PropertyChanged;

		#endregion
	}
}
