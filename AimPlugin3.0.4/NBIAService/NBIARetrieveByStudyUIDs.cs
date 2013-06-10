#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.IO;
using System.Net;
using System.ServiceModel;
using System.ServiceModel.Channels;
using DataServiceUtil;
using TransferServiceContextService;

namespace NBIAService
{
	public class NBIARetrieveByStudyUIDs
	{
		private string[] _str;
		private string _directory;

		public string retrieveStudyURL(string[] studyUIDs, string endPointUrl)
		{
			TransferServiceContextService.DataTransferDescriptor dtd;
			try
			{
				var proxy = new NCIACoreServicePortTypeClient();
				var tras = proxy.retrieveDicomDataByStudyUIDs(studyUIDs);
				var endPoint = tras.EndpointReference;
				var ah = new AddressHeader[endPoint.ReferenceProperties.Any.Length];
				proxy.Endpoint.Address = new EndpointAddress(endPointUrl);
				for (var lcv = 0; lcv < ah.Length; lcv++)
				{
					var refProp = endPoint.ReferenceProperties.Any[lcv];
					ah[lcv] = AddressHeader.CreateAddressHeader(refProp.LocalName, refProp.NamespaceURI, refProp.InnerText);
				}
				var ea = new EndpointAddress(new Uri(endPoint.Address.Value), ah);
				var binding = new BasicHttpBinding(BasicHttpSecurityMode.None);
				binding.Name = "TransferServiceContextPortTypePort";
				var transProxy = new TransferServiceContextPortTypeClient(binding, ea);
				dtd = transProxy.getDataTransferDescriptor();
			}
			catch (WebException ex)
			{
				Console.WriteLine(ex.Message);
				throw new GridServicerException("Error querying NCIA Grid", ex);

			}
			catch (Exception e)
			{
				Console.WriteLine(e.Message);
				throw new GridServicerException("Error retrieving from NCIA Grid", e);
			}

			if (dtd.url != null || dtd.url.Equals(""))
				return dtd.url;
			else
				return null;
		}

		public void retrieveStudyUIDs(string[] str, string directory)
		{
			_str = str;
			_directory = directory;
			foreach (var st in _str)
			{
				string[] eachStr = { st };
				retrieveStudyUID(eachStr);
			}
		}

		private void retrieveStudyUID(string[] str)
		{
			TransferServiceContextService.DataTransferDescriptor dtd = null;
			TransferServiceContextPortTypeClient transProxy = null;
			NCIACoreServicePortTypeClient proxy = null;

			try
			{
				proxy = new NCIACoreServicePortTypeClient();
				var tras = proxy.retrieveDicomDataByStudyUIDs(str);
				var endPoint = tras.EndpointReference;
				var ah = new AddressHeader[endPoint.ReferenceProperties.Any.Length];
				for (var lcv = 0; lcv < ah.Length; lcv++)
				{
					var refProp = endPoint.ReferenceProperties.Any[lcv];
					ah[lcv] = AddressHeader.CreateAddressHeader(refProp.LocalName, refProp.NamespaceURI, refProp.InnerText);
				}
				var ea = new EndpointAddress(new Uri(endPoint.Address.Value), ah);
				var binding = new BasicHttpBinding(BasicHttpSecurityMode.None);
				binding.Name = "TransferServiceContextPortTypePort";
				transProxy = new TransferServiceContextPortTypeClient(binding, ea);
				dtd = transProxy.getDataTransferDescriptor();
			}
			catch (WebException ex)
			{
				Console.WriteLine(ex.Message);
			}
			catch (Exception e)
			{
				Console.WriteLine(e.Message);
				throw new GridServicerException("Error querying NCIA Grid", e);
			}

			if (dtd.url != null && dtd.url.Equals(""))
			{
				var wr = WebRequest.Create(dtd.url);
				var resp = wr.GetResponse();
				var buf = new byte[8192];
				int read;
				if (transProxy != null && proxy != null)
				{
					try
					{
						var stream = resp.GetResponseStream();
						var fs = new FileStream(_directory + "/" + str[0] + ".zip", FileMode.Create, FileAccess.Write);
						while ((read = stream.Read(buf, 0, buf.Length)) > 0)
						{
							fs.Write(buf, 0, read);
						}
						fs.Close();
						stream.Close();
						resp.Close();
						proxy.Close();
						transProxy.Close();
					}
					catch (IOException ioe)
					{
						throw new GridServicerException("Error writting zip file from caGrid", ioe);
					}
				}
			}
		}
	}
}
