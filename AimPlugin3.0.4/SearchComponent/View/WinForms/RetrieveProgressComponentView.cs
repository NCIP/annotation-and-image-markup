//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.Text;

using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.View.WinForms;

namespace SearchComponent.View.WinForms
{
    /// <summary>
    /// Provides a Windows Forms view onto <see cref="RetrieveProgressComponent"/>.
    /// </summary>
    [ExtensionOf(typeof(RetrieveProgressComponentViewExtensionPoint))]
    public class RetrieveProgressComponentView : WinFormsView, IApplicationComponentView
    {
        private RetrieveProgressComponent _component;
        private RetrieveProgressComponentControl _control;

        #region IApplicationComponentView Members

        /// <summary>
        /// Called by the host to assign this view to a component.
        /// </summary>
        public void SetComponent(IApplicationComponent component)
        {
            _component = (RetrieveProgressComponent)component;
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
                    _control = new RetrieveProgressComponentControl(_component);
                }
                return _control;
            }
        }
    }
}
