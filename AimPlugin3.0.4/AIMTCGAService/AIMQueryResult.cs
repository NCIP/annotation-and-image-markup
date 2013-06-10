#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Xml;

namespace AIMTCGAService
{
	public class AIMQueryResult
	{
		private string[] _anatomicEntity;
		private string[] _imagingObservation;
		private string _studyInstanceUID;
		private string _seriesInstanceUID;
		private string _sopInstanceUID;
		private string _aimXmlObject;
		private string _patientName;
		readonly XmlElement _xmlElement;

		public AIMQueryResult(XmlElement result)
		{
			_xmlElement = result;
		}

		public string[] anatomicEntity
		{
			get
			{
				string ver = _xmlElement.Attributes["aimVersion"].InnerText;
				return _anatomicEntity;
			}

			set
			{
				_anatomicEntity = value;
			}
		}

		public string[] imagingObservation
		{
			get
			{
				return _imagingObservation;
			}

			set
			{
				_imagingObservation = value;
			}
		}

		public string studyInstanceUID
		{
			get
			{
				return _studyInstanceUID;
			}

			set
			{
				_studyInstanceUID = value;
			}
		}

		public string seriesInstanceUID
		{
			get
			{
				return _seriesInstanceUID;
			}

			set
			{
				_seriesInstanceUID = value;
			}
		}

		public string sopInstanceUID
		{
			get
			{
				return _sopInstanceUID;
			}

			set
			{
				_sopInstanceUID = value;
			}
		}

		public string aimXmlObject
		{
			get
			{
				return _aimXmlObject;
			}

			set
			{
				_aimXmlObject = value;
			}
		}

		public string patientName
		{
			get
			{
				return _patientName;
			}

			set
			{
				_patientName = value;
			}
		}
	}
}
