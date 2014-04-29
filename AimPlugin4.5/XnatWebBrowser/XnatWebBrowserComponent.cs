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
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.Desktop.Tools;

namespace XnatWebBrowser
{
    /// <summary>
    /// Defines an extension point so that web link shortcuts can be
    /// placed on the shortcut toolbar of the browser.
    /// </summary>
    [ExtensionPoint]
    public class XnatWebBrowserToolExtensionPoint : ExtensionPoint<ITool>
    {
    }

    /// <summary>
    /// Extension point for views onto <see cref="XnatWebBrowserComponent"/>.
    /// </summary>
    [ExtensionPoint]
    public class XnatWebBrowserComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
    {
    }

    /// <summary>
    /// The interface that is consumed by the "shortcut tools", such as
    /// the LaunchGoogleTool.
    /// </summary>
    public interface IWebBrowserToolContext : IToolContext
    {
        string Url { get; set; }
        void Go();
        void Back();
        void Forward();
        void Refresh();
        void Cancel();
    }

    /// <summary>
    /// BrowserComponent class
    /// </summary>
    [AssociateView(typeof (XnatWebBrowserComponentViewExtensionPoint))]
    public class XnatWebBrowserComponent : ApplicationComponent
    {
        public string DocumentText
        {
            get { return _documentText; }
            set
            {
                _documentText = value;
                EventsHelper.Fire(DocumentTextChangedEvent, this, EventArgs.Empty);
            }
        }

        /// <summary>
        /// The current URL of the web browser.
        /// </summary>
        public string Url
        {
            get { return _url; }
            set
            {
                _url = value;
                EventsHelper.Fire(UrlChangedEvent, this, EventArgs.Empty);
            }
        }

        /// <summary>
        /// Used by the view to create the shortcut toolbar.
        /// </summary>
        public ActionModelRoot ToolbarModel
        {
            get { return _toolbarModel; }
        }

        public event EventHandler UrlChanged
        {
            add { UrlChangedEvent += value; }
            remove { UrlChangedEvent -= value; }
        }

        public event EventHandler GoInvoked
        {
            add { GoInvokedEvent += value; }
            remove { GoInvokedEvent -= value; }
        }

        public event EventHandler BackInvoked
        {
            add { BackInvokedEvent += value; }
            remove { BackInvokedEvent -= value; }
        }

        public event EventHandler ForwardInvoked
        {
            add { ForwardInvokedEvent += value; }
            remove { ForwardInvokedEvent -= value; }
        }

        public event EventHandler RefreshInvoked
        {
            add { RefreshInvokedEvent += value; }
            remove { RefreshInvokedEvent -= value; }
        }

        public event EventHandler CancelInvoked
        {
            add { CancelInvokedEvent += value; }
            remove { CancelInvokedEvent -= value; }
        }

        public event EventHandler DocumentTextChanged
        {
            add { DocumentTextChangedEvent += value; }
            remove { DocumentTextChangedEvent -= value; }
        }

        public override void Start()
        {
            // Instantiate all the tools that are marked with the
            // WebBrowserToolExtensionPoint attribute (e.g. LaunchGoogleTool)
            _toolSet = new ToolSet(new XnatWebBrowserToolExtensionPoint(), new WebBrowserToolContext(this));

            // Create the action model so that the view can read it and create
            // the appropriate toolbar items.
            _toolbarModel = ActionModelRoot.CreateModel(GetType().FullName, "webbrowser-toolbar", _toolSet.Actions);

            base.Start();
        }

        
        /// <summary>
        /// Sets the tab title.
        /// </summary>
        /// <param name="title"></param>
        public void SetDocumentTitle(string title)
        {
            Host.Title = title;
        }

        public void Go()
        {
            EventsHelper.Fire(GoInvokedEvent, this, EventArgs.Empty);
        }

        public void Back()
        {
            EventsHelper.Fire(BackInvokedEvent, this, EventArgs.Empty);
        }

        public void Forward()
        {
            EventsHelper.Fire(ForwardInvokedEvent, this, EventArgs.Empty);
        }

        public void Refresh()
        {
            EventsHelper.Fire(RefreshInvokedEvent, this, EventArgs.Empty);
        }

        public void Cancel()
        {
            EventsHelper.Fire(CancelInvokedEvent, this, EventArgs.Empty);
        }

        #region Nested type: WebBrowserToolContext

        /// <summary>
        /// An internal class that implements IWebBrowserToolContext.
        /// Note that WebBrowserToolContext just calls members of
        /// WebBrowserComponent. Most of the time, you will want to create
        /// an IXXXToolContext implementation that just calls members
        /// of the XXXComponent. In essence, your IXXXToolContext determines
        /// what members of XXXComponent your tools will see.
        /// </summary>
        public class WebBrowserToolContext : ToolContext, IWebBrowserToolContext
        {
            private readonly XnatWebBrowserComponent _component;

            public WebBrowserToolContext(XnatWebBrowserComponent component)
            {
                Platform.CheckForNullReference(component, "component");
                _component = component;
            }

            #region IWebBrowserToolContext Members

            public string Url
            {
                get { return _component.Url; }
                set { _component.Url = value; }
            }

            public void Go()
            {
                _component.Go();
            }

            public void Back()
            {
                _component.Back();
            }

            public void Forward()
            {
                _component.Forward();
            }

            public void Refresh()
            {
                _component.Refresh();
            }

            public void Cancel()
            {
                _component.Cancel();
            }

            #endregion
        }

        #endregion

        #region Private members

        private string _documentText;
        private ToolSet _toolSet;
        private ActionModelRoot _toolbarModel;
        private string _url;

        private event EventHandler UrlChangedEvent;
        private event EventHandler GoInvokedEvent;
        private event EventHandler BackInvokedEvent;
        private event EventHandler ForwardInvokedEvent;
        private event EventHandler RefreshInvokedEvent;
        private event EventHandler CancelInvokedEvent;
        private event EventHandler DocumentTextChangedEvent;

        #endregion
    }
}
