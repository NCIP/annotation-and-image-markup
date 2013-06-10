#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.View.WinForms;

namespace AIM.Annotation.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms view onto <see cref="AimAnnotationComponent"/>.
    /// </summary>
    [ExtensionOf(typeof(AimAnnotationComponentViewExtensionPoint))]
    public class AimAnnotationComponentView : WinFormsView, IApplicationComponentView
    {
        private AimAnnotationComponent _component;
        private AimAnnotationComponentControl _control;

        #region IApplicationComponentView Members

        /// <summary>
        /// Called by the host to assign this view to a component.
        /// </summary>
        public void SetComponent(IApplicationComponent component)
        {
            _component = (AimAnnotationComponent)component;
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
                    _control = new AimAnnotationComponentControl(_component);
                }
                return _control;
            }
        }
    }
}
