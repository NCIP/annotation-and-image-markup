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
using System.Threading;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Input;
using AIM.Annotation.TemplateTree;
using ClearCanvas.Common;
using OpenFileDialog = Microsoft.Win32.OpenFileDialog;
using UserControl = System.Windows.Controls.UserControl;

namespace AIM.Annotation.View.WinForms.Wpf
{
    /// <summary>
    /// Interaction logic for AimAnnotationComponentWpfControl.xaml
    /// </summary>
    public partial class AimAnnotationComponentWpfControl : UserControl
    {
        public event EventHandler CheckingChildControlValidity;

        public TemplateWpfControl TemplateControl { get; private set; }

        public AimAnnotationComponent Component { get; private set; }

        internal static AimAnnotationComponentWpfControl Instance { get; private set; }

        internal static void InitializeAimAnnotationWpfControl(AimAnnotationComponent component)
        {
            Instance = new AimAnnotationComponentWpfControl(component);
        }

        private AimAnnotationComponentWpfControl(AimAnnotationComponent component)
        {
            Component = component;
            InitializeComponent();

            InitializeAnnotationTypeCombo();
            InitializeTemplateControl();

            _buttonCreateAnnotation.IsEnabled = Component.CreateAnnotationEnabled;

            Component.TemplateTreeSet += OnTemplateTreeSet;
            Component.PropertyChanged += ComponentPropertyChanged;


            _buttonCreateAnnotation.IsEnabled = Component.CreateAnnotationEnabled;
            _buttonResetAnnotation.IsEnabled = Component.ResetButtonEnabled;
            _buttonUserInfo.IsEnabled = Component.UserInfoButtonEnabled;
            if (Component.CreateAnnotationEnabled)
                _buttonWhyIsTemplateIncomplete.Visibility = Visibility.Hidden;

            _btnExtension1.Visibility = Visibility.Hidden;

            try
            {
                // Create extension points that use this component
                AimAnnotationExtensionPoint xp = new AimAnnotationExtensionPoint();
                Object[] extensions = xp.CreateExtensions();
                if (extensions.Length > 0)
                {
                    IAimAnnotationExtension extension = (IAimAnnotationExtension)extensions[0];
                    extension.Component = Component;
                    _btnExtension1.Content = extension.ButtonText;
                    _btnExtension1.Click += extension.OnButtonClick;
                    _btnExtension1.Visibility = Visibility.Visible;
                    _btnExtension1.IsEnabled = false;
                }
            }
            catch (NotSupportedException ex)
            {
                Platform.Log(LogLevel.Error, ex, "Failed to create AimAnnotationExtension", null);
            }
        }

        void ComponentPropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "CreateAnnotationEnabled")
            {
                _buttonCreateAnnotation.IsEnabled = Component.CreateAnnotationEnabled;
                _btnExtension1.IsEnabled = Component.CreateAnnotationEnabled;

                _buttonWhyIsTemplateIncomplete.Visibility = Component.CreateAnnotationEnabled ? Visibility.Hidden : Visibility.Visible;
                TemplateControl.UpdateValid();
            }
            else if (e.PropertyName == "AvailableAnnotationTypes")
            {
                // Reinitialize templates list after document is updated
                SynchronizationContext.Current.Post(
                    delegate
                    { InitializeAnnotationTypeCombo(); }
                    , null);
                _cmbAnnotationType.Items.Refresh();
                _buttonCreateAnnotation.IsEnabled = Component.CreateAnnotationEnabled;
                _btnExtension1.IsEnabled = Component.CreateAnnotationEnabled;

                _buttonWhyIsTemplateIncomplete.Visibility = Component.CreateAnnotationEnabled ? Visibility.Hidden : Visibility.Visible;
                TemplateControl.UpdateValid();
            }
            else if (e.PropertyName == "Preview")
            {
                _buttonUserInfo.IsEnabled = Component.UserInfoButtonEnabled;
            }
            else if (e.PropertyName == "AnnotationModuleEnabled")
            {
                _buttonCreateAnnotation.IsEnabled = Component.CreateAnnotationEnabled;
                _buttonResetAnnotation.IsEnabled = Component.ResetButtonEnabled;
                _buttonUserInfo.IsEnabled = Component.UserInfoButtonEnabled;

                _buttonWhyIsTemplateIncomplete.Visibility = Component.CreateAnnotationEnabled ? Visibility.Hidden : Visibility.Visible;
                TemplateControl.UpdateValid();
            }
            else if (e.PropertyName == "AnnotationStatus")
            {
                AnimateStatusBarText(Component.AnnotationStatus);
            }
        }

        private void BtnSelectTemplateClick(object sender, RoutedEventArgs e)
        {
            // Reload default template when Shift is pressed
            if (Keyboard.IsKeyDown(Key.LeftShift) || Keyboard.IsKeyDown(Key.RightShift))
            {
                var msgBox = new ClearCanvas.Desktop.View.WinForms.MessageBox();
                if (msgBox.Show(@"Do you want to select default template?", MessageBoxActions.YesNo) == DialogBoxAction.Yes)
                {
                    this.SetNewTemplateDocument(null);
                    return;
                }
            }

            var openFileDialog = new OpenFileDialog
                                                {
                                                    DefaultExt = "xml",
                                                    Filter = @"XML Files (*.xml)|*.xml|All Files|*.*",
                                                    Title = @"Open AIM Template File",
                                                    Multiselect = false,
                                                    RestoreDirectory = true,
                                                    InitialDirectory = Component.SelectedAimTemplateLocalFolder
                                                };

            if (openFileDialog.ShowDialog() == true)
            {
                this.SetNewTemplateDocument(openFileDialog.FileName);
            }
        }

        private void AnimateStatusBarText(string text)
        {
            _statusBarText.Text = text;
            ((System.Windows.Media.Animation.Storyboard)FindResource("Storyboard1")).Begin();
        }

        private void OnTemplateTreeSet(object sender, EventArgs e)
        {
            Component.ResetAimTemplateTree();
            InitializeTemplateControl();

            _buttonCreateAnnotation.IsEnabled = Component.CreateAnnotationEnabled;
            _btnExtension1.IsEnabled = Component.CreateAnnotationEnabled;
            _buttonResetAnnotation.IsEnabled = Component.ResetButtonEnabled;
        }

        private void ButtonResetAnnotationClick(object sender, RoutedEventArgs e)
        {
            Component.ResetAimTemplateTree();
            AnimateStatusBarText("Template Reset");
        }


        private void ButtonCreateAnnotationClick(object sender, RoutedEventArgs e)
        {
            Component.CreateAnnotationFromTemplateTree();
        }

        private void ButtonUserInfoClick(object sender, RoutedEventArgs e)
        {
            var frmUserInfo = new FormUserInfo(
                Component.UserName,
                Component.LoginName,
                Component.RoleInTrial,
                Component.NumberWithinRoleInTrial);

            if (frmUserInfo.ShowDialog() == DialogResult.OK)
            {
                Component.UserName = frmUserInfo.UserName;
                Component.LoginName = frmUserInfo.LoginName;
                Component.RoleInTrial = frmUserInfo.RoleInTrial;
                Component.NumberWithinRoleInTrial = frmUserInfo.NumberWithinRoleInTrial;
            }
        }

        private void InitializeTemplateControl()
        {
            if (TemplateControl != null)
                _gridTemplateControl.Children.Remove(TemplateControl);

            TemplateControl = new TemplateWpfControl(Component, this) { Margin = new Thickness(0, 0, 0, 96) };
            _gridTemplateControl.Children.Add(TemplateControl);
        }

        private void SetNewTemplateDocument(string templateDocumentFileName)
        {
            // templateDocumentFileName == null means use built-in template
            Component.Preview = false;
            Component.SelectedAimTemplateDocument = templateDocumentFileName;

            // Reinitialize templates list after document is updated
            SynchronizationContext.Current.Post(
                delegate
                { InitializeAnnotationTypeCombo(); }
                , null);
        }

        private void InitializeAnnotationTypeCombo()
        {
            _cmbAnnotationType.SelectionChanged -= OnAnnotationTypeSelectedValueChanged;
            _cmbAnnotationType.DataContext = Component.AimTemplateTrees.Keys;
            _cmbAnnotationType.SelectedItem = Component.AnnotationTypeCode;
            _cmbAnnotationType.SelectionChanged += OnAnnotationTypeSelectedValueChanged;
        }

        private void OnAnnotationTypeSelectedValueChanged(object sender, EventArgs e)
        {
            if (_cmbAnnotationType.SelectedItem != null && _cmbAnnotationType.SelectedItem is TemplateTree.StandardCodeSequence)
                Component.AnnotationTypeCode = _cmbAnnotationType.SelectedItem as TemplateTree.StandardCodeSequence;
            //this.ValidateChildren();
        }

        private void ButtonCreateWordReportClick(object sender, RoutedEventArgs e)
        {
            Component.CreateAnnotationFromTemplateTree();
        }

        private void ButtonWhyIsTemplateIncompleteClick(object sender, RoutedEventArgs e)
        {
            var invalidControl = TemplateControl.FindInvalidControl();
            if (invalidControl != null)
            {
                invalidControl.NotifyIfInvalid();
                AnimateStatusBarText("Missing answer for: " + invalidControl.NodeName);
            }
            else
            {
                var missingMarkupControl = TemplateControl.FindControlWithMissingMarkup();
                if (missingMarkupControl != null)
                {
                    string missingMarkupMessage = String.Empty;
                    switch (missingMarkupControl.GeometricShapeWpfControl.GeometricShape.GeometricShape)
                    {

                        case AimTemplateTreeGeometricShapeNode.GeometricShapes.MultiPoint:
                            missingMarkupMessage = "line or protractor/angle";
                            break;
                        case AimTemplateTreeGeometricShapeNode.GeometricShapes.Polyline:
                            missingMarkupMessage = "rectangle or polygon";
                            break;
                        case AimTemplateTreeGeometricShapeNode.GeometricShapes.Circle:
                            missingMarkupMessage = "ellipse";
                            break;
                        case AimTemplateTreeGeometricShapeNode.GeometricShapes.Ellipse:
                            missingMarkupMessage = "ellipse";
                            break;
                        case AimTemplateTreeGeometricShapeNode.GeometricShapes.Point:
                            missingMarkupMessage = "point callout or crosshair";
                            break;
                    }

                    missingMarkupControl.GeometricShapeWpfControl.Valid = false;
                    missingMarkupControl.GeometricShapeWpfControl.NotifyIfInvalid();
                    if (missingMarkupControl.MarkupCount == 1)
                        AnimateStatusBarText("Missing " + missingMarkupMessage + " markup");
                    else
                        AnimateStatusBarText("Missing " + missingMarkupControl.MarkupCount + " " + missingMarkupMessage + " markups");
                }
                else if (Annotation.Configuration.AimSettings.Default.RequireMarkupInAnnotation && 
                    Component.AimTemplateTree.Markup.Count == 0)
                {
                    AnimateStatusBarText("Missing graphic markup on image.");
                }
            }
        }
    }
}
