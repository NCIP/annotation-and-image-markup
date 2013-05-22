/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"

#include "dcmtk/dcmimgle/dimoimg.h"
#include "dcmtk/dcmimgle/dimoipxt.h"
#include "dcmtk/dcmimgle/dimoopxt.h"
#include "dcmtk/dcmimgle/diutils.h"


void DiMonoImage::getDataUint8(void *buffer,
                               DiDisplayFunction *disp,
                               const int samples,
                               const unsigned long frame,
                               const int bits,
                               const Uint32 low,
                               const Uint32 high)
{
    if (InterData != NULL)
    {
        if (InterData->isPotentiallySigned())
        {
            if (bits <= 8)
                OutputData = new DiMonoOutputPixelTemplate<Uint8, Sint32, Uint8>(buffer, InterData, Overlays, VoiLutData, PresLutData,
                    disp, VoiLutFunction, WindowCenter, WindowWidth, low, high, Columns, Rows, frame, NumberOfFrames, samples > 1);
            else if (bits <= 16)
                OutputData = new DiMonoOutputPixelTemplate<Uint8, Sint32, Uint16>(buffer, InterData, Overlays, VoiLutData, PresLutData,
                    disp, VoiLutFunction, WindowCenter, WindowWidth, low, high, Columns, Rows, frame, NumberOfFrames);
            else
                OutputData = new DiMonoOutputPixelTemplate<Uint8, Sint32, Uint32>(buffer, InterData, Overlays, VoiLutData, PresLutData,
                    disp, VoiLutFunction, WindowCenter, WindowWidth, low, high, Columns, Rows, frame, NumberOfFrames);
        } else {
            if (bits <= 8)
                OutputData = new DiMonoOutputPixelTemplate<Uint8, Uint32, Uint8>(buffer, InterData, Overlays, VoiLutData, PresLutData,
                    disp, VoiLutFunction, WindowCenter, WindowWidth, low, high, Columns, Rows, frame, NumberOfFrames, samples > 1);
            else if (bits <= 16)
                OutputData = new DiMonoOutputPixelTemplate<Uint8, Uint32, Uint16>(buffer, InterData, Overlays, VoiLutData, PresLutData,
                    disp, VoiLutFunction, WindowCenter, WindowWidth, low, high, Columns, Rows, frame, NumberOfFrames);
            else
                OutputData = new DiMonoOutputPixelTemplate<Uint8, Uint32, Uint32>(buffer, InterData, Overlays, VoiLutData, PresLutData,
                    disp, VoiLutFunction, WindowCenter, WindowWidth, low, high, Columns, Rows, frame, NumberOfFrames);
        }
    }
}


void DiMonoImage::getDataSint8(void *buffer,
                               DiDisplayFunction *disp,
                               const int samples,
                               const unsigned long frame,
                               const int bits,
                               const Uint32 low,
                               const Uint32 high)
{
    if (bits <= 8)
        OutputData = new DiMonoOutputPixelTemplate<Sint8, Sint32, Uint8>(buffer, InterData, Overlays, VoiLutData, PresLutData,
            disp, VoiLutFunction, WindowCenter, WindowWidth, low, high, Columns, Rows, frame, NumberOfFrames, samples > 1);
    else if (bits <= 16)
        OutputData = new DiMonoOutputPixelTemplate<Sint8, Sint32, Uint16>(buffer, InterData, Overlays, VoiLutData, PresLutData,
            disp, VoiLutFunction, WindowCenter, WindowWidth, low, high, Columns, Rows, frame, NumberOfFrames);
    else
        OutputData = new DiMonoOutputPixelTemplate<Sint8, Sint32, Uint32>(buffer, InterData, Overlays, VoiLutData, PresLutData,
            disp, VoiLutFunction, WindowCenter, WindowWidth, low, high, Columns, Rows, frame, NumberOfFrames);
}
