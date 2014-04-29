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
using System.Xml;
using System.Runtime.Serialization;
using System.Xml.Serialization;

namespace AIM.Annotation.TemplateTree.Utilities
{
    public class AimTemplateTreeSerializer
    {
        private static string _namespaceString =
            "{gme://caCORE.caCORE/3.2/edu.northwestern.radiology.AIMTemplate}";

        private Dictionary<StandardCodeSequence, AimTemplateTree> AimTemplateTreeFromXsdTemplate(TemplateContainer container)
        {
            var templates = new Dictionary<StandardCodeSequence, AimTemplateTree>();

            if (container.Template != null && container.Template.Any())
                foreach (var template in container.Template)
                {
                    var aimTemplateTree = new AimTemplateTree();

                    if (template.creationDateSpecified)
                        aimTemplateTree.CreationDate = template.creationDate;

                    aimTemplateTree.TemplateName = template.name;
                    aimTemplateTree.TemplateDescription = template.description;
                    aimTemplateTree.TemplateAuthors = template.authors;
                    aimTemplateTree.SelectedTemplateUid = template.uid;
                    aimTemplateTree.SelectedTemplateContainerUid = container.uid;

                    foreach (TemplateComponent templateComponent in template.Component)
                    {
                        var node = AimTemplateTreeNodeFromXsdComponent(templateComponent);
                        if (node != null)
                            aimTemplateTree.TemplateNodes.Add(node);
                    }

                    StandardCodeSequence codeSequence;

                    var sequenceNumber = String.Empty;
                    int sequence = 0;

                    do
                    {
                        codeSequence = new StandardCodeSequence(
                            template.codeValue + sequenceNumber,
                            template.codeMeaning,
                            template.codingSchemeDesignator,
                            template.codingSchemeVersion);
                        sequenceNumber = sequence.ToString();
                        sequence++;

                    } while (templates.ContainsKey(codeSequence));

                    aimTemplateTree.StandardCodeSequence = codeSequence;
                    templates.Add(codeSequence, aimTemplateTree);
                }
            else
            {
                throw new Exception("Template container invalid or contained no templates.");
            }

            return templates;
        }

        private AimTemplateTreeNode AimTemplateTreeNodeFromXsdComponent(TemplateComponent component)
        {
            AimTemplateTreeNode node = null;

            var allowedTerms = new List<AimTemplateTreeAllowedTerm>();

            if (component.Items != null)
            {
                foreach (object item in component.Items)
                {
                    if (item.GetType() == typeof(TemplateComponentAnatomicEntity))
                    {
                        node = AimTemplateTreeAnatomicEntityNodeFromXsdAnatomicEntity(component, (TemplateComponentAnatomicEntity)item);
                    }

                    if (item.GetType() == typeof(TemplateComponentImagingObservation))
                    {
                        node = AimTemplateTreeImagingObservationNodeFromXsdImagingObservation(component, (TemplateComponentImagingObservation)item);
                    }

                    if (item.GetType() == typeof(TemplateComponentInference))
                    {
                        node = AimTemplateTreeInferenceNodeFromXsdInference(component, (TemplateComponentInference)item);
                    }

                    if (item.GetType() == typeof(TemplateComponentGeometricShape))
                    {
                        node = AimTemplateTreeGeometricShapeNodeFromXsdGeometricShape(component,
                                                                                 (TemplateComponentGeometricShape)item);
                    }

                    if (item.GetType() == typeof(TemplateComponentCalculation))
                    {
                        node = AimTemplateTreeCalculationNodeFromXsdCalculation(component,
                                                                              (TemplateComponentCalculation)item);
                    }

                    if (item.GetType() == typeof(TemplateComponentAllowedTerm))
                    {
                        //AllowedTerm term = AllowedTermFromXsdAllowedTerm((TemplateComponentAllowedTerm)item);
                        //allowedTerms.Add(term);
                    }

                }
            }

            return node;
        }

