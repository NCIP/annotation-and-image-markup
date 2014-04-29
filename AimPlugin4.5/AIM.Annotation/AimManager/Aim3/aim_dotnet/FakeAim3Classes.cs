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
using ClearCanvas.Dicom.Iod;

namespace AIM.Annotation.AimManager.Aim3.aim_dotnet
{
	//
	// Placeholder Classes for AIM 3.0 functionality to enable old AIM 3.0 code to compile
	//
	public abstract class Annotation
	{
		public string UniqueIdentifier
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string Name
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public DateTime DateTime
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string Comment
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeMeaning
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeDesignator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeVersion
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public Equipment Equipment
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public User User
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<AnatomicEntity> AnatomyEntityCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<ImagingObservation> ImagingObservationCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<Calculation> CalculationCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<Inference> InferenceCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public AnnotationKind AnnotationKind
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public enum AnnotationKind
	{
		AK_ImageAnnotation,
		AK_AnnotationOfAnnotation
	}

	internal class ImageAnnotation : Annotation
	{
		public List<ImageReference> ImageReferenceCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<IGeometricShape> GeometricShapeCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<TextAnnotation> TextAnnotationCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public Person Patient
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	internal class AnnotationOfAnnotation : Annotation
	{
	}

	public class AnatomicEntity
	{
		public string Label
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeMeaning
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeDesignator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeVersion
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public double? AnnotatorConfidence
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<AnatomicEntityCharacteristic> AnatomicEntityCharacteristicCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class AnatomicEntityCharacteristic
	{
		public string Label
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeMeaning
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeDesignator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeVersion
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<ICharacteristicQuantification> CharacteristicQuantificationCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public double? AnnotatorConfidence
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class ImagingObservation
	{
		public string Label
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeMeaning
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeDesignator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeVersion
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public double? AnnotatorConfidence
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<ImagingObservationCharacteristic> ImagingObservationCharacteristicCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class ImagingObservationCharacteristic
	{
		public string Label
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeMeaning
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeDesignator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeVersion
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<ICharacteristicQuantification> CharacteristicQuantificationCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public double? AnnotatorConfidence
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Inference
	{
		public string CodeValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeMeaning
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeDesignator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeVersion
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public double? AnnotatorConfidence
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public bool ImageEvidence
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class ICharacteristicQuantification
	{
		public string Name
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public double? AnnotatorConfidence
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public CharacteristicQuantificationType QuantificationType
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public enum CharacteristicQuantificationType
	{
		Numerical,
		Quantile,
		NonQuantifiable,
		Scale,
		Interval
	}

	public class NonQuantifiable : ICharacteristicQuantification
	{
		public string CodeValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeMeaning
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeVersion
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeDesignator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Scale : ICharacteristicQuantification
	{
		public string Value
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string Description
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string Comment
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Quantile : ICharacteristicQuantification
	{
		public int Bin
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Interval : ICharacteristicQuantification
	{
		public double MinValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public double MaxValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public ComparisonOperatorIdentifier MinOperator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public ComparisonOperatorIdentifier MaxOperator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string UcumString
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Numerical : ICharacteristicQuantification
	{
		public double Value
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public ComparisonOperatorIdentifier Operator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string UcumString
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public enum ComparisonOperatorIdentifier
	{
		InvalidComparisonOperator,
		None,
		Equal,
		NotEqual,
		LessThan,
		LessThanEqual,
		GreaterThan,
		GreaterThanEqual
	}

	public class Calculation
	{
		public Calculation()
		{
			throw new NotImplementedException();
		}

		public Calculation(Calculation calculation)
		{
			throw new NotImplementedException();
		}

		public string UID
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeValue
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodeMeaning
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeDesignator
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string CodingSchemeVersion
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string Description
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<CalculationResult> CalculationResultCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<ReferencedGeometricShape> ReferencedGeometricShapeCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class CalculationResult
	{
		public CalculationResultIdentifier TypeOfCalculationResult
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string UnitOfMeasure
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public int NumberOfDimensions
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<Dimension> DimensionCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<CalculationData> CalculationDataCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Dimension
	{
		public int Index
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public int Size
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string Label
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class CalculationData
	{
		public double Value
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public List<Coordinate> CoordinateCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Coordinate
	{
		public int DimensionIndex
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public int Position
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public enum CalculationResultIdentifier
	{
		Scalar
	}

	internal interface ImageReference
	{
	}

	internal class DICOMImageReference : ImageReference
	{
		public ImageStudy Study
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	internal class WebImageReference : ImageReference
	{
	}

	internal class ImageStudy
	{
		public ImageSeries Series
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string InstanceUID
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public DateTime StartDate
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	internal class ImageSeries
	{
		public string InstanceUID;

		public List<Image> ImageCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	internal class Image
	{
		public string SopInstanceUID
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string SopClassUID
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class TextAnnotation
	{
		public IGeometricShape ConnectorPoints
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string Text
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class ReferencedGeometricShape
	{
		public int ReferencedShapeIdentifier
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class IGeometricShape
	{
		public List<ISpatialCoordinate> SpatialCoordinateCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public bool IsIncludeFlag
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public int ShapeIdetifier
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Point : IGeometricShape
	{
		public ISpatialCoordinate Center
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Circle : IGeometricShape
	{
		public ISpatialCoordinate Center
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public ISpatialCoordinate RadiusPoint
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Ellipse : IGeometricShape
	{
		public List<ISpatialCoordinate> EllipseCollection
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class MultiPoint : IGeometricShape
	{
	}

	public class Polyline : IGeometricShape
	{
	}

	public enum SpatialCoordinateType
	{
		SPATIAL_COORD_2D,
		SPATIAL_COORD_3D
	}

	public interface ISpatialCoordinate
	{
		SpatialCoordinateType CoordinateType { get; set; }
	}

	public class TwoDimensionSpatialCoordinate : ISpatialCoordinate
	{
		public string ImageReferenceUID;
		public SpatialCoordinateType CoordinateType { get; set; }

		public int ReferencedFrameNumber
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public double X
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public double Y
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public int CoordinateIndex
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Person
	{
		public string Id
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public PersonName Name
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public DateTime BirthDate
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string Sex
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string EthnicGroup
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class Equipment
	{
		public string ManufacturerName
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string ManufacturerModelName
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string SoftwareVersion
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public class User
	{
		public string Name
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string LoginName
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public string RoleInTrial
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}

		public int NumberWithinRoleOfClinicalTrial
		{
			get { throw new NotImplementedException(); }
			set { throw new NotImplementedException(); }
		}
	}

	public abstract class BaseModel
	{
		public List<Annotation> ReadAnnotationsFromFile(string fileName)
		{
			throw new NotImplementedException();
		}

		public void WriteAnnotationToFile(Annotation annotation, string filePathName)
		{
			throw new NotImplementedException();
		}

		// Do not use it for XML!!!
		public void WriteAnnotationsToFile(List<Annotation> annotations, string fileName)
		{
			throw new NotImplementedException();
		}

		public string AimModelVersion
		{
			get { throw new NotImplementedException(); }
		}
	}

	public class XmlModel : BaseModel, IDisposable
	{
		public Annotation ReadAnnotationFromXmlString(string xmlString)
		{
			throw new NotImplementedException();
		}

		public string WriteAnnotationToXmlString(Annotation annotation)
		{
			throw new NotImplementedException();
		}

		#region IDisposable Members

		public void Dispose()
		{
			throw new NotImplementedException();
		}

		#endregion
	}

	public class DcmModel : BaseModel, IDisposable
	{
		#region IDisposable Members

		public void Dispose()
		{
			throw new NotImplementedException();
		}

		#endregion
	}
}
