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
using System.Windows.Forms;

using ClearCanvas.Desktop.View.WinForms;
using ClearCanvas.Desktop.Actions;

namespace AIMTemplateService.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms user-interface for <see cref="BrowserComponent"/>
    /// </summary>
    public partial class WebBrowserComponentControl : ApplicationComponentUserControl
    {
        private WebBrowserComponent _component;
		private ActionModelNode _toolbarModel;

        /// <summary>
        /// Constructor
        /// </summary>
        public WebBrowserComponentControl(WebBrowserComponent component)
            :base(component)
        {
            InitializeComponent();

            _component = component;

			// Build the shortcut toolbar
			this.ToolbarModel = _component.ToolbarModel;

			_back.Enabled = _browser.CanGoBack;
			_forward.Enabled = _browser.CanGoForward;

			ListenForComponentEvents();
			ListenForUIEvents();
			ListenForBrowserEvents();
        }

		private ActionModelNode ToolbarModel
		{
			get { return _toolbarModel; }
			set
			{
				_toolbarModel = value;
				ToolStripBuilder.Clear(_shortcutToolbar.Items);
				
				if (_toolbarModel != null)
				{
					// Use the toolbar model in the component to build the toolbar
					ToolStripBuilder.ToolStripBuilderStyle style = new ToolStripBuilder.ToolStripBuilderStyle(
						ToolStripItemDisplayStyle.ImageAndText,
						ToolStripItemAlignment.Left,
						TextImageRelation.ImageBeforeText);
					ToolStripBuilder.BuildToolbar(_shortcutToolbar.Items, _toolbarModel.ChildNodes, style);

					foreach (ToolStripItem item in _shortcutToolbar.Items)
					{
						item.TextImageRelation = TextImageRelation.ImageBeforeText;
						item.DisplayStyle = ToolStripItemDisplayStyle.ImageAndText;
					}
				}
			}
		}

		private void ListenForComponentEvents()
		{
			_component.UrlChanged +=
				delegate(object sender, EventArgs e) { _address.Text = _component.Url; };
			_component.GoInvoked +=
				delegate(object sender, EventArgs e)
				{
					_component.Url = _address.Text;
					_browser.Navigate(_component.Url);
				};
			_component.BackInvoked +=
				delegate(object sender, EventArgs e) { _browser.GoBack(); };
			_component.ForwardInvoked +=
				delegate(object sender, EventArgs e) { _browser.GoForward(); };
			_component.RefreshInvoked +=
				delegate(object sender, EventArgs e) { _browser.Refresh(); };
			_component.CancelInvoked +=
				delegate(object sender, EventArgs e) { _browser.Stop(); };
            _component.DocumentTextChanged +=
                delegate(object sender, EventArgs e) { _browser.DocumentText = _component.DocumentText; };
		}

		private void ListenForUIEvents()
		{
			_address.TextChanged +=
				delegate(object sender, EventArgs e) { _component.Url = _address.Text; };

			_address.KeyDown +=
				delegate(object sender, KeyEventArgs e)
				{
					if (e.KeyCode == Keys.Return)
						_component.Go();
				};

			_back.Click +=
				delegate(object sender, EventArgs e) { _component.Back(); };
			_forward.Click +=
				delegate(object sender, EventArgs e) { _component.Forward(); };
			_refresh.Click +=
				delegate(object sender, EventArgs e) { _component.Refresh(); };
			_stop.Click +=
				delegate(object sender, EventArgs e) { _component.Cancel(); };
			_go.Click +=
				delegate(object sender, EventArgs e) { _component.Go(); };
		}

		private void ListenForBrowserEvents()
		{
			_browser.CanGoBackChanged +=
				delegate(object sender, EventArgs e) { _back.Enabled = _browser.CanGoBack; };
			_browser.CanGoForwardChanged +=
				delegate(object sender, EventArgs e) { _forward.Enabled = _browser.CanGoForward; };
			_browser.DocumentTitleChanged +=
				delegate(object sender, EventArgs e) 
				{
                    if (_browser.DocumentTitle.Equals("NBIA - National Biomedical Imaging Archive"))
					    _component.SetDocumentTitle("NBIA download archive");
                    else
                        _component.SetDocumentTitle(_browser.DocumentTitle);
					_component.Url = _browser.Url.ToString();
				};
			_browser.ProgressChanged +=
				delegate(object sender, WebBrowserProgressChangedEventArgs e)
				{
					_browserProgress.Maximum = (int)e.MaximumProgress;
					_browserProgress.Value = (int)e.CurrentProgress;
				};
			_browser.StatusTextChanged +=
				delegate(object sender, EventArgs e) { _browserStatus.Text = _browser.StatusText; };
            
		}
    }
}
