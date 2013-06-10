#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Drawing;

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.View.WinForms;

using AIM.Annotation.Configuration;
namespace AIM.Annotation.View.WinForms.Configuration
{
    [ExtensionOf(typeof(AimMarkupColorComponentViewExtensionPoint))]
    public class AimMarkupColorComponentView : WinFormsView, IApplicationComponentView
    {
        private AimMarkupColorComponent _component;

        private AimMarkupColorComponentControl _control;

        #region IApplicationComponentView Members

        /// <summary>
        /// Called by the host to assign this view to a component.
        /// </summary>
        public void SetComponent(IApplicationComponent component)
        {
            _component = (AimMarkupColorComponent)component;
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
                    _control = new AimMarkupColorComponentControl(_component);
                }
                return _control;
            }
        }
    }
}
