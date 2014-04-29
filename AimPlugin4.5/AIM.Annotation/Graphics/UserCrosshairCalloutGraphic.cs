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

using ClearCanvas.Common.Utilities;
using ClearCanvas.ImageViewer.Graphics;
using ClearCanvas.ImageViewer.InteractiveGraphics;

namespace AIM.Annotation.Graphics
{
    /// <summary>
    /// A user-interactive version of <see cref="CalloutGraphic"/>.
    /// </summary>
    [Cloneable]
    public class UserCrosshairCalloutGraphic : CrosshairCalloutGraphic
    {
        /// <summary>
        /// Instantiates a new instance of <see cref="UserCalloutGraphic"/>.
        /// </summary>
        public UserCrosshairCalloutGraphic() : base("") { }

        /// <summary>
        /// Cloning constructor.
        /// </summary>
        protected UserCrosshairCalloutGraphic(UserCrosshairCalloutGraphic source, ICloningContext context)
            : base(source, context)
        {
            context.CloneFields(source, this);
        }

        /// <summary>
        /// Gets or sets the callout text label.
        /// </summary>
        public new string Text
        {
            get { return base.Text; }
            set { base.Text = value; }
        }

        /// <summary>
        /// Gets the <see cref="IControlGraphic"/> controlling the <see cref="CalloutGraphic.TextGraphic"/>.
        /// </summary>
        protected new TextEditControlGraphic TextControlGraphic
        {
            get { return (TextEditControlGraphic)base.TextControlGraphic; }
        }

        /// <summary>
        /// Initializes the control chain for the text graphic portion of the callout.
        /// </summary>
        /// <remarks>
        /// This implementation creates a <see cref="TextEditControlGraphic"/> and a <see cref="MoveControlGraphic"/> to allow the
        /// user to interactively edit and move the callout text.
        /// </remarks>
        /// <param name="textGraphic">The text graphic to be controlled.</param>
        /// <returns>A control graphic chain controlling the text graphic.</returns>
        protected override IControlGraphic InitializeTextControlGraphic(ITextGraphic textGraphic)
        {
            return new TextEditControlGraphic(new TextPlaceholderControlGraphic(base.InitializeTextControlGraphic(textGraphic)));
        }

        /// <summary>
        /// Initializes the control chain for the anchor point of the callout.
        /// </summary>
        /// <remarks>
        /// This implementation creates an <see cref="AnchorPointControlGraphic"/> to allow the user to
        /// interactively move the <see cref="CalloutGraphic.AnchorPoint"/> of the callout.
        /// </remarks>
        /// <param name="pointGraphic">The anchor point to be controlled.</param>
        /// <returns>A control graphic chain controlling the anchor point.</returns>
        protected override IControlGraphic InitializePointControlGraphic(IPointGraphic pointGraphic)
        {
            return new AnchorPointControlGraphic(base.InitializePointControlGraphic(pointGraphic));
        }

        /// <summary>
        /// Starts the interactive edit mode of the callout.
        /// </summary>
        /// <returns>True if the callout successfully entered interactive edit mode.</returns>
        public bool StartEdit()
        {
            return this.TextControlGraphic.StartEdit();
        }

        /// <summary>
        /// Ends the interactive edit mode of the callout.
        /// </summary>
        public void EndEdit()
        {
            this.TextControlGraphic.EndEdit();
        }
    }
}
