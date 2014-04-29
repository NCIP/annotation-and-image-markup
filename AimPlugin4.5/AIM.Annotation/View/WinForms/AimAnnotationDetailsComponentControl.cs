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
		private readonly AimCodeSequenceDetailsControl _imagingObsDetailsControl;
		private readonly AimCodeSequenceDetailsControl _anatomicEntitiesDetailsControl;

		private readonly AimAnnotationDetailsComponent _component;

		/// <summary>
		/// Constructor.
		/// </summary>
		public AimAnnotationDetailsComponentControl(AimAnnotationDetailsComponent component)
			: base(component)
		{
			_component = component;
			InitializeComponent();

			BindingSource bindingSource = new BindingSource();
			bindingSource.DataSource = _component;

			// TODO add .NET databindings to bindingSource
			_tboxCalculations.DataBindings.Add("Lines", bindingSource, "CalculationDescriptions", true, DataSourceUpdateMode.OnPropertyChanged);
			_infoTabs.DataBindings.Add("Visible", bindingSource, "IsImageViewerActive", true, DataSourceUpdateMode.OnPropertyChanged);

			this._tabAnatomicEntities.SuspendLayout();
			this._tabImagingObservations.SuspendLayout();
			this._infoTabs.SuspendLayout();
			this.SuspendLayout();

			// Anatomic Entities
			_anatomicEntitiesDetailsControl = new AimCodeSequenceDetailsControl(component, "AnatomicEntities");
			this._anatomicEntitiesDetailsControl.Dock = DockStyle.Fill;
			this._anatomicEntitiesDetailsControl.Location = new Point(3, 3);
			this._anatomicEntitiesDetailsControl.Name = "_anatomicEntitiesDetailsControl";
			this._anatomicEntitiesDetailsControl.Size = new Size(543, 458);
			this._anatomicEntitiesDetailsControl.TabIndex = 0;
			this._tabAnatomicEntities.Controls.Add(_anatomicEntitiesDetailsControl);

			_imagingObsDetailsControl = new AimCodeSequenceDetailsControl(component, "ImagingObservations");
			this._imagingObsDetailsControl.Dock = DockStyle.Fill;
			this._imagingObsDetailsControl.Location = new Point(3, 3);
			this._imagingObsDetailsControl.Name = "_imagingObsDetailsControl";
			this._imagingObsDetailsControl.Size = new Size(543, 458);
			this._imagingObsDetailsControl.TabIndex = 0;
			this._tabImagingObservations.Controls.Add(_imagingObsDetailsControl);

			this._wbDetails.DataBindings.Add("DocumentText", bindingSource, "AllDetailsHtml", true, DataSourceUpdateMode.OnPropertyChanged);
			DisableClickSounds(); // no annoying "click" sound when databinding is in progress for the WebBrowser

			this._tabAnatomicEntities.ResumeLayout(false);
			this._tabImagingObservations.ResumeLayout(false);
			this._infoTabs.ResumeLayout(false);
			this.ResumeLayout(false);
		}

		#region WebBrowser Context Menu

		private void contextMenuWb_Opening(object sender, CancelEventArgs e)
		{
			copyToolStripMenuItem.Enabled = !string.IsNullOrEmpty(this.SelectedWebBrowserText);
			selectAllToolStripMenuItem.Enabled = this.WebDocument != null;
		}

		private void copyToolStripMenuItem_Click(object sender, EventArgs e)
		{
			try
			{
				Clipboard.SetText(this.SelectedWebBrowserText);
			}
			catch (Exception ex)
			{
				Platform.Log(LogLevel.Error, ex, "Failed to place annotation details onto clipboard");
			}
		}

		private void selectAllToolStripMenuItem_Click(object sender, EventArgs e)
		{
			IHTMLDocument2 htmlDocument = this.WebDocument;
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
				IHTMLDocument2 htmlDocument = this.WebDocument;
				if (htmlDocument != null)
				{
					IHTMLSelectionObject currentSelection = htmlDocument.selection;
					if (currentSelection != null)
					{
						IHTMLTxtRange range = currentSelection.createRange() as IHTMLTxtRange;
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

		#endregion

		#region Disable WebBrowser Click Sound

		const int FEATURE_DISABLE_NAVIGATION_SOUNDS = 21;
		const int SET_FEATURE_ON_THREAD = 0x00000001;
		const int SET_FEATURE_ON_PROCESS = 0x00000002;
		const int SET_FEATURE_IN_REGISTRY = 0x00000004;
		const int SET_FEATURE_ON_THREAD_LOCALMACHINE = 0x00000008;
		const int SET_FEATURE_ON_THREAD_INTRANET = 0x00000010;
		const int SET_FEATURE_ON_THREAD_TRUSTED = 0x00000020;
		const int SET_FEATURE_ON_THREAD_INTERNET = 0x00000040;
		const int SET_FEATURE_ON_THREAD_RESTRICTED = 0x00000080;

		[DllImport("urlmon.dll")]
		[PreserveSig]
		[return: MarshalAs(UnmanagedType.Error)]
		static extern int CoInternetSetFeatureEnabled(
			int featureEntry,
			[MarshalAs(UnmanagedType.U4)] int dwFlags,
			bool fEnable);

		static private void DisableClickSounds()
		{
			CoInternetSetFeatureEnabled(
				FEATURE_DISABLE_NAVIGATION_SOUNDS,
				SET_FEATURE_ON_PROCESS,
				true);
		}

		#endregion
	}
}
