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

using System.Windows.Forms;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Desktop.View.WinForms;

namespace XnatWebBrowser.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms user-interface for <see cref="XnatWebBrowserComponent"/>
    /// </summary>
    public partial class XnatWebBrowserComponentControl : ApplicationComponentUserControl
    {
        private readonly XnatWebBrowserComponent _component;
        private ActionModelNode _toolbarModel;

        /// <summary>
        /// Constructor
        /// </summary>
        public XnatWebBrowserComponentControl(XnatWebBrowserComponent component)
            : base(component)
        {
            InitializeComponent();

            _component = component;

            // Build the shortcut toolbar
            ToolbarModel = _component.ToolbarModel;

            _back.Enabled = _browser.CanGoBack;
            _forward.Enabled = _browser.CanGoForward;

            ListenForComponentEvents();
            ListenForUiEvents();
            ListenForBrowserEvents();

            _browser.ScriptErrorsSuppressed = true;
        }

        private ActionModelNode ToolbarModel
        {
            set
            {
                _toolbarModel = value;
                ToolStripBuilder.Clear(_shortcutToolbar.Items);

                if (_toolbarModel != null)
                {
                    // Use the toolbar model in the component to build the toolbar
                    var style = new ToolStripBuilder.ToolStripBuilderStyle(
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
                delegate { _address.Text = _component.Url; };
            _component.GoInvoked +=
                delegate
                    {
                        _component.Url = _address.Text;
                        _browser.Navigate(_component.Url);
                    };
            _component.BackInvoked +=
                delegate { _browser.GoBack(); };
            _component.ForwardInvoked +=
                delegate { _browser.GoForward(); };
            _component.RefreshInvoked +=
                delegate { _browser.Refresh(); };
            _component.CancelInvoked +=
                delegate { _browser.Stop(); };
            _component.DocumentTextChanged +=
                delegate { _browser.DocumentText = _component.DocumentText; };
        }

        private void ListenForUiEvents()
        {
            _address.TextChanged +=
                delegate { _component.Url = _address.Text; };

            _address.KeyDown +=
                delegate(object sender, KeyEventArgs e)
                    {
                        if (e.KeyCode == Keys.Return)
                            _component.Go();
                    };

            _back.Click +=
                delegate { _component.Back(); };
            _forward.Click +=
                delegate { _component.Forward(); };
            _refresh.Click +=
                delegate { _component.Refresh(); };
            _stop.Click +=
                delegate { _component.Cancel(); };
            _go.Click +=
                delegate { _component.Go(); };
        }

        private void ListenForBrowserEvents()
        {
            _browser.CanGoBackChanged +=
                delegate { _back.Enabled = _browser.CanGoBack; };
            _browser.CanGoForwardChanged +=
                delegate { _forward.Enabled = _browser.CanGoForward; };
            _browser.DocumentTitleChanged +=
                delegate
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
                        _browserProgress.Maximum = (int) e.MaximumProgress;
                        if (e.CurrentProgress > -1 && e.CurrentProgress < e.MaximumProgress)
                            _browserProgress.Value = (int) e.CurrentProgress;
                    };
            _browser.StatusTextChanged +=
                delegate { _browserStatus.Text = _browser.StatusText; };
        }
    }
}