        private AimTemplateTreeAllowedTerm AllowedTermFromXsdAllowedTerm(TemplateComponentAllowedTerm allowedTerm)
        {
            var standardValidTerms = new List<StandardValidTerm>();

            if (allowedTerm.ValidTerm1 != null)
            {
                foreach (var childValidTerm in allowedTerm.ValidTerm1)
                {
                    var childTerm = ValidTermFromXsdValidTerm(childValidTerm);
                    if (childTerm != null)
                        standardValidTerms.Add(childTerm);
                }
            }

            var term = new AimTemplateTreeAllowedTerm(new StandardCodeSequence(
                                                             allowedTerm.codeValue,
                                                             allowedTerm.codeMeaning,
                                                             allowedTerm.codingSchemeDesignator,
                                                             allowedTerm.codingSchemeVersion),
                                                             allowedTerm.defaultAnswer,
                                                             allowedTerm.nextId,
                                                             allowedTerm.noMoreQuestions,
                                                             standardValidTerms);

            return term;
        }

        private AimTemplateTreeAllowedTerm AllowedTermFromXsdAllowedTerm(ComponentCharacteristicAllowedTerm allowedTerm)
        {
            var standardValidTerms = new List<StandardValidTerm>();

            if (allowedTerm.ValidTerm1 != null)
            {
                foreach (var childValidTerm in allowedTerm.ValidTerm1)
                {
                    var childTerm = ValidTermFromXsdValidTerm(childValidTerm);
                    if (childTerm != null)
                        standardValidTerms.Add(childTerm);
                }
            }

            var term = new AimTemplateTreeAllowedTerm(new StandardCodeSequence(
                                                             allowedTerm.codeValue,
                                                             allowedTerm.codeMeaning,
                                                             allowedTerm.codingSchemeDesignator,
                                                             allowedTerm.codingSchemeVersion),
                                                             allowedTerm.defaultAnswer,
                                                             allowedTerm.nextId,
                                                             allowedTerm.noMoreQuestions,
                                                             standardValidTerms);


            if (allowedTerm.ValidTerm1 != null)
            {
                foreach (var childValidTerm in allowedTerm.ValidTerm1)
                {
                    var childTerm = ValidTermFromXsdValidTerm(childValidTerm);
                    if (childTerm != null)
                        term.StandardValidTerms.Add(childTerm);
                }
            }

            return term;
        }

        private StandardCodedTerm StandardCodedTermFomXsdNonQuantifiable(ComponentCharacteristicAllowedTermCharacteristicQuantificationNonQuantifiable nonQuantifiable)
        {
            return new StandardCodedTerm(
                nonQuantifiable.defaultAnswer,
                nonQuantifiable.nextId,
                nonQuantifiable.noMoreQuestions,
                nonQuantifiable.codeValue,
                nonQuantifiable.codeMeaning,
                nonQuantifiable.codingSchemeDesignator,
                nonQuantifiable.codingSchemeVersion);
        }

        private CharacteristicQuantificationAllowedTerm CharacteristicQuantificationAllowedTermFromXsdAllowedTerm(ComponentCharacteristicAllowedTerm allowedTerm)
        {
            var nonQuantifiables = new List<StandardCodedTerm>();

            //if (allowedTerm.CharacteristicQuantification != null && allowedTerm.CharacteristicQuantification.NonQuantifiable != null)
            //{
            //    nonQuantifiables.AddRange(allowedTerm.CharacteristicQuantification.NonQuantifiable.Select(
            //    nonQuantifiable => StandardCodedTermFomXsdNonQuantifiable(nonQuantifiable)).ToList());
            //}

            var standardValidTerms = new List<StandardValidTerm>();

            if (allowedTerm.ValidTerm1 != null)
            {
                foreach (var childValidTerm in allowedTerm.ValidTerm1)
                {
                    var childTerm = ValidTermFromXsdValidTerm(childValidTerm);
                    if (childTerm != null)
                        standardValidTerms.Add(childTerm);
                }
            }

            string name = String.Empty;
            bool hasConfidence = false;

            var quantifications = new List<AimTemplateTreeCharacteristicQuantification>();

            if (allowedTerm.CharacteristicQuantification != null)
            {
                foreach (var quantification in allowedTerm.CharacteristicQuantification)
                    quantifications.Add(CharacteristicQuantificationFromXsdCharacteristicQuantification(quantification));
            }

            return new CharacteristicQuantificationAllowedTerm(
                quantifications,
                new StandardCodeSequence(
                    allowedTerm.codeValue,
                    allowedTerm.codeMeaning,
                    allowedTerm.codingSchemeDesignator,
                    allowedTerm.codingSchemeVersion),
                    allowedTerm.defaultAnswer,
                    allowedTerm.nextId,
                    allowedTerm.noMoreQuestions,
                    standardValidTerms);
        }

