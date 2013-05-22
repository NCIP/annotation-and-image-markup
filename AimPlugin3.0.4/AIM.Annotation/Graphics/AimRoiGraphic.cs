//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using ClearCanvas.Common.Utilities;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InteractiveGraphics;
using ClearCanvas.ImageViewer.RoiGraphics;
using ClearCanvas.Desktop.Actions;

using AIM.Annotation.Configuration;

namespace AIM.Annotation.Graphics
{
    public class AimRoiGraphic : RoiGraphic
    {
        private static AimRoiGraphic _selectedAimRoiGraphic = null;

        public AimRoiGraphic(IGraphic roi) : base(roi) { }
        public AimRoiGraphic(IGraphic roi, IAnnotationCalloutLocationStrategy strategy) : base(roi, strategy) { }

        public static AimRoiGraphic SelectedAimRoiGraphic 
        { 
            get 
            {
                return _selectedAimRoiGraphic; 
            } 
        }

        public override IActionSet GetExportedActions(string site, ClearCanvas.ImageViewer.InputManagement.IMouseInformation mouseInformation)
        {
            IResourceResolver resolver = new ResourceResolver(GetType(), true);
            var @namespace = GetType().FullName;
            var hideAction = new MenuAction(@namespace + ":toggle", new ActionPath(site + "/MenuSetMarkupColorForUser", resolver), ClickActionFlags.None, resolver);
            hideAction.Label = "Set User Markup Color";
            hideAction.Persistent = true;
            hideAction.SetClickHandler(OpenAimMarkupColorOptions);

            IActionSet actions = new ActionSet(new IAction[] { hideAction });
            var other = base.GetExportedActions(site, mouseInformation);
            if (other != null)
                actions = actions.Union(other);

            return actions;
        }

        private void OpenAimMarkupColorOptions()
        {
            _selectedAimRoiGraphic = this;
            ClearCanvas.Desktop.Configuration.ConfigurationDialog.Show(ImageViewer.DesktopWindow, AimMarkupColorComponent.Path);
            _selectedAimRoiGraphic = null;
        }

        public new static AimRoiGraphic CreateEllipse()
        {
            var roiGraphic = new AimRoiGraphic(new BoundableResizeControlGraphic(new BoundableStretchControlGraphic(new MoveControlGraphic(new EllipsePrimitive()))));
            roiGraphic.State = roiGraphic.CreateInactiveState();
            return roiGraphic;
        }

        public new static AimRoiGraphic CreateRectangle()
        {
            var roiGraphic = new AimRoiGraphic(new BoundableResizeControlGraphic(new BoundableStretchControlGraphic(new MoveControlGraphic(new RectanglePrimitive()))));
            roiGraphic.State = roiGraphic.CreateInactiveState();
            return roiGraphic;
        }

        public new static AimRoiGraphic CreatePolygon()
        {
            var roiGraphic = new AimRoiGraphic(new PolygonControlGraphic(true, new MoveControlGraphic(new PolylineGraphic(true))));
            roiGraphic.State = roiGraphic.CreateInactiveState();
            return roiGraphic;
        }
    }
}
