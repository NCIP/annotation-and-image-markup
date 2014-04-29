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
using System.Linq;
using System.Text;
using ClearCanvas.Desktop;
using AIM.Annotation;

namespace AIMTemplateService
{
    public class ATSWebBrowserContainer : SplitComponentContainer
    {
        private ATSWebBrowserContainer(SplitPane pane1, SplitPane pane2)
			: base(pane1, pane2, SplitOrientation.Vertical)
        {

        }

        public static ATSWebBrowserContainer Create(IDesktopWindow desktopWindow)
        {
            var atsWebBrowserComponent = new ATSWebBrowserComponent();

            var aimAnnotationComponent = AimAnnotationComponent.Create(desktopWindow, true);
            aimAnnotationComponent.Preview = true;

            atsWebBrowserComponent.AimAnnotationComponent = aimAnnotationComponent;

            var leftPane = new SplitPane(SR.TitleWebBrowserPane, atsWebBrowserComponent, 0.75f);
            var rightPane = new SplitPane(SR.TitleAimAnnotationPane, aimAnnotationComponent, 0.25f);

            return new ATSWebBrowserContainer(leftPane, rightPane);
        }
    }
}