        private AimTemplateTreeCharacteristicQuantification CharacteristicQuantificationFromXsdCharacteristicQuantification(
            ComponentCharacteristicAllowedTermCharacteristicQuantification characteristicQuantification)
        {
            var intervals = new List<TemplateTree.Interval>();
            var numericals = new List<TemplateTree.Numerical>();
            var scales = new List<TemplateTree.Scale>();
            var quantiles = new List<TemplateTree.Quantile>();

            AimTemplateTreeCharacteristicQuantification quantification = null;
            var nonQuantifiables = new List<StandardCodedTerm>();

            string name = characteristicQuantification.name;
            bool annotatorConfidence = characteristicQuantification.annotatorConfidence;
            int index = 0;
            int.TryParse(characteristicQuantification.characteristicQuantificationIndex, out index);

            if (characteristicQuantification.NonQuantifiable != null)
            {
                nonQuantifiables.AddRange(characteristicQuantification.NonQuantifiable.Select(nonQuantifiable => StandardCodedTermFomXsdNonQuantifiable(nonQuantifiable)));
            }
            if (characteristicQuantification.Items != null)
            {
                foreach (var quantificationItem in characteristicQuantification.Items)
                {
                    if (quantificationItem is Interval)
                    {
                        intervals.Add(AimTemplateTreeIntervalFromXsdInterval((Interval)quantificationItem));
                    }
                    if (quantificationItem is Scale)
                    {
                        scales.Add(AimTemplateTreeScaleFromXsdScale((Scale)quantificationItem));
                    }
                    if (quantificationItem is Quantile)
                    {
                        quantiles.Add(AimTemplateTreeQuantileFromXsdQuantile((Quantile)quantificationItem));
                    }
                    if (quantificationItem is Numerical)
                    {
                        numericals.Add(AimTemplateTreeNumericalFromXsdNumerical((Numerical)quantificationItem));
                    }
                }
            }

            if (quantiles.Count > 0)
                quantification = new AimTemplateTreeQuantileQuantification(
                    quantiles[0],
                    name,
                    annotatorConfidence,
                    index,
                    nonQuantifiables);
            if (intervals.Count > 0)
                quantification = new AimTemplateTreeIntervalQuantification(
                    intervals,
                    name,
                    annotatorConfidence,
                    index,
                    nonQuantifiables);
            else if (numericals.Count > 0)
                quantification = new AimTemplateTreeNumericalQuantification(
                    numericals,
                    name,
                    annotatorConfidence,
                    index,
                    nonQuantifiables);
            else if (scales.Count > 0)
                quantification = new AimTemplateTreeScaleQuantification(
                    scales[0],
                    name,
                    annotatorConfidence,
                    index,
                    nonQuantifiables);
            else if (quantification == null)
                quantification = new AimTemplateTreeCharacteristicQuantification(
                    name,
                    annotatorConfidence,
                    index,
                    nonQuantifiables);
            return quantification;
        }

        private TemplateTree.Quantile AimTemplateTreeQuantileFromXsdQuantile(Quantile quantile)
        {
            int bins = 0;
            int.TryParse(quantile.bins, out bins);

            int defaultBin = 0;
            int.TryParse(quantile.defaultBin, out defaultBin);

            return new TemplateTree.Quantile
                       {
                           Bins = bins,
                           DefaultBin = defaultBin,
                           DefaultAnswer = false,
                           MaxValue = quantile.maxValue,
                           MinValue = quantile.minValue,
                           ValueLabel = quantile.valueLabel
                       };
        }

        private TemplateTree.Numerical AimTemplateTreeNumericalFromXsdNumerical(Numerical numerical)
        {
            return new TemplateTree.Numerical
                       {
                           Value = numerical.value,
                           Operator = (ComparisonOperator)numerical.@operator,
                           UcumString = numerical.ucumString,
                           OperatorSpecified = numerical.operatorSpecified,
                           DefaultAnswer = numerical.defaultAnswer,
                           NextId = numerical.nextId,
                           NoMoreQuestions = numerical.noMoreQuestions
                       };
        }

