//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

using ClearCanvas.Common;
using ClearCanvas.Desktop.View.WinForms;

namespace AIM.Annotation.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms user-interface for <see cref="AimAnnotationComponent"/>.
    /// </summary>
    public partial class AimAnnotationComponentControl : ApplicationComponentUserControl
    {
        private readonly AimAnnotationComponent _component;
        private readonly BindingSource _bindingSource;
    	private readonly Template.TemplateControl _templateCtrlAimTemplate;

        public AimAnnotationComponentControl(AimAnnotationComponent component)
            :base(component)
        {
        	_component = component;
        	InitializeComponent();

            _bindingSource = new BindingSource();
			_bindingSource.DataSource = _component;

            SuspendLayout();

        	var yOffset = 0;
			foreach(Control ctrl in Controls)
				yOffset = Math.Max(yOffset, ctrl.Bottom);
        	yOffset = Math.Max(5, yOffset);
            var szTemplate = Size - new Size(Margin.Horizontal, Margin.Vertical + yOffset);
        	_templateCtrlAimTemplate = new Template.TemplateControl(_component);
			_templateCtrlAimTemplate.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			_templateCtrlAimTemplate.Location = new Point(3, yOffset);
			_templateCtrlAimTemplate.Name = "_templateCtrlAimTemplate";
			_templateCtrlAimTemplate.Size = szTemplate;
			_templateCtrlAimTemplate.TabIndex = 2;

        	Controls.Add(_templateCtrlAimTemplate);
            ResumeLayout(false);
            PerformLayout();
        	InitializeAnnotationTypeCombo();

			_templateCtrlAimTemplate.DataBindings.Add("Visible", _bindingSource, "AimTemplateVisible", true, DataSourceUpdateMode.OnPropertyChanged);
            DataBindings.Add("Enabled", _bindingSource, "AnnotationModuleEnabled", true, DataSourceUpdateMode.OnPropertyChanged);
        }

		private void InitializeAnnotationTypeCombo()
		{
			_cmbAnnotationType.SelectedValueChanged -= OnAnnotationTypeSelectedValueChanged;
			_cmbAnnotationType.DataSource = _component.AvailableAnnotationTypes;
			_cmbAnnotationType.SelectedItem = _component.AnnotationTypeCode;
			_cmbAnnotationType.SelectedValueChanged += OnAnnotationTypeSelectedValueChanged;
		}

		private void OnAnnotationTypeSelectedValueChanged(object sender, EventArgs e)
		{
			_component.AnnotationTypeCode = _cmbAnnotationType.SelectedItem as StandardCodeSequence;
		}

    	private void _cmbAnnotationType_DropDown(object sender, EventArgs e)
		{
			var cmbBox = sender as ComboBox;
			if (cmbBox != null)
				cmbBox.DropDownWidth = AimWinFormsUtil.CalculateComboBoxDropdownWidth(cmbBox);
		}

		private void btnSelectTemplateDoc_Click(object sender, EventArgs e)
		{
			if (ModifierKeys == Keys.Shift)
			{
				var msgBox = new ClearCanvas.Desktop.View.WinForms.MessageBox();
				if (msgBox.Show(@"Do you want to select default template?", MessageBoxActions.YesNo) == DialogBoxAction.Yes)
				{
					SetNewTemplateDocument(null);
					return;
				}
			}
			var openFileDialog = new OpenFileDialog();
			openFileDialog.DefaultExt = "xml";
			openFileDialog.Filter = @"XML Files (*.xml)|*.xml|All Files|*.*";
			openFileDialog.Title = @"Open AIM Template File";
			openFileDialog.Multiselect = false;
			openFileDialog.RestoreDirectory = true;
			openFileDialog.InitialDirectory = _component.SelectedAimTemplateLocalFolder;
			if (openFileDialog.ShowDialog(this) == DialogResult.OK)
			{
				SetNewTemplateDocument(openFileDialog.FileName);
			}
		}

		private void SetNewTemplateDocument(string templateDocumentFileName)
		{
			_component.SelectedAimTemplateDocument = templateDocumentFileName;
			SynchronizationContext.Current.Post(
				delegate
				{ InitializeAnnotationTypeCombo(); }
				, null);
		}
    }
}
