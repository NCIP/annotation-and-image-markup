include ../Makefile.rules

NAME = AIMXML
DEPLIBS = ../Altova/libAltova.a ../AltovaXML/libAltovaXML.a
SHAREDDEPLIBS = ../Altova/libAltova.so ../AltovaXML/libAltovaXML.so
LIB = lib$(NAME).a
SHAREDLIB = lib$(NAME).so

HDRS = AIMXML-typeinfo.h
HDRS +=	AIMXML.h

HDRS += type_.CAimStatus.h
HDRS += type_.CAnatomicEntity.h
HDRS += type_.CAnatomicEntityCharacteristic.h
HDRS += type_.CAnnotation.h
HDRS += type_.CAnnotationOfAnnotation.h
HDRS += type_.CAnnotationRole.h
HDRS += type_.CCalculation.h
HDRS += type_.CCalculationData.h
HDRS += type_.CCalculationResult.h
HDRS += type_.CCalculationResultIdentifier.h
HDRS += type_.CCharacteristicQuantification.h
HDRS += type_.CCircle.h
HDRS += type_.CComparisonOperators.h
HDRS += type_.CCoordinate.h
HDRS += type_.CDICOMImageReference.h
HDRS += type_.CDimension.h
HDRS += type_.CEllipse.h
HDRS += type_.CEquipment.h
HDRS += type_.CGeometricShape.h
HDRS += type_.CImage.h
HDRS += type_.CImageAnnotation.h
HDRS += type_.CImageReference.h
HDRS += type_.CImageSeries.h
HDRS += type_.CImageStudy.h
HDRS += type_.CImagingObservation.h
HDRS += type_.CImagingObservationCharacteristic.h
HDRS += type_.CInference.h
HDRS += type_.CInterval.h
HDRS += type_.CMultiPoint.h
HDRS += type_.CNonQuantifiable.h
HDRS += type_.CNumerical.h
HDRS += type_.CPerson.h
HDRS += type_.CPoint.h
HDRS += type_.CPolyline.h
HDRS += type_.CPresentationState.h
HDRS += type_.CQuantile.h
HDRS += type_.CReferencedAnnotation.h
HDRS += type_.CReferencedCalculation.h
HDRS += type_.CReferencedGeometricShape.h
HDRS += type_.CScale.h
HDRS += type_.CSegmentation.h
HDRS += type_.CSpatialCoordinate.h
HDRS += type_.CTextAnnotation.h
HDRS += type_.CThreeDimensionSpatialCoordinate.h
HDRS += type_.CTwoDimensionSpatialCoordinate.h
HDRS += type_.CUser.h
HDRS += type_.CWebImageReference.h
HDRS += type_.CAIMXML.h
HDRS += type_.CanatomicEntityCharacteristicCollectionType.h
HDRS += type_.CcharacteristicQuantificationCollectionType.h
HDRS += type_.CcalculationCollectionType.h
HDRS += type_.CinferenceCollectionType.h
HDRS += type_.CuserType.h
HDRS += type_.CequipmentType.h
HDRS += type_.CanatomicEntityCollectionType.h
HDRS += type_.CimagingObservationCollectionType.h
HDRS += type_.CaimStatusType.h
HDRS += type_.CreferencedAnnotationCollectionType.h
HDRS += type_.CreferencedCalculationCollectionType.h
HDRS += type_.CcalculationResultCollectionType.h
HDRS += type_.CreferencedGeometricShapeCollectionType.h
HDRS += type_.CcoordinateCollectionType.h
HDRS += type_.CcalculationDataCollectionType.h
HDRS += type_.CdimensionCollectionType.h
HDRS += type_.CspatialCoordinateCollectionType.h
HDRS += type_.CimageStudyType.h
HDRS += type_.CpresentationStateCollectionType.h
HDRS += type_.CsegmentationCollectionType.h
HDRS += type_.CimageReferenceCollectionType.h
HDRS += type_.CgeometricShapeCollectionType.h
HDRS += type_.CpersonType.h
HDRS += type_.CtextAnnotationCollectionType.h
HDRS += type_.CimageCollectionType.h
HDRS += type_.CimageSeriesType.h
HDRS += type_.CimagingObservationCharacteristicCollectionType.h
HDRS += type_.CreferencedGeometricShapeType.h
HDRS += type_.CcharacteristicQuantificationCollectionType2.h
HDRS += type_.CannotationRoleType.h
HDRS += type_.CimagingObservationType.h
HDRS += type_.CmultiPointType.h
HDRS += type_xs.CENTITIES.h
HDRS += type_xs.CENTITY.h
HDRS += type_xs.CID.h
HDRS += type_xs.CIDREF.h
HDRS += type_xs.CIDREFS.h
HDRS += type_xs.CNCName.h
HDRS += type_xs.CNMTOKEN.h
HDRS += type_xs.CNMTOKENS.h
HDRS += type_xs.CNOTATION.h
HDRS += type_xs.CName.h
HDRS += type_xs.CQName.h
HDRS += type_xs.CanySimpleType.h
HDRS += type_xs.CanyType.h
HDRS += type_xs.CanyURI.h
HDRS += type_xs.Cbase64Binary.h
HDRS += type_xs.Cboolean.h
HDRS += type_xs.Cbyte.h
HDRS += type_xs.Cdate.h
HDRS += type_xs.CdateTime.h
HDRS += type_xs.Cdecimal.h
HDRS += type_xs.Cdouble.h
HDRS += type_xs.Cduration.h
HDRS += type_xs.Cfloat.h
HDRS += type_xs.CgDay.h
HDRS += type_xs.CgMonth.h
HDRS += type_xs.CgMonthDay.h
HDRS += type_xs.CgYear.h
HDRS += type_xs.CgYearMonth.h
HDRS += type_xs.ChexBinary.h
HDRS += type_xs.Cint.h
HDRS += type_xs.Cinteger.h
HDRS += type_xs.Clanguage.h
HDRS += type_xs.Clong.h
HDRS += type_xs.CnegativeInteger.h
HDRS += type_xs.CnonNegativeInteger.h
HDRS += type_xs.CnonPositiveInteger.h
HDRS += type_xs.CnormalizedString.h
HDRS += type_xs.CpositiveInteger.h
HDRS += type_xs.Cshort.h
HDRS += type_xs.Cstring.h
HDRS += type_xs.Ctime.h
HDRS += type_xs.Ctoken.h
HDRS += type_xs.CunsignedByte.h
HDRS += type_xs.CunsignedInt.h
HDRS += type_xs.CunsignedLong.h
HDRS += type_xs.CunsignedShort.h