        private TemplateTree.Interval AimTemplateTreeIntervalFromXsdInterval(Interval interval)
        {
            return new TemplateTree.Interval
                       {
                           MaxOperator = (ComparisonOperator)interval.maxOperator,
                           MinOperator = (ComparisonOperator)interval.minOperator,
                           MaxValue = interval.maxValue,
                           MinValue = interval.minValue,
                           UcumString = interval.ucumString,
                           DefaultAnswer = interval.defaultAnswer,
                           NoMoreQuestions = interval.noMoreQuestions,
                           NextId = interval.nextId
                       };
        }

        private TemplateTree.ScaleLevel AimTemplateTreeScaleLevelFromXsdScaleLevel(ScaleScaleLevel scaleLevel)
        {
            return new TemplateTree.ScaleLevel
                       {
                           Value = scaleLevel.value,
                           ValueDescription = scaleLevel.valueDescription,
                           ValueLabel = scaleLevel.valueLabel,
                           NoMoreQuestions = scaleLevel.noMoreQuestions,
                           DefaultAnswer = scaleLevel.defaultAnswer,
                           NextId = scaleLevel.nextId
                       };
        }

        private TemplateTree.Scale AimTemplateTreeScaleFromXsdScale(Scale scale)
        {
            var scaleLevels = scale.ScaleLevel.Select(scaleLevel =>
                AimTemplateTreeScaleLevelFromXsdScaleLevel(scaleLevel)).ToList();

            return new TemplateTree.Scale
                       {
                           ScaleLevels = scaleLevels,
                           ScaleType = (TemplateTree.ScaleType)scale.scaleType
                       };
        }

        private StandardValidTerm ValidTermFromXsdValidTerm(ValidTerm validTerm)
        {
            if (validTerm == null)
                return null;

            var validTerms = new List<StandardValidTerm>();
            if (validTerm.ValidTerm1 != null)
            {
                foreach (var childValidTerm in validTerm.ValidTerm1)
                {
                    var childTerm = ValidTermFromXsdValidTerm(childValidTerm);
                    if (childTerm != null)
                        validTerms.Add(childTerm);
                }
            }

            var term = new StandardValidTerm(new StandardCodeSequence(
                                                 validTerm.codeValue,
                                                 validTerm.codeMeaning,
                                                 validTerm.codingSchemeDesignator,
                                                 validTerm.codingSchemeVersion),
                                                 validTerms);



            return term;
        }

        private AimTemplateTreeAnatomicEntityNode AimTemplateTreeAnatomicEntityNodeFromXsdAnatomicEntity(TemplateComponent component, TemplateComponentAnatomicEntity anatomicEntity)
        {
            var allowedTerms = new List<AimTemplateTreeAllowedTerm>();
            for (int index = 0; index < component.Items.Length; index++)
            {
                object item = component.Items[index];
                if (item.GetType() == typeof(TemplateComponentAllowedTerm))
                {
                    var term = AllowedTermFromXsdAllowedTerm((TemplateComponentAllowedTerm)item);
                    if (term != null)
                    {
                        term.PresentationIndex = index;
                        allowedTerms.Add(term);
                    }
                }
            }

            var anatomicEntityCharacteristics = new List<AimTemplateTreeAnatomicEntityCharacteristicNode>();
            if (anatomicEntity.AnatomicEntityCharacteristic != null)
            {
                anatomicEntityCharacteristics.AddRange(anatomicEntity.AnatomicEntityCharacteristic.Select(
                anatomicEntityCharacteristic => AimTemplateTreeAnatomicEntityCharacteristicNodeFromXsdAnatomicEntityCharacteristic(anatomicEntityCharacteristic)).ToList());
            }

            var imagingObservationCharacteristics = new List<AimTemplateTreeImagingObservationCharacteristicNode>();
            if (anatomicEntity.ImagingObservationCharacteristic != null)
            {
                imagingObservationCharacteristics.AddRange(anatomicEntity.ImagingObservationCharacteristic.Select(
                imagingObservationCharacteristic => AimTemplateTreeImagingObservationCharacteristicNodeFromXsdImagingObservationCharacteristic(imagingObservationCharacteristic)).ToList());
            }

            int itemNumber;
            int.TryParse(component.itemNumber, out itemNumber);

            int minCardinality;
            int.TryParse(component.minCardinality, out minCardinality);

            int maxCardinality;
            int.TryParse(component.maxCardinality, out maxCardinality);

            string label = component.label;
            if (component.QuestionType != null)
                label = component.QuestionType.codeMeaning;

            var node = new AimTemplateTreeAnatomicEntityNode(
                label,
                itemNumber,
                component.explanatoryText,
                minCardinality,
                maxCardinality,
                component.shouldDisplay,
                component.groupLabel,
                ValidTermFromXsdValidTerm(component.QuestionType),
                anatomicEntity.annotatorConfidence,
                allowedTerms,
                anatomicEntityCharacteristics,
                imagingObservationCharacteristics,
                component.id
                );
            return node;
        }

