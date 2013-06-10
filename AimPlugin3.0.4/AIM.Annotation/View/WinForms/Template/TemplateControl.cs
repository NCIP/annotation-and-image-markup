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
using System.Windows.Forms;

using ClearCanvas.Common;
using ClearCanvas.Desktop.View.WinForms;

namespace AIM.Annotation.View.WinForms.Template
{
	public partial class TemplateControl : UserControl
	{
		private readonly AimAnnotationComponent _component;
		private readonly BindingSource _bindingSource;
		private readonly List<Control> _extensionControls = new List<Control>();

		public TemplateControl(AimAnnotationComponent component)
		{
			Platform.CheckForNullReference(component, "component");

			_component = component;
			InitializeComponent();

			_bindingSource = new BindingSource();
			_bindingSource.DataSource = _component;

			_tboxAnnotationName.DataBindings.Add("Enabled", _bindingSource, "AnnotationModuleEnabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_tboxAnnotationName.DataBindings.Add("Text", _bindingSource, "AnnotationName", true, DataSourceUpdateMode.OnPropertyChanged);

			_componentContainerControl.DataBindings.Add("SelectedTemplate", _bindingSource, "SelectedAimTemplate", true, DataSourceUpdateMode.OnPropertyChanged);
			_componentContainerControl.DataBindings.Add("SelectedAnatomicEntities", _bindingSource, "SelectedAnatomicEntities", true, DataSourceUpdateMode.OnPropertyChanged);
			_componentContainerControl.DataBindings.Add("SelectedImagingObservations", _bindingSource, "SelectedImagingObservations", true, DataSourceUpdateMode.OnPropertyChanged);
			_componentContainerControl.DataBindings.Add("SelectedInferences", _bindingSource, "SelectedInferences", true, DataSourceUpdateMode.OnPropertyChanged);
			_componentContainerControl.DataBindings.Add("IsValid", _bindingSource, "IsAimTemplateValid", true, DataSourceUpdateMode.OnPropertyChanged);

			_btnCreateAnnotation.DataBindings.Add("Enabled", _bindingSource, "CreateAnnotationEnabled", true, DataSourceUpdateMode.OnPropertyChanged);
			_btnCreateAnnotation.EnabledChanged += BtnCreateAnnotationEnabledChanged;

			_component.AnnotationCreated += OnAnnotationCreated;

			try
			{
				var xp = new AimAnnotationExtensionPoint();
				var extensions = xp.CreateExtensions();
				if (extensions.Length > 0)
				{
					var extension = (IAimAnnotationExtension)extensions[0];
					extension.Component = _component;
					_btnExtension1.Text = extension.ButtonText;
					_btnExtension1.Click += extension.OnButtonClick;
					_btnExtension1.Enabled = false;
					_extensionControls.Add(_btnExtension1);
				}
			}
			catch (NotSupportedException ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to create AimAnnotationExtension", null);
			}
		}

		void BtnCreateAnnotationEnabledChanged(object sender, EventArgs e)
		{
			foreach (var control in _extensionControls)
			{
				control.Visible = true;
				control.Enabled = _btnCreateAnnotation.Enabled;		
			}
		}

		private void OnAnnotationCreated(object sender, EventArgs e)
		{
			_componentContainerControl.Reset();
		}

		private void _btnCreateAnnotation_Click(object sender, EventArgs e)
		{
			using (new CursorManager(this, Cursors.WaitCursor))
			{
				_component.CreateAnnotation();
			}
		}

		private void _btnUserInfo_Click(object sender, EventArgs e)
		{
			var frmUserInfo = new FormUserInfo(
				_component.UserName,
				_component.LoginName,
				_component.RoleInTrial,
				_component.NumberWithinRoleInTrial);

			if (frmUserInfo.ShowDialog() == DialogResult.OK)
			{
				_component.UserName = frmUserInfo.UserName;
				_component.LoginName = frmUserInfo.LoginName;
				_component.RoleInTrial = frmUserInfo.RoleInTrial;
				_component.NumberWithinRoleInTrial = frmUserInfo.NumberWithinRoleInTrial;
			}
		}
	}
}