SRCS = AIMXML.cpp AIMXML-typeinfo.cpp

OBJS = $(filter %.o, $(SRCS:.cpp=.o))
Q ?= @

# Xerces-C non-shared installation support
ifneq ($(strip $(LIB_XERCESC_FOLDER)),)
DEPLIBS += $(strip $(LIB_XERCESC_FOLDER))/libxerces-c.a
SHAREDDEPLIBS += $(strip $(LIB_XERCESC_FOLDER))/libxerces-c.so
endif

.PHONY: all clean


all: $(LIB)


$(SHAREDLIB): $(OBJS) $(SHAREDDEPLIBS)
	@echo '===> Linking shared $(SHAREDLIB)'
	$(Q)gcc -shared -Wl,-soname,$(SHAREDLIB) -o $(SHAREDLIB)$(VERSION) $(OBJS)
	$(Q)ln -s $(SHAREDLIB)$(VERSION) $(SHAREDLIB)

$(LIB): $(OBJS) $(DEPLIBS)
	@echo '===> Linking $(LIB)'
	$(Q)ar cr $(LIB) $(OBJS)
	$(Q)ranlib $(LIB)

$(OBJS): $(HDRS) $(SRCS)

clean:
	rm -Rf $(OBJS) $(LIB) $(SHAREDLIB)