        private AimTemplateTreeImagingObservationNode AimTemplateTreeImagingObservationNodeFromXsdImagingObservation(TemplateComponent component, TemplateComponentImagingObservation imagingObservation)
        {
            var allowedTerms = new List<AimTemplateTreeAllowedTerm>();
            for (int index = 0; index < component.Items.Length; index++)
            {
                object item = component.Items[index];
                if (item.GetType() == typeof(TemplateComponentAllowedTerm))
                {
                    var term = AllowedTermFromXsdAllowedTerm((TemplateComponentAllowedTerm)item);
                    if (term != null)
                    {
                        term.PresentationIndex = index;
                        allowedTerms.Add(term);
                    }
                }
            }

            var imagingObservationCharacteristics = new List<AimTemplateTreeImagingObservationCharacteristicNode>();
            if (imagingObservation.ImagingObservationCharacteristic != null)
            {
                imagingObservationCharacteristics.AddRange(imagingObservation.ImagingObservationCharacteristic.Select(
                anatomicEntityCharacteristic => AimTemplateTreeImagingObservationCharacteristicNodeFromXsdImagingObservationCharacteristic(anatomicEntityCharacteristic)).ToList());
            }

            int itemNumber;
            int.TryParse(component.itemNumber, out itemNumber);

            int minCardinality;
            int.TryParse(component.minCardinality, out minCardinality);

            int maxCardinality;
            int.TryParse(component.maxCardinality, out maxCardinality);

            string label = component.label;
            if (component.QuestionType != null)
                label = component.QuestionType.codeMeaning;

            var node = new AimTemplateTreeImagingObservationNode(
                label,
                itemNumber,
                component.explanatoryText,
                minCardinality,
                maxCardinality,
                component.shouldDisplay,
                component.groupLabel,
                ValidTermFromXsdValidTerm(component.QuestionType),
                imagingObservation.annotatorConfidence,
                allowedTerms,
                imagingObservationCharacteristics,
                component.id
                );
            return node;
        }

        private AimTemplateTreeInferenceNode AimTemplateTreeInferenceNodeFromXsdInference(TemplateComponent component, TemplateComponentInference inference)
        {
            var allowedTerms = new List<AimTemplateTreeAllowedTerm>();
            for (int index = 0; index < component.Items.Length; index++)
            {
                object item = component.Items[index];
                if (item.GetType() == typeof(TemplateComponentAllowedTerm))
                {
                    var term = AllowedTermFromXsdAllowedTerm((TemplateComponentAllowedTerm)item);
                    if (term != null)
                    {
                        term.PresentationIndex = index;
                        allowedTerms.Add(term);
                    }
                }
            }

            int itemNumber;
            int.TryParse(component.itemNumber, out itemNumber);

            int minCardinality;
            int.TryParse(component.minCardinality, out minCardinality);

            int maxCardinality;
            int.TryParse(component.maxCardinality, out maxCardinality);

            string label = component.label;
            if (component.QuestionType != null)
                label = component.QuestionType.codeMeaning;

            var node = new AimTemplateTreeInferenceNode(
                label,
                itemNumber,
                component.explanatoryText,
                minCardinality,
                maxCardinality,
                component.shouldDisplay,
                component.groupLabel,
                ValidTermFromXsdValidTerm(component.QuestionType),
                inference.annotatorConfidence,
                allowedTerms,
                component.id
                );
            return node;
        }

