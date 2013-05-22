//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Tools;

namespace AIM.Annotation.Tools
{
	[ExtensionOf(typeof(DesktopToolExtensionPoint))]
	public class AnnotationQueueSendTool : Tool<IDesktopToolContext>
	{
		private bool _enabled;
		private event EventHandler _enabledChanged;

		public AnnotationQueueSendTool()
		{
			_enabled = true;
		}

		public override void Initialize()
		{
			base.Initialize();
			AimDataServiceSendQueue.Instance.Start();
		}

		protected override void Dispose(bool disposing)
		{
			base.Dispose(disposing);
			AimDataServiceSendQueue.Instance.Stop();
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
	}
}
