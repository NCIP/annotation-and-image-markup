//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.View.WinForms
{
	/// <summary>
	/// Generic control to display a list of aim_dotnet.ICodeSequence items
	/// </summary>
	public partial class AimCodeSequenceDetailsControl : UserControl, INotifyPropertyChanged
	{
		private readonly AimAnnotationDetailsComponent _component;

		private IList<aim_dotnet.ICodeSequence> _codeSequenceList;
		private readonly string _bindingCollectionName;

		public AimCodeSequenceDetailsControl(AimAnnotationDetailsComponent component, string bindingCollectionName)
		{
			Platform.CheckForNullReference(bindingCollectionName, "bindingCollectionName");

			InitializeComponent();

			_component = component;
			_bindingCollectionName = bindingCollectionName;

			var bindingSource = new BindingSource();
			bindingSource.DataSource = _component;

			DataBindings.Add("SetupCodeSequenceList", bindingSource, _bindingCollectionName, true, DataSourceUpdateMode.OnPropertyChanged);

			_dgvCodeSequenceDetails.AutoGenerateColumns = false;
			_dgvCodeSequenceDetails.DataBindings.Add("DataSource", this, "CodeSequenceList", true, DataSourceUpdateMode.OnPropertyChanged);
			_codeValue.DataPropertyName = "CodeValue";
			_codeMeaning.DataPropertyName = "CodeMeaning";
			_codingSchemeDesignator.DataPropertyName = "CodingSchemeDesignator";
		}

		public IEnumerable SetupCodeSequenceList
		{
			get { return null; }
			set
			{
				var propInfo = _component.GetType().GetProperty(_bindingCollectionName);
				if (propInfo != null)
				{
					try
					{
						CodeSequenceList = propInfo.GetValue(_component, null) as IList<aim_dotnet.ICodeSequence>;
					}
					catch (Exception)
					{
						CodeSequenceList = null;
					}
				}
			}
		}

		public IList<aim_dotnet.ICodeSequence> CodeSequenceList
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
