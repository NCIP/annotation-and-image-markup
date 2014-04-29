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
using System.IO;
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Configuration;

namespace Segmentation.Configuration
{
    [ExtensionPoint]
    public sealed class SegmentationConfigurationComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
    {
    }

    /// <summary>
    /// SegmentationConfigurationComponent class.
    /// </summary>
    [AssociateView(typeof (SegmentationConfigurationComponentViewExtensionPoint))]
    public class SegmentationConfigurationComponent : ConfigurationApplicationComponent
    {
        public static readonly string Path = "Segmentation";
        private string _anatomicRegionModifierConfigurationFileLocation;
        private string _categoryTypeModifierConfigurationFileLocation;

        private SegmentationSettings _settings;
        private bool _showSegmentationCreationDialog;


        public bool ShowSegmentationCreationDialog
        {
            get { return _showSegmentationCreationDialog; }
            set
            {
                if (_showSegmentationCreationDialog != value)
                {
                    _showSegmentationCreationDialog = value;
                    Modified = true;
                    NotifyPropertyChanged("ShowSegmentationCreationDialog");
                }
            }
        }

        public string CategoryTypeModifierConfigurationFileLocation
        {
            get { return _categoryTypeModifierConfigurationFileLocation; }
            set
            {
                if (_categoryTypeModifierConfigurationFileLocation != value)
                {
                    _categoryTypeModifierConfigurationFileLocation = value;
                    Modified = true;
                    NotifyPropertyChanged("CategoryTypeModifierConfigurationFileLocation");
                }
            }
        }

        public string AnatomicRegionModifierConfigurationFileLocation
        {
            get { return _anatomicRegionModifierConfigurationFileLocation; }
            set
            {
                if (_anatomicRegionModifierConfigurationFileLocation != value)
                {
                    _anatomicRegionModifierConfigurationFileLocation = value;
                    Modified = true;
                    NotifyPropertyChanged("AnatomicRegionModifierConfigurationFileLocation");
                }
            }
        }

        public override void Start()
        {
            base.Start();

            _settings = SegmentationSettings.Default;
            _showSegmentationCreationDialog = _settings.ShowSegmentationCreationDialog;
            _categoryTypeModifierConfigurationFileLocation = _settings.CategoryTypeModifierConfigurationFileLocation;
            _anatomicRegionModifierConfigurationFileLocation = _settings.AnatomicRegionModifierConfigurationFileLocation;
        }

        /// <summary>
        /// Called by the host when the application component is being terminated.
        /// </summary>
        public override void Stop()
        {
            _settings = null;

            base.Stop();
        }

        public override void Save()
        {
            _settings.ShowSegmentationCreationDialog = _showSegmentationCreationDialog;
            _settings.CategoryTypeModifierConfigurationFileLocation = _categoryTypeModifierConfigurationFileLocation;
            _settings.AnatomicRegionModifierConfigurationFileLocation = _anatomicRegionModifierConfigurationFileLocation;
            _settings.Save();
        }

        public bool ExportDefaultConfigurationFiles(string pathName)
        {
            try
            {
                if (!String.IsNullOrEmpty(pathName) && Directory.Exists(pathName))
                {
                    File.WriteAllText(System.IO.Path.Combine(pathName, "AnatomicRegionAndModifier.xml"),
                        Resources.AnatomicRegionAndModifierXml);
                    File.WriteAllText(System.IO.Path.Combine(pathName, "AnatomicRegionAndModifier.xsd"),
                        Resources.AnatomicRegionAndModifierXsd);
                    File.WriteAllText(System.IO.Path.Combine(pathName, "SegmentationCategoryTypeModifier.xml"),
                        Resources.SegmentationCategoryTypeModifierXml);
                    File.WriteAllText(System.IO.Path.Combine(pathName, "SegmentationCategoryTypeModifier.xsd"),
                        Resources.SegmentationCategoryTypeModifierXsd);
                    return true;
                }
            }
            catch (Exception exception)
            {
                Platform.Log(LogLevel.Error, exception, "Error writing default segmentation configuration XML to disk location [{0}].", pathName);
            }
            return false;
        }

        public string GetDefaultXmlFilesPath()
        {
            string segDocumentsPath = System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "AIM Segmentation");
            if (HasWriteAccessToPath(segDocumentsPath))
            {
                if (!Directory.Exists(segDocumentsPath))
                {
                    Directory.CreateDirectory(segDocumentsPath);
                }
                return segDocumentsPath;
            }
            return null;
        }

        private bool HasWriteAccessToPath(string path)
        {
            try
            {
                Directory.GetAccessControl(path);
                return true;
            }
            catch (UnauthorizedAccessException)
            {
                return false;
            }
        }
    }
}
