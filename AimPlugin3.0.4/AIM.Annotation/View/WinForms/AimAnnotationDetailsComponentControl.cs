#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

using ClearCanvas.Common;
using ClearCanvas.Desktop.View.WinForms;

using mshtml;

namespace AIM.Annotation.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms user-interface for <see cref="AimAnnotationDetailsComponent"/>.
    /// </summary>
    public partial class AimAnnotationDetailsComponentControl : ApplicationComponentUserControl
    {
		const int FEATURE_DISABLE_NAVIGATION_SOUNDS = 21;
		const int SET_FEATURE_ON_PROCESS = 0x00000002;

		[DllImport("urlmon.dll")]
		[PreserveSig]
		[return: MarshalAs(UnmanagedType.Error)]
		static extern int CoInternetSetFeatureEnabled(int featureEntry, [MarshalAs(UnmanagedType.U4)] int dwFlags, bool fEnable);

    	private readonly AimCodeSequenceDetailsControl _imagingObsDetailsControl;
    	private readonly AimCodeSequenceDetailsControl _anatomicEntitiesDetailsControl;

        private readonly AimAnnotationDetailsComponent _component;

        public AimAnnotationDetailsComponentControl(AimAnnotationDetailsComponent component)
            :base(component)
        {
			_component = component;
            InitializeComponent();

            var bindingSource = new BindingSource();
			bindingSource.DataSource = _component;

			_tboxCalculations.DataBindings.Add("Lines", bindingSource, "CalculationDescriptions", true, DataSourceUpdateMode.OnPropertyChanged);
        	_infoTabs.DataBindings.Add("Visible", bindingSource, "IsImageViewerActive", true, DataSourceUpdateMode.OnPropertyChanged);

        	_tabAnatomicEnities.SuspendLayout();
        	_tabImagingObservations.SuspendLayout();
        	_infoTabs.SuspendLayout();
        	SuspendLayout();

			_anatomicEntitiesDetailsControl = new AimCodeSequenceDetailsControl(component, "AnatomicEntities");
			_anatomicEntitiesDetailsControl.Dock = DockStyle.Fill;
			_anatomicEntitiesDetailsControl.Location = new Point(3, 3);
			_anatomicEntitiesDetailsControl.Name = "_anatomicEntitiesDetailsControl";
			_anatomicEntitiesDetailsControl.Size = new Size(543, 458);
			_anatomicEntitiesDetailsControl.TabIndex = 0;
			_tabAnatomicEnities.Controls.Add(_anatomicEntitiesDetailsControl);

        	_imagingObsDetailsControl = new AimCodeSequenceDetailsControl(component, "ImagingObservations");
			_imagingObsDetailsControl.Dock = DockStyle.Fill;
			_imagingObsDetailsControl.Location = new Point(3, 3);
			_imagingObsDetailsControl.Name = "_imagingObsDetailsControl";
			_imagingObsDetailsControl.Size = new Size(543, 458);
			_imagingObsDetailsControl.TabIndex = 0;
        	_tabImagingObservations.Controls.Add(_imagingObsDetailsControl);

        	_wbDetails.DataBindings.Add("DocumentText", bindingSource, "AllDetailsHtml", true, DataSourceUpdateMode.OnPropertyChanged);
        	DisableClickSounds();

        	_tabAnatomicEnities.ResumeLayout(false);
        	_tabImagingObservations.ResumeLayout(false);
        	_infoTabs.ResumeLayout(false);
        	ResumeLayout(false);
		}

		private void ContextMenuWbOpening(object sender, CancelEventArgs e)
		{
			copyToolStripMenuItem.Enabled = !string.IsNullOrEmpty(SelectedWebBrowserText);
			selectAllToolStripMenuItem.Enabled = WebDocument != null;
		}

		private void CopyToolStripMenuItemClick(object sender, EventArgs e)
		{
			try
			{
				Clipboard.SetText(SelectedWebBrowserText);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to place annotation details onto clipboard");
			}
		}

		private void SelectAllToolStripMenuItemClick(object sender, EventArgs e)
		{
			var htmlDocument = WebDocument;
			if (htmlDocument != null && htmlDocument.body != null)
			{
				try
				{
					((DispHTMLBody) htmlDocument.body).createTextRange().select();
				}
				catch (InvalidCastException ex)
				{
					Platform.Log(LogLevel.Error, ex, "Failed to get body of the Annotation Details browser control");
				}
				catch (COMException ex)
				{
					Platform.Log(LogLevel.Error, ex, "Failed to select all text in the Annotation Details browser control");
				}
			}
		}

    	private string SelectedWebBrowserText
    	{
			get
			{
				var htmlDocument = WebDocument;
				if (htmlDocument != null)
				{
					var currentSelection = htmlDocument.selection;
					if (currentSelection != null)
					{
						var range = currentSelection.createRange() as IHTMLTxtRange;
						if (range != null)
						{
							return range.text;
						}
					}
				}

				return null;
			}
    	}

    	private IHTMLDocument2 WebDocument
    	{
    		get { return _wbDetails.Document != null ? _wbDetails.Document.DomDocument as IHTMLDocument2 : null; }
    	}

		static private void DisableClickSounds()
		{
			CoInternetSetFeatureEnabled(
				FEATURE_DISABLE_NAVIGATION_SOUNDS,
				SET_FEATURE_ON_PROCESS,
				true);
		}
	}
}
