//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using AIM.Annotation.Configuration;
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.View.WinForms;

namespace AIM.Annotation.View.WinForms.Configuration
{
	/// <summary>
	/// Provides a Windows Forms view onto <see cref="AimConfigurationComponent"/>.
	/// </summary>
	[ExtensionOf(typeof(AimConfigurationComponentViewExtensionPoint))]
	public class AimConfigurationComponentView : WinFormsView, IApplicationComponentView
	{
		private AimConfigurationComponent _component;
		private AimConfigurationComponentControl _control;

		#region IApplicationComponentView Members

		/// <summary>
		/// Called by the host to assign this view to a component.
		/// </summary>
		public void SetComponent(IApplicationComponent component)
		{
			_component = (AimConfigurationComponent)component;
		}

		#endregion

		/// <summary>
		/// Gets the underlying GUI component for this view.
		/// </summary>
		public override object GuiElement
		{
			get
			{
				if (_control == null)
				{
					_control = new AimConfigurationComponentControl(_component);
				}
				return _control;
			}
		}
	}
}
