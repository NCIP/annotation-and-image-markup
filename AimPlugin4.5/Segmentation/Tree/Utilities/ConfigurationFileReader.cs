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
using System.IO;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using ClearCanvas.Common;
using Segmentation.Configuration;

namespace Segmentation.Tree.Utilities
{
    public class ConfigurationFileReader
    {
        public List<Category> ReadConfigurationFile()
        {
            var categories = new List<Category>();
            var anatomicRegions = new List<AnatomicRegion>();

            var categoryFile = SegmentationSettings.Default.CategoryTypeModifierConfigurationFileLocation;

            var isRead = false;
            if (!string.IsNullOrEmpty(categoryFile) && File.Exists(categoryFile))
            {
                try
                {
                    using (var fs = new FileStream(categoryFile, FileMode.Open))
                    {
                        var xmlSerializer = new XmlSerializer(typeof (SegmentationCodes));
                        var segmentationCodes = (SegmentationCodes) xmlSerializer.Deserialize(fs);

                        if (segmentationCodes != null && segmentationCodes.Category != null)
                        {
                            categories.AddRange(from xsdCategory in segmentationCodes.Category
                                                where xsdCategory != null
                                                select XsdCategoryToCategory(xsdCategory));
                        }
                        isRead = true;
                    }
                }
                catch (Exception ex)
                {
                    Platform.Log(LogLevel.Error, "Failed to read segmentation categories XML file [{0}]. Will use built-in categories. Error: {1}",
                                 categoryFile, ex.Message);
                }
            }
            if (!isRead)
            {
                byte[] byteArray = Encoding.UTF8.GetBytes(Resources.SegmentationCategoryTypeModifierXml);
                using (var ms = new MemoryStream(byteArray))
                {
                    var xmlSerializer = new XmlSerializer(typeof(SegmentationCodes));
                    var segmentationCodes = (SegmentationCodes)xmlSerializer.Deserialize(ms);

                    if (segmentationCodes != null && segmentationCodes.Category != null)
                    {
                        categories.AddRange(from xsdCategory in segmentationCodes.Category
                                            where xsdCategory != null
                                            select XsdCategoryToCategory(xsdCategory));
                    }
                }
            }

            var anatomicRegionFile = SegmentationSettings.Default.AnatomicRegionModifierConfigurationFileLocation;

            isRead = false;
            if (!string.IsNullOrEmpty(anatomicRegionFile) && File.Exists(anatomicRegionFile))
            {
                try
                {
                    using (var fs = new FileStream(anatomicRegionFile, FileMode.Open))
                    {
                        var xmlSerializer = new XmlSerializer(typeof (AnatomicCodes));
                        var anatomicCodes = (AnatomicCodes) xmlSerializer.Deserialize(fs);

                        if (anatomicCodes != null && anatomicCodes.AnatomicRegion != null)
                        {
                            anatomicRegions.AddRange(from xsdAnatomicRegion in anatomicCodes.AnatomicRegion
                                                     where xsdAnatomicRegion != null
                                                     select XsdAnatomicRegionToAnatomicRegion(xsdAnatomicRegion));

                            foreach (var category in categories.Where(cat => cat.AnatomicRegionRequired))
                            {
                                category.AnatomicRegions.AddRange(anatomicRegions);
                            }
                        }
                        isRead = true;
                    }
                }
                catch (Exception ex)
                {
                    Platform.Log(LogLevel.Error,
                                 "Failed to read segmentation anatomic region modifiers XML file [{0}]. Will use built-in anatomic region modifiers. Error: {1}",
                                 anatomicRegionFile, ex.Message);
                }
            }
            if (!isRead)
            {
                byte[] byteArray = Encoding.UTF8.GetBytes(Resources.AnatomicRegionAndModifierXml);
                using (var ms = new MemoryStream(byteArray))
                {
                    var xmlSerializer = new XmlSerializer(typeof(AnatomicCodes));
                    var anatomicCodes = (AnatomicCodes)xmlSerializer.Deserialize(ms);

                    if (anatomicCodes != null && anatomicCodes.AnatomicRegion != null)
                    {
                        anatomicRegions.AddRange(from xsdAnatomicRegion in anatomicCodes.AnatomicRegion
                                                 where xsdAnatomicRegion != null
                                                 select XsdAnatomicRegionToAnatomicRegion(xsdAnatomicRegion));

                        foreach (var category in categories.Where(cat => cat.AnatomicRegionRequired))
                        {
                            category.AnatomicRegions.AddRange(anatomicRegions);
                        }
                    }
                }
            }

            categories.Sort((code1, code2) => code1.CodeMeaning.CompareTo(code2.CodeMeaning));
            foreach (var category in categories)
            {
                if (category.Types != null)
                {
                    category.Types.Sort((code1, code2) => code1.CodeMeaning.CompareTo(code2.CodeMeaning));
                    foreach (var type in category.Types)
                    {
                        if (type.TypeModifiers != null)
                        {
                            type.TypeModifiers.Sort((code1, code2) => code1.CodeMeaning.CompareTo(code2.CodeMeaning));
                        }
                    } 
                }
                if (category.AnatomicRegions != null)
                {
                    category.AnatomicRegions.Sort((code1, code2) => code1.CodeMeaning.CompareTo(code2.CodeMeaning));
                    foreach (var anatomicRegion in category.AnatomicRegions)
                    {
                        if (anatomicRegion.AnatomicRegionModifiers != null)
                        {
                            anatomicRegion.AnatomicRegionModifiers.Sort((code1, code2) => code1.CodeMeaning.CompareTo(code2.CodeMeaning));
                        }
                    }
                }
            }
            return categories;
        }

