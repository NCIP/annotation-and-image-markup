/*
*  Copyright Northwestern University
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "../stdafx.h"

#include "../AimEnum.h"

#include "AimBase.h"
#include "DateTime.h"
#include "User.h"
#include "Equipment.h"
#include "AimStatus.h"
#include "ReferencedGeometricShape.h"
#include "CharacteristicQuantification.h"
#include "AnatomicEntityCharacteristic.h"
#include "AnatomicEntity.h"
#include "ImagingObservationCharacteristic.h"
#include "ImagingObservation.h"
#include "ImageReference.h"
#include "Segmentation.h"
#include "ReferencedCalculation.h"
#include "Dimension.h"
#include "Coordinate.h"
#include "CalculationData.h"
#include "CalculationResult.h"
#include "Calculation.h"
#include "Inference.h"
#include "Annotation.h"
#include "Person.h"
#include "SpatialCoordinate.h"
#include "GeometricShape.h"
#include "MultiPoint.h"
#include "TextAnnotation.h"
#include "ImageAnnotation.h"

using namespace aim_lib;

ImageAnnotation::ImageAnnotation() : Annotation(C_IMAGE_ANNOTATION_NAME){
}

ImageAnnotation::ImageAnnotation(const ImageAnnotation& imageAnnotation) : Annotation(imageAnnotation){

	this->SetPatient(imageAnnotation.GetPatient());
	this->SetSegmentationCollection(imageAnnotation.GetSegmentationCollection());
	this->SetGeometricShapeCollection(imageAnnotation.GetGeometricShapeCollection());
	this->SetTextAnnotationCollection(imageAnnotation.GetTextAnnotationCollection());
	this->SetImageReferenceCollection(imageAnnotation.GetImageReferenceCollection());
}

ImageAnnotation::~ImageAnnotation(){
	// TODO - release all collections

	// Geometric Shape Collection
	this->FreeAllShapes();

	// Images
	this->FreeAllImages();
}

Annotation::AnnotationKind ImageAnnotation::GetAnnotationKind() const
{
	return Annotation::AK_ImageAnnotation;
}

const Person& ImageAnnotation::GetPatient() const{

	return  _patient;
}

const SegmentationVector& ImageAnnotation::GetSegmentationCollection() const{

	return  _segmentationCollection;
}

const GeoShapePtrVector& ImageAnnotation::GetGeometricShapeCollection() const{

	return _geometricShapeCollection;
}

const ImageReferencePtrVector& ImageAnnotation::GetImageReferenceCollection() const{

	return  _imageReferenceCollection;
}

const TextAnnotationVector& ImageAnnotation::GetTextAnnotationCollection() const{

	return  _textAnnotationCollection;
}

void ImageAnnotation::SetPatient(const Person& patient){

	_patient = patient;
}

void ImageAnnotation::SetSegmentationCollection(const SegmentationVector& segmentations){

	_segmentationCollection.assign(segmentations.begin(), segmentations.end());
}

void ImageAnnotation::SetGeometricShapeCollection(const GeoShapePtrVector& geometricShapes){

	this->FreeAllShapes();

	_geometricShapeCollection.reserve(geometricShapes.size());
	for(GeoShapePtrVector::size_type i=0; i < geometricShapes.size(); i++)
		if (geometricShapes[i] != NULL)
			_geometricShapeCollection.push_back(geometricShapes[i]->Clone());
}

void ImageAnnotation::SetImageReferenceCollection(const ImageReferencePtrVector& imageReferences){

	this->FreeAllImages();

	_imageReferenceCollection.reserve(imageReferences.size());
	for(ImageReferencePtrVector::size_type i=0; i < imageReferences.size(); i++)
		if (imageReferences[i] != NULL)
			_imageReferenceCollection.push_back(imageReferences[i]->Clone());
}

void ImageAnnotation::SetTextAnnotationCollection(const TextAnnotationVector& textAnnotations){

	_textAnnotationCollection.assign(textAnnotations.begin(), textAnnotations.end());
}

void ImageAnnotation::FreeAllShapes()
{
	GeoShapePtrVector::iterator iter;
	for(iter = _geometricShapeCollection.begin(); iter < _geometricShapeCollection.end(); iter++)
	{
		delete *iter;
		*iter = NULL;
	}
	_geometricShapeCollection.clear();
}

void ImageAnnotation::FreeAllImages()
{
	ImageReferencePtrVector::iterator iter;
	for(iter = _imageReferenceCollection.begin(); iter < _imageReferenceCollection.end(); iter++)
	{
		delete *iter;
		*iter = NULL;
	}
	_imageReferenceCollection.clear();
}
