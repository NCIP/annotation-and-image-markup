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
using ClearCanvas.Desktop;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Tools;
using ClearCanvas.Desktop.Actions;

namespace AIMTemplateService
{
	/// <summary>
	/// Defines an extension point so that web link shortcuts can be
	/// placed on the shortcut toolbar of the browser.
	/// </summary>
	[ExtensionPoint()]
	public class WebBrowserToolExtensionPoint : ExtensionPoint<ITool>
	{
	}

	/// <summary>
	/// Extension point for views onto <see cref="BrowserComponent"/>.
	/// </summary>
	[ExtensionPoint]
	public class BrowserComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
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
	[AssociateView(typeof(BrowserComponentViewExtensionPoint))]
	public class WebBrowserComponent : ApplicationComponent
	{
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
			WebBrowserComponent _component;

			public WebBrowserToolContext(WebBrowserComponent component)
			{
				Platform.CheckForNullReference(component, "component");
				_component = component;
			}


			#region IWebBrowserToolContext Members

			public string Url
			{
				get { return _component.Url;  }
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

		#region Private members
		
		private string _url;
        private string _documentText;

		private event EventHandler _urlChangedEvent;
		private event EventHandler _goInvokedEvent;
		private event EventHandler _backInvokedEvent;
		private event EventHandler _forwardInvokedEvent;
		private event EventHandler _refreshInvokedEvent;
		private event EventHandler _cancelInvokedEvent;
        private event EventHandler _documentTextChangedEvent;

		private ToolSet _toolSet;
		private ActionModelRoot _toolbarModel;
		
		#endregion

		/// <summary>
		/// Constructor
		/// </summary>
		public WebBrowserComponent()
		{
		}

        public string DocumentText
        {
            get { return _documentText; }
            set
            {
                _documentText = value;
                EventsHelper.Fire(_documentTextChangedEvent, this, EventArgs.Empty);
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
				EventsHelper.Fire(_urlChangedEvent, this, EventArgs.Empty);
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
			add { _urlChangedEvent += value; }
			remove { _urlChangedEvent -= value; }
		}

		public event EventHandler GoInvoked
		{
			add { _goInvokedEvent += value; }
			remove { _goInvokedEvent -= value; }
		}

		public event EventHandler BackInvoked
		{
			add { _backInvokedEvent += value; }
			remove { _backInvokedEvent -= value; }
		}

		public event EventHandler ForwardInvoked
		{
			add { _forwardInvokedEvent += value; }
			remove { _forwardInvokedEvent -= value; }
		}

		public event EventHandler RefreshInvoked
		{
			add { _refreshInvokedEvent += value; }
			remove { _refreshInvokedEvent -= value; }
		}

		public event EventHandler CancelInvoked
		{
			add { _cancelInvokedEvent += value; }
			remove { _cancelInvokedEvent -= value; }
		}

        public event EventHandler DocumentTextChanged
        {
            add { _documentTextChangedEvent += value; }
            remove { _documentTextChangedEvent -= value; }
        }

		/// <summary>
		/// Allows the favourites menu to be integrated into the main menu.
		/// </summary>
        //public override IActionSet ExportedActions
        //{
        //    get
        //    {
        //        return FavouritesBuilder.Build(this);
        //    }
        //}

		public override void Start()
		{
			// Instantiate all the tools that are marked with the
			// WebBrowserToolExtensionPoint attribute (e.g. LaunchGoogleTool)
			_toolSet = new ToolSet(new WebBrowserToolExtensionPoint(), new WebBrowserToolContext(this));

			// Create the action model so that the view can read it and create
			// the appropriate toolbar items.
			_toolbarModel = ActionModelRoot.CreateModel(this.GetType().FullName, "webbrowser-toolbar", _toolSet.Actions);

			base.Start();
		}

		public override void Stop()
		{
			base.Stop();
		}

		/// <summary>
		/// Sets the tab title.
		/// </summary>
		/// <param name="title"></param>
		public void SetDocumentTitle(string title)
		{
			this.Host.Title = title;
		}

		public void Go()
		{
			EventsHelper.Fire(_goInvokedEvent, this, EventArgs.Empty);
		}

		public void Back()
		{
			EventsHelper.Fire(_backInvokedEvent, this, EventArgs.Empty);
		}

		public void Forward()
		{
			EventsHelper.Fire(_forwardInvokedEvent, this, EventArgs.Empty);
		}

		public void Refresh()
		{
			EventsHelper.Fire(_refreshInvokedEvent, this, EventArgs.Empty);
		}

		public void Cancel()
		{
			EventsHelper.Fire(_cancelInvokedEvent, this, EventArgs.Empty);
		}
	}
}