        private AimTemplateTreeGeometricShapeNode AimTemplateTreeGeometricShapeNodeFromXsdGeometricShape(TemplateComponent component, TemplateComponentGeometricShape geometricShape)
        {
            int itemNumber;
            int.TryParse(component.itemNumber, out itemNumber);

            int minCardinality;
            int.TryParse(component.minCardinality, out minCardinality);

            int maxCardinality;
            int.TryParse(component.maxCardinality, out maxCardinality);

            string label = component.label;
            if (component.QuestionType != null)
                label = component.QuestionType.codeMeaning;

            var node = new AimTemplateTreeGeometricShapeNode(
                label,
                itemNumber,
                component.explanatoryText,
                minCardinality,
                maxCardinality,
                component.shouldDisplay,
                component.groupLabel,
                ValidTermFromXsdValidTerm(component.QuestionType),
                geometricShape.noMoreQuestions,
                geometricShape.nextId,
                component.id,
                GeometricShapesFromXsdGeometricShapeValue(geometricShape.Value)
                );
            return node;
        }

        private AimTemplateTreeGeometricShapeNode.GeometricShapes GeometricShapesFromXsdGeometricShapeValue(GeometricShape geometricShapeValue)
        {
            var geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Point;

            switch (geometricShapeValue)
            {
                case GeometricShape.Point:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Point;
                    break;
                case GeometricShape.Polyline:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Polyline;
                    break;
                case GeometricShape.MultiPoint:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.MultiPoint;
                    break;
                case GeometricShape.Circle:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Circle;
                    break;
                case GeometricShape.Ellipse:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Ellipse;
                    break;
                case GeometricShape.Item3DPoint:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Point3D;
                    break;
                case GeometricShape.Item3DPolygon:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Polygon3D;
                    break;
                case GeometricShape.Item3DPolyline:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Polyline3D;
                    break;
                case GeometricShape.Item3DEllipse:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Ellipse3D;
                    break;
                case GeometricShape.Item3DEllipsoid:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.Ellipsoid3D;
                    break;
                case GeometricShape.Item3DMultiPoint:
                    geometricShape = AimTemplateTreeGeometricShapeNode.GeometricShapes.MultiPoint3D;
                    break;
            }

            return geometricShape;
        }

        private AimTemplateTreeCalculationNode AimTemplateTreeCalculationNodeFromXsdCalculation(TemplateComponent component, TemplateComponentCalculation calculation)
        {
            int itemNumber;
            int.TryParse(component.itemNumber, out itemNumber);

            var calculationTypes = calculation.CalculationType.Select(calc => AimTemplateTreeCalculationTypeFromXsdCalculationType(calc)).ToList();

            int minCardinality;
            int.TryParse(component.minCardinality, out minCardinality);

            int maxCardinality;
            int.TryParse(component.maxCardinality, out maxCardinality);

            string label = component.label;
            if (component.QuestionType != null)
                label = component.QuestionType.codeMeaning;

            return new AimTemplateTreeCalculationNode(
                label,
                itemNumber,
                component.explanatoryText,
                minCardinality,
                maxCardinality,
                component.shouldDisplay,
                component.groupLabel,
                ValidTermFromXsdValidTerm(component.QuestionType),
                calculation.noMoreQuestions,
                calculation.nextId,
                calculationTypes,
                component.id
                );
        }

        private AimTemplateTreeCalculationType AimTemplateTreeCalculationTypeFromXsdCalculationType(TemplateComponentCalculationCalculationType calculationType)
        {
            var algorithms = new List<AimTemplateTreeAlgorithm>();
                
            if (calculationType.AlgorithmType != null)
                algorithms = calculationType.AlgorithmType.Select(AimTemplateTreeAlgorithmFromXsdAlgorithm).ToList();

            var validTerms = new List<StandardValidTerm>();
            if (calculationType.ValidTerm1 != null)
            {
                foreach (var childValidTerm in calculationType.ValidTerm1)
                {
                    var childTerm = ValidTermFromXsdValidTerm(childValidTerm);
                    if (childTerm != null)
                        validTerms.Add(childTerm);
                }
            }

            var codeSequence = new StandardCodeSequence(
                calculationType.codeValue,
                calculationType.codeMeaning,
                calculationType.codingSchemeDesignator,
                calculationType.codingSchemeVersion);

            return new AimTemplateTreeCalculationType(codeSequence, algorithms, validTerms);
        }

