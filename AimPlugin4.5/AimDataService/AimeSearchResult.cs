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

using System.Collections.Generic;
using System.Runtime.Serialization;

namespace AimDataService
{
    [DataContract]
    public class AimeSearchResult
    {
        [DataMember]
        public List<AimeAnnotationContainer> AnnotationContainers { get; set; }
    }

    [DataContract]
    public class AimeAnnotationContainer
    {
        [DataMember(Name = "annotationContainerUID")]
        public string AnnotationContainerUid { get; set; }

        [DataMember(Name = "annotationDateTime")]
        public string AnnotationDateTime { get; set; }

        [DataMember(Name = "patientName")]
        public string PatientName { get; set; }

        [DataMember(Name = "sex")]
        public string PatientSex { get; set; }

        [DataMember(Name = "dob")]
        public string PatientDateOfBirth { get; set; }

        [DataMember(Name = "annotationType")]
        public string AnnotationType { get; set; }

        [DataMember(Name = "user")]
        public string User { get; set; }

        [DataMember(Name = "annotations")]
        public List<AimeAnnotation> Annotations { get; set; }
    }

    [DataContract]
    public class AimeAnnotation
    {
        [DataMember(Name = "annotationName")]
        public string AnnotationName { get; set; }

        [DataMember(Name = "annotationUID")]
        public string AnnotationUid { get; set; }

        [DataMember(Name = "studyInstanceUid")]
        public string StudyInstanceUid { get; set; }

        [DataMember(Name = "imagingPhysicalEntities")]
        public List<AimeImagingPhysicalEntities> ImagingPhysicalEntities { get; set; }

        [DataMember(Name = "imagingObservationEntities")]
        public List<AimeImagingObservationEntities> ImagingObservations { get; set; }
    }

    [DataContract]
    public class AimeImagingPhysicalEntities
    {
        [DataMember(Name = "imagingPhysicalEntityCharacteristicCollection")]
        public AimeImagingPhysicalEntityCharacteristicCollection ImagingPhysicalEntityCharacteristicCollection { get; set; }

        [DataMember(Name = "typeCode")]
        public List<AimeTypeCode> TypeCodes { get; set; }

        [DataMember(Name = "isPresent")]
        public AimeIsPresent IsPresent { get; set; }

        #region Nested type: AimeImagingPhysicalEntityCharacteristicCollection

        [DataContract]
        public class AimeImagingPhysicalEntityCharacteristicCollection
        {
            [DataMember(Name = "imagingPhysicalEntityCharacteristic")]
            public List<AimeImagingPhysicalEntityCharacteristic> ImagingPhysicalEntityCharacteristics { get; set; }

            [DataMember(Name = "uniqueIdentifier")]
            public AimeUniqueIdentifier UniqueIdentifier { get; set; }

            #region Nested type: AimeImagingPhysicalEntityCharacteristic

            [DataContract]
            public class AimeImagingPhysicalEntityCharacteristic
            {
                [DataMember(Name = "typeCode")]
                public List<AimeTypeCode> TypeCodes { get; set; }

                [DataMember(Name = "label")]
                public AimeLabel Label { get; set; }
            }

            #endregion
        }

        #endregion
    }

    [DataContract]
    public class AimeImagingObservationEntities
    {
        [DataMember(Name = "imagingObservationCharacteristicCollection")]
        public AimeImagingObservationCharacteristicCollection ImagingPhysicalEntityCharacteristicCollection { get; set; }

        [DataMember(Name = "typeCode")]
        public List<AimeTypeCode> TypeCodes { get; set; }

        [DataMember(Name = "isPresent")]
        public AimeIsPresent IsPresent { get; set; }

        #region Nested type: AimeImagingObservationCharacteristicCollection

        [DataContract]
        public class AimeImagingObservationCharacteristicCollection
        {
            [DataMember(Name = "imagingObservationCharacteristic")]
            public List<AimeImagingObservationCharacteristic> ImagingPhysicalEntityCharacteristics { get; set; }

            [DataMember(Name = "uniqueIdentifier")]
            public AimeUniqueIdentifier UniqueIdentifier { get; set; }

            #region Nested type: AimeImagingObservationCharacteristic

            [DataContract]
            public class AimeImagingObservationCharacteristic
            {
                [DataMember(Name = "typeCode")]
                public List<AimeTypeCode> TypeCodes { get; set; }

                [DataMember(Name = "label")]
                public AimeLabel Label { get; set; }
            }

            #endregion
        }

        #endregion
    }

    [DataContract]
    public class AimeUniqueIdentifier
    {
        [DataMember(Name = "root")]
        public string Root { get; set; }
    }

    [DataContract]
    public class AimeIsPresent
    {
        [DataMember(Name = "value")]
        public bool Value { get; set; }
    }

    [DataContract]
    public class AimeLabel
    {
        [DataMember(Name = "value")]
        public string Value { get; set; }
    }

    [DataContract]
    public class AimeTypeCode
    {
        [DataMember(Name = "displayName")]
        public AimeDisplayName DisplayName { get; set; }

        [DataMember(Name = "code")]
        public string Code { get; set; }

        [DataMember(Name = "codeSystemName")]
        public string CodeSystemName { get; set; }

        [DataMember(Name = "codeSystemVersion")]
        public string CodeSystemVersion { get; set; }

        #region Nested type: AimeDisplayName

        [DataContract]
        public class AimeDisplayName
        {
            [DataMember(Name = "value")]
            public string Value { get; set; }
        }

        #endregion
    }
}
