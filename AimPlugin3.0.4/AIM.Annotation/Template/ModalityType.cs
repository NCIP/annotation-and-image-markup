#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Xml.Serialization;

namespace AIM.Annotation.Template
{
	[XmlTypeAttribute(Namespace = TemplateContainer.Namespace)]
	public enum ModalityType
	{
		AU,
		BDUS,
		BI,
		BMD,
		CD,
		CR,
		CT,
		DD,
		DOC,
		DG,
		DX,
		ECG,
		EPS,
		ES,
		GM,
		HC,
		HD,
		IO,
		IVUS,
		KO,
		LS,
		MG,
		MR,
		NM,
		OCT,
		OT,
		OP,
		OPM,
		OPT,
		OPR,
		OPV,
		PR,
		PT,
		PX,
		REG,
		RG,
		RTDOSE,
		RTIMAGE,
		RTPLAN,
		RTSTRUCT,
		RTRECORD,
		SEG,
		SM,
		SMR,
		SR,
		ST,
		US,
		XA,
		XC
	}
}
