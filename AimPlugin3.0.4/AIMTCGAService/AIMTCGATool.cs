#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Tools;
using ClearCanvas.Desktop.Actions;

namespace AIMTCGAService
{
    [MenuAction("apply", "global-menus/MenuTools/caGrid Tools/AIM Data Service Settings", "Apply")]
    [ButtonAction("apply", "global-toolbars/ToolbarMyTools/AIMTCGATool", "Apply")]
    [Tooltip("apply", "AIM Data Service Settings")]
    [IconSet("apply", IconScheme.Colour, "Icons.AIMTCGAToolSmall.png", "Icons.AIMTCGAToolMedium.png", "Icons.AIMTCGAToolLarge.png")]
    [EnabledStateObserver("apply", "Enabled", "EnabledChanged")]

    [ExtensionOf(typeof(DesktopToolExtensionPoint))]
    public class AIMTCGATool : Tool<IDesktopToolContext>
    {
        private bool _enabled;
        private event EventHandler _enabledChanged;

        public AIMTCGATool()
        {
            _enabled = true;
        }

        public override void Initialize()
        {
            base.Initialize();
        }

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

        public event EventHandler EnabledChanged
        {
            add { _enabledChanged += value; }
            remove { _enabledChanged -= value; }
        }

        public void Apply()
        {
            var component = new AIMTCGAComponent();
            var exitCode = ApplicationComponent.LaunchAsDialog(
                Context.DesktopWindow,
                component,
                "AIM Data Service Options");
        }
    }
}
