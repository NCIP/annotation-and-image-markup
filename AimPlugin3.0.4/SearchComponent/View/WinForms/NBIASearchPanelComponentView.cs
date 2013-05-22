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
    /// Provides a Windows Forms view onto <see cref="NBIASearchPanelComponent"/>.
    /// </summary>
	[ExtensionOf(typeof(NBIASearchCriteriaComponentViewExtensionPoint))]
    public class NBIASearchPanelComponentView : WinFormsView, IApplicationComponentView
    {
		private NBIASearchCriteriaComponent _component;
        private NBIASearchCriteriaComponentControl _control;

        #region IApplicationComponentView Members

        /// <summary>
        /// Called by the host to assign this view to a component.
        /// </summary>
        public void SetComponent(IApplicationComponent component)
        {
            _component = (NBIASearchCriteriaComponent)component;
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
                    _control = new NBIASearchCriteriaComponentControl(_component);
                }
                return _control;
            }
        }
    }
}
