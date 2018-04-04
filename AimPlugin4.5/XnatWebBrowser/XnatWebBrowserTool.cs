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
using XnatWebBrowser.Configuration;

namespace XnatWebBrowser
{
    [MenuAction("apply", "global-menus/MenuTools/MenuAimTools/MenuXnatImaging", "Apply")]
    [ButtonAction("apply", "global-toolbars/ToolbarStandard/ToolbarWebBrowser", "Apply")]
    [Tooltip("apply", "XNAT Imaging")]
    [IconSet("apply", "Icons.XnatToolSmall.png", "Icons.XnatToolMedium.png", "Icons.XnatToolLarge.png")]
    [EnabledStateObserver("apply", "Enabled", "EnabledChanged")]
    [GroupHint("apply", "Tools.Image.Aim.Xnat")]
    [ExtensionOf(typeof (DesktopToolExtensionPoint))]
    public class XnatWebBrowserTool : Tool<IDesktopToolContext>
    {
        private bool _enabled;

        /// <summary>
        /// Gets whether the tool is actively displayed
        /// </summary>
        internal static bool Active { get; private set; }

        /// <summary>
        /// Default constructor.  A no-args constructor is required by the
        /// framework.  Do not remove.
        /// </summary>
        public XnatWebBrowserTool()
        {
            _enabled = true;
        }

        /// <summary>
        /// Called to determine whether this tool is enabled/disabled in the UI.
        /// </summary>
        public bool Enabled
        {
            get { return _enabled; }
            protected set
            {
                if (_enabled != value)
                {
                    _enabled = value;
                    EventsHelper.Fire(EnabledChanged, this, EventArgs.Empty);
                }
            }
        }

        public event EventHandler EnabledChanged;


        /// <summary>
        /// Called by the framework when the user clicks the "apply" menu item or toolbar button.
        /// </summary>
        public void Apply()
        {
            var component = new XnatWebBrowserComponent();

            ApplicationComponent.LaunchAsWorkspace(Context.DesktopWindow, component, SR.WorkspaceName);
            component.Url = XnatSettings.Default.XnatUrl;
            component.SetDocumentTitle("XNAT Imaging");
            component.Go();
            component.Stopped += ComponentStopped;
            Active = true;
        }

        void  ComponentStopped(object sender, EventArgs e)
        {
            Active = false;
        }
    }
}