        private AimTemplateTreeAlgorithm AimTemplateTreeAlgorithmFromXsdAlgorithm(TemplateComponentCalculationCalculationTypeAlgorithmType algorithmType)
        {
            var algorithms = new List<AimTemplateTreeAlgorithm>();

            return new AimTemplateTreeAlgorithm(
                new StandardCodeSequence(algorithmType.codeValue, algorithmType.codeMeaning,
                                         algorithmType.codingSchemeDesignator, algorithmType.codingSchemeVersion),
                algorithms,
                algorithmType.description,
                algorithmType.uniqueIdentifier,
                algorithmType.algorithmName,
                algorithmType.algorithmVersion,
                algorithmType.mathML);
        }

        private AimTemplateTreeAnatomicEntityCharacteristicNode AimTemplateTreeAnatomicEntityCharacteristicNodeFromXsdAnatomicEntityCharacteristic(TemplateComponentAnatomicEntityAnatomicEntityCharacteristic anatomicEntityCharacteristic)
        {
            var characteristicQuantificationAllowedTerms = new List<CharacteristicQuantificationAllowedTerm>();

            if (anatomicEntityCharacteristic.AllowedTerm != null)
            {
                for (int index = 0; index < anatomicEntityCharacteristic.AllowedTerm.Count(); index++)
                {
                    var term =
                        CharacteristicQuantificationAllowedTermFromXsdAllowedTerm(
                            anatomicEntityCharacteristic.AllowedTerm[index]);
                    if (term != null)
                    {
                        term.PresentationIndex = index;
                        characteristicQuantificationAllowedTerms.Add(term);
                    }
                }
            }

            int itemNumber;
            int.TryParse(anatomicEntityCharacteristic.itemNumber, out itemNumber);

            int minCardinality;
            int.TryParse(anatomicEntityCharacteristic.minCardinality, out minCardinality);

            int maxCardinality;
            int.TryParse(anatomicEntityCharacteristic.maxCardinality, out maxCardinality);

            string label = anatomicEntityCharacteristic.label;
            if (anatomicEntityCharacteristic.QuestionType != null)
                label = anatomicEntityCharacteristic.QuestionType.codeMeaning;

            return new AimTemplateTreeAnatomicEntityCharacteristicNode(
                label,
                itemNumber,
                anatomicEntityCharacteristic.explanatoryText,
                minCardinality,
                maxCardinality,
                anatomicEntityCharacteristic.shouldDisplay,
                anatomicEntityCharacteristic.groupLabel,
                ValidTermFromXsdValidTerm(anatomicEntityCharacteristic.QuestionType),
                anatomicEntityCharacteristic.annotatorConfidence,
                characteristicQuantificationAllowedTerms,
                anatomicEntityCharacteristic.id);
        }

        private AimTemplateTreeImagingObservationCharacteristicNode AimTemplateTreeImagingObservationCharacteristicNodeFromXsdImagingObservationCharacteristic(TemplateComponentImagingObservationImagingObservationCharacteristic imagingObservationCharacteristic)
        {
            var characteristicQuantificationAllowedTerms = new List<CharacteristicQuantificationAllowedTerm>();

            if (imagingObservationCharacteristic.AllowedTerm != null)
            {
                for (int index = 0; index < imagingObservationCharacteristic.AllowedTerm.Count(); index++)
                {
                    var term =
                        CharacteristicQuantificationAllowedTermFromXsdAllowedTerm(
                            imagingObservationCharacteristic.AllowedTerm[index]);
                    if (term != null)
                    {
                        term.PresentationIndex = index;
                        characteristicQuantificationAllowedTerms.Add(term);
                    }
                }
            }

            int itemNumber;
            int.TryParse(imagingObservationCharacteristic.itemNumber, out itemNumber);

            int minCardinality;
            int.TryParse(imagingObservationCharacteristic.minCardinality, out minCardinality);

            int maxCardinality;
            int.TryParse(imagingObservationCharacteristic.maxCardinality, out maxCardinality);

            string label = imagingObservationCharacteristic.label;
            if (imagingObservationCharacteristic.QuestionType != null)
                label = imagingObservationCharacteristic.QuestionType.codeMeaning;

            return new AimTemplateTreeImagingObservationCharacteristicNode(
                label,
                itemNumber,
                imagingObservationCharacteristic.explanatoryText,
                minCardinality,
                maxCardinality,
                imagingObservationCharacteristic.shouldDisplay,
                imagingObservationCharacteristic.groupLabel,
                ValidTermFromXsdValidTerm(imagingObservationCharacteristic.QuestionType),
                imagingObservationCharacteristic.annotatorConfidence,
                characteristicQuantificationAllowedTerms,
                imagingObservationCharacteristic.id);
        }

