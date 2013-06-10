#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections.Generic;
using System.Text;

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.View.WinForms;

namespace SearchComponent.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms view onto <see cref="AIMSearchCriteriaComponent"/>.
    /// </summary>
    [ExtensionOf(typeof(AIMSearchCriteriaComponentViewExtensionPoint))]
    public class AIMSearchCriteriaComponentView : WinFormsView, IApplicationComponentView
    {
        private AIMSearchCriteriaComponent _component;
        private AIMSearchCriteriaComponentControl _control;

        #region IApplicationComponentView Members

        /// <summary>
        /// Called by the host to assign this view to a component.
        /// </summary>
        public void SetComponent(IApplicationComponent component)
        {
            _component = (AIMSearchCriteriaComponent)component;
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
                    _control = new AIMSearchCriteriaComponentControl(_component);
                }
                return _control;
            }
        }
    }
}
