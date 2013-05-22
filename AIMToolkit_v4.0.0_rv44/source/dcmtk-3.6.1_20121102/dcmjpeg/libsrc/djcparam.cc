/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djcparam.h"

DJCodecParameter::DJCodecParameter(
    E_CompressionColorSpaceConversion pCompressionCSConversion,
    E_DecompressionColorSpaceConversion pDecompressionCSConversion,
    E_UIDCreation pCreateSOPInstanceUID,
    E_PlanarConfiguration pPlanarConfiguration,
    OFBool predictor6WorkaroundEnable,
    OFBool pOptimizeHuffman,
    int pSmoothingFactor,
    int pForcedBitDepth,
    Uint32 pFragmentSize,
    OFBool pCreateOffsetTable,
    E_SubSampling pSampleFactors,
    OFBool pWriteYBR422,
    OFBool pConvertToSC,
    unsigned long pWindowType,
    unsigned long pWindowParameter,
    double pVoiCenter,
    double pVoiWidth,
    unsigned long pRoiLeft,
    unsigned long pRoiTop,
    unsigned long pRoiWidth,
    unsigned long pRoiHeight,
    OFBool pUsePixelValues,
    OFBool pUseModalityRescale,
    OFBool pAcceptWrongPaletteTags,
    OFBool pAcrNemaCompatibility,
    OFBool pTrueLosslessMode)
: DcmCodecParameter()
, compressionCSConversion(pCompressionCSConversion)
, decompressionCSConversion(pDecompressionCSConversion)
, planarConfiguration(pPlanarConfiguration)
, optimizeHuffman(pOptimizeHuffman)
, smoothingFactor(pSmoothingFactor)
, forcedBitDepth(pForcedBitDepth)
, fragmentSize(pFragmentSize)
, createOffsetTable(pCreateOffsetTable)
, sampleFactors(pSampleFactors)
, writeYBR422(pWriteYBR422)
, convertToSC(pConvertToSC)
, uidCreation(pCreateSOPInstanceUID)
, windowType(pWindowType)
, windowParameter(pWindowParameter)
, voiCenter(pVoiCenter)
, voiWidth(pVoiWidth)
, roiLeft(pRoiLeft)
, roiTop(pRoiTop)
, roiWidth(pRoiWidth)
, roiHeight(pRoiHeight)
, usePixelValues(pUsePixelValues)
, useModalityRescale(pUseModalityRescale)
, acceptWrongPaletteTags(pAcceptWrongPaletteTags)
, acrNemaCompatibility(pAcrNemaCompatibility)
, trueLosslessMode(pTrueLosslessMode)
, predictor6WorkaroundEnabled_(predictor6WorkaroundEnable)
{
}


DJCodecParameter::DJCodecParameter(const DJCodecParameter& arg)
: DcmCodecParameter(arg)
, compressionCSConversion(arg.compressionCSConversion)
, decompressionCSConversion(arg.decompressionCSConversion)
, planarConfiguration(arg.planarConfiguration)
, optimizeHuffman(arg.optimizeHuffman)
, smoothingFactor(arg.smoothingFactor)
, forcedBitDepth(arg.forcedBitDepth)
, fragmentSize(arg.fragmentSize)
, createOffsetTable(arg.createOffsetTable)
, sampleFactors(arg.sampleFactors)
, writeYBR422(arg.writeYBR422)
, convertToSC(arg.convertToSC)
, uidCreation(arg.uidCreation)
, windowType(arg.windowType)
, windowParameter(arg.windowParameter)
, voiCenter(arg.voiCenter)
, voiWidth(arg.voiWidth)
, roiLeft(arg.roiLeft)
, roiTop(arg.roiTop)
, roiWidth(arg.roiWidth)
, roiHeight(arg.roiHeight)
, usePixelValues(arg.usePixelValues)
, useModalityRescale(arg.useModalityRescale)
, acceptWrongPaletteTags(arg.acceptWrongPaletteTags)
, acrNemaCompatibility(arg.acrNemaCompatibility)
, trueLosslessMode(arg.trueLosslessMode)
, predictor6WorkaroundEnabled_(arg.predictor6WorkaroundEnabled_)
{
}

DJCodecParameter::~DJCodecParameter()
{
}

DcmCodecParameter *DJCodecParameter::clone() const
{
  return new DJCodecParameter(*this);
}

const char *DJCodecParameter::className() const
{
  return "DJCodecParameter";
}