        private AimTemplateTreeImagingObservationCharacteristicNode AimTemplateTreeImagingObservationCharacteristicNodeFromXsdImagingObservationCharacteristic(TemplateComponentAnatomicEntityImagingObservationCharacteristic imagingObservationCharacteristic)
        {
            var characteristicQuantificationAllowedTerms = new List<CharacteristicQuantificationAllowedTerm>();

            if (imagingObservationCharacteristic.AllowedTerm != null)
            {
                for (int index = 0; index < imagingObservationCharacteristic.AllowedTerm.Count(); index++)
                {
                    var term =
                        CharacteristicQuantificationAllowedTermFromXsdAllowedTerm(
                            imagingObservationCharacteristic.AllowedTerm[index]);
                    if (term != null)
                    {
                        term.PresentationIndex = index;
                        characteristicQuantificationAllowedTerms.Add(term);
                    }
                }
            }

            int itemNumber;
            int.TryParse(imagingObservationCharacteristic.itemNumber, out itemNumber);

            int minCardinality;
            int.TryParse(imagingObservationCharacteristic.minCardinality, out minCardinality);

            int maxCardinality;
            int.TryParse(imagingObservationCharacteristic.maxCardinality, out maxCardinality);

            string label = imagingObservationCharacteristic.label;
            if (imagingObservationCharacteristic.QuestionType != null)
                label = imagingObservationCharacteristic.QuestionType.codeMeaning;

            return new AimTemplateTreeImagingObservationCharacteristicNode(
                label,
                itemNumber,
                imagingObservationCharacteristic.explanatoryText,
                minCardinality,
                maxCardinality,
                imagingObservationCharacteristic.shouldDisplay,
                imagingObservationCharacteristic.groupLabel,
                ValidTermFromXsdValidTerm(imagingObservationCharacteristic.QuestionType),
                imagingObservationCharacteristic.annotatorConfidence,
                characteristicQuantificationAllowedTerms,
                imagingObservationCharacteristic.id);
        }

        private MemoryStream SerializeAimTemplateTree(AimTemplateTree tree)
        {
            XmlObjectSerializer serializer = new DataContractSerializer(typeof(AimTemplateTree));

            MemoryStream ms = new MemoryStream();
            serializer.WriteObject(ms, tree);
            ms.Seek(0, SeekOrigin.Begin);
            return ms;
        }

        private AimTemplateTree DeserializeAimTemplateTree(MemoryStream ms)
        {
            AimTemplateTree tree = null;

            XmlDictionaryReader reader =
                XmlDictionaryReader.CreateTextReader(ms, new XmlDictionaryReaderQuotas());
            var ser = new DataContractSerializer(typeof(AimTemplateTree));

            tree = (AimTemplateTree)ser.ReadObject(reader, true);
            reader.Close();

            return tree;
        }

        public Dictionary<TemplateTree.StandardCodeSequence, AimTemplateTree> DeserializeAimTemplateTreeFromTemplate(string filename)
        {
            using (FileStream fs = new FileStream(filename, FileMode.Open))
            {
                var xmlSerializer = new XmlSerializer(typeof(TemplateContainer));
                var component = (TemplateContainer)xmlSerializer.Deserialize(fs);
                return AimTemplateTreeFromXsdTemplate(component);
            }
        }
    }
}