        private AnatomicRegion XsdAnatomicRegionToAnatomicRegion(AnatomicCodesAnatomicRegion xsdAnatomicRegion)
        {
            var anatomicRegion = new AnatomicRegion()
            {
                CodeMeaning = xsdAnatomicRegion.codeMeaning,
                CodeValue = xsdAnatomicRegion.codeValue,
                CodingSchemeDesignator = xsdAnatomicRegion.codingScheme
            };

            if (xsdAnatomicRegion.Modifier != null)
            {
                foreach (var xsdModifier in xsdAnatomicRegion.Modifier)
                {
                    if (xsdModifier != null)
                    {
                        AnatomicRegionModifier modifier = XsdAnatomicRegionModifierToAnatomicRegionModifier(xsdModifier);
                        anatomicRegion.AnatomicRegionModifiers.Add(modifier);
                    }
                }
            }
            return anatomicRegion;
        }

        private AnatomicRegionModifier XsdAnatomicRegionModifierToAnatomicRegionModifier(AnatomicCodesAnatomicRegionModifier xsdModifier)
        {
            var modifier = new AnatomicRegionModifier
            {
                CodeMeaning = xsdModifier.codeMeaning,
                CodeValue = xsdModifier.codeValue,
                CodingSchemeDesignator = xsdModifier.codingScheme
            };

            return modifier;
        }

        public Category XsdCategoryToCategory(SegmentationCodesCategory xsdCategory)
        {
            var category = new Category
                               {
                                   CodeMeaning = xsdCategory.codeMeaning,
                                   CodeValue = xsdCategory.codeValue,
                                   CodingSchemeDesignator = xsdCategory.codingScheme,
                                   AnatomicRegionRequired = xsdCategory.showAnatomy
                               };

            if (xsdCategory.Type != null)
            {
                foreach (SegmentationCodesCategoryType xsdType in xsdCategory.Type)
                {
                    if (xsdType != null)
                    {
                        Type type = XsdTypeToType(xsdType);
                        category.Types.Add(type);
                    }
                }
            }

            return category;
        }

        public Type XsdTypeToType(SegmentationCodesCategoryType xsdType)
        {
            var type = new Type
                           {
                               CodeMeaning = xsdType.codeMeaning,
                               CodeValue = xsdType.codeValue,
                               CodingSchemeDesignator = xsdType.codingScheme
                           };

            if (xsdType.Modifier != null)
            {
                foreach (SegmentationCodesCategoryTypeModifier xsdModifier in xsdType.Modifier)
                {
                    if (xsdModifier != null)
                    {
                        TypeModifier typeModifier = XsdTypeModifierToTypeModifier(xsdModifier);
                        type.TypeModifiers.Add(typeModifier);
                    }
                }
            }

            return type;
        }

        public TypeModifier XsdTypeModifierToTypeModifier(SegmentationCodesCategoryTypeModifier xsdTypeModifier)
        {
            var typeModifier = new TypeModifier
                                   {
                                       CodeMeaning = xsdTypeModifier.codeMeaning,
                                       CodeValue = xsdTypeModifier.codeValue,
                                       CodingSchemeDesignator = xsdTypeModifier.codingScheme
                                   };

            return typeModifier;
        }
    }
}