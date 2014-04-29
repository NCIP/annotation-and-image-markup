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
using System.Collections.Generic;
using System.Runtime.Remoting.Contexts;
using AIM.Annotation;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Tools;
using ClearCanvas.Desktop.Actions;
using ClearCanvas.ImageViewer;
using ClearCanvas.ImageViewer.BaseTools;

namespace AIMTemplateService
{
    [MenuAction("apply", "global-menus/MenuTools/MenuAimTools/ATSToolMenu", "Apply")]
    [ButtonAction("apply", "global-toolbars/ToolbarStandard/ATSToolbarWebBrowser", "Apply")]
    [Tooltip("apply", "ATSToolTooltip")]
    [IconSet("apply", "Icons.ATSToolSmall.png", "Icons.ATSToolMedium.png", "Icons.ATSToolLarge.png")]
    [EnabledStateObserver("apply", "Enabled", "EnabledChanged")]
    [GroupHint("apply", "Tools.Image.Aim.Ats")]

    [ExtensionOf(typeof(ImageViewerToolExtensionPoint))]
    public class ATSWebBrowserTool : ImageViewerTool
    {
        private bool _enabled;
        private event EventHandler _enabledChanged;

        // List of created shelfs
        private static readonly Dictionary<IDesktopWindow, IShelf> _shelves = new Dictionary<IDesktopWindow, IShelf>();
        private IDesktopWindow _desktopWindow;

        /// <summary>
        /// Default constructor.  A no-args constructor is required by the
        /// framework.  Do not remove.
        /// </summary>
        public ATSWebBrowserTool()
        {
            _enabled = true;
        }

        /// <summary>
        /// Called by the framework to initialize this tool.
        /// </summary>
        public override void Initialize()
        {
            base.Initialize();

            // TODO: add any significant initialization code here rather than in the constructor
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
                    EventsHelper.Fire(_enabledChanged, this, EventArgs.Empty);
                }
            }
        }

        /// <summary>
        /// Notifies that the Enabled state of this tool has changed.
        /// </summary>
        public event EventHandler EnabledChanged
        {
            add { _enabledChanged += value; }
            remove { _enabledChanged -= value; }
        }

        /// <summary>
        /// Called by the framework when the user clicks the "apply" menu item or toolbar button.
        /// </summary>
        public void Apply()
        {

			// check if a layout component is already displayed
            if (_shelves.ContainsKey(this.Context.DesktopWindow))
            {
                _shelves[this.Context.DesktopWindow].Activate();
            }
            else
            {
                BlockingOperation.Run(delegate
                                        {
                                            _desktopWindow = Context.DesktopWindow;

                                            var atsWebBrowserContainer = ATSWebBrowserContainer.Create(_desktopWindow);
                                            var atsWebBrowserComponent =
                                                atsWebBrowserContainer.Pane1.Component as ATSWebBrowserComponent;
                                            var aimAnnotationComponent =
                                                atsWebBrowserContainer.Pane2.Component as AimAnnotationComponent;

                                            if (atsWebBrowserComponent != null && aimAnnotationComponent != null)
                                            {

                                                ApplicationComponent.LaunchAsWorkspace(Context.DesktopWindow, atsWebBrowserContainer, SR.WorkspaceName);
                                                atsWebBrowserComponent.Url = Configuration.AtsSettings.Default.AtsUrl;
                                                atsWebBrowserComponent.AimAnnotationComponent = aimAnnotationComponent;
                                                atsWebBrowserComponent.Go(); 
                                            }                                    
                                        });
            }
            
        }


        private void OnShelfClosed(object sender, ClosedEventArgs e)
        {
            // We need to cache the owner DesktopWindow (_desktopWindow) because this tool is an 
            // ImageViewer tool, disposed when the viewer component is disposed.  Shelves, however,
            // exist at the DesktopWindow level and there can only be one of each type of shelf
            // open at the same time per DesktopWindow (otherwise things look funny).  Because of 
            // this, we need to allow this event handling method to be called after this tool has
            // already been disposed (e.g. viewer workspace closed), which is why we store the 
            // _desktopWindow variable.
            _shelves[_desktopWindow].Closed -= OnShelfClosed;
            _shelves.Remove(_desktopWindow);
            _desktopWindow = null;
        }
    }
}
