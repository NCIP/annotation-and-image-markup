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
using System.Net;
using System.IO;
using System.Xml;
using DataServiceUtil;
using System.ServiceModel;
using System.ServiceModel.Channels;
using TransferServiceContextService;

namespace NBIAService
{
    public class NBIARetrieveByStudyUIDs
    {
        private string[] _str;
        private string _directory;

        /// <summary>
        /// Gets URL upon calling which the required study data can be retrieved.
        /// </summary>
        /// <param name="studyUIDs">List of UIDs for the studies to be retrieved</param>
        /// <param name="endPointUrl">URL of the NBIA Data Service to query. This is NOT the Data Transfer URL!</param>
        /// <returns>URL that returns zip file with the studies</returns>
        public string retrieveStudyURL(string[] studyUIDs, string endPointUrl)
        {
            TransferServiceContextService.DataTransferDescriptor dtd;
            using (NCIACoreServicePortTypeClient proxy = new NCIACoreServicePortTypeClient("NCIACoreServicePortTypePort", endPointUrl))
            {
                try
                {
                    TransferServiceContextReference tras = proxy.retrieveDicomDataByStudyUIDs(studyUIDs); // new TransferServiceContextReference();
                    EndpointReferenceType endPoint = tras.EndpointReference; // new EndpointReferenceType();
                    AddressHeader[] ah = new AddressHeader[endPoint.ReferenceProperties.Any.Length];
                    for (int lcv = 0; lcv < ah.Length; lcv++)
                    {
                        XmlElement refProp = endPoint.ReferenceProperties.Any[lcv];
                        ah[lcv] = AddressHeader.CreateAddressHeader(refProp.LocalName, refProp.NamespaceURI, refProp.InnerText);
                    }
                    EndpointAddress ea = new EndpointAddress(new Uri(endPoint.Address.Value), ah);
                    // create binding by hand so we don't have to associate a config file with a dll
                    BasicHttpBinding binding = new BasicHttpBinding(BasicHttpSecurityMode.None);
                    binding.Name = "TransferServiceContextPortTypePort";
                    TransferServiceContextPortTypeClient transProxy = new TransferServiceContextPortTypeClient(binding, ea);
                    dtd = transProxy.getDataTransferDescriptor();
                }
                catch (System.Net.WebException ex)
                {
                    System.Console.WriteLine(ex.Message); //never gets here
                    throw new GridServicerException("Error querying NCIA Grid", ex);

                }
                catch (Exception e)
                {
                    System.Console.WriteLine(e.Message); //never gets here
                    throw new GridServicerException("Error retrieving from NCIA Grid", e);
                }
            }

            if (string.IsNullOrEmpty(dtd.url))
                return dtd.url;
            else
                return null;
        }

        public void retrieveStudyUIDs(string[] str, string directory)
        {
            _str = str;
            _directory = directory;
            foreach (string st in _str)
            {
                string[] eachStr = { st };
                retrieveStudyUID(eachStr);
            }
        }

        private void retrieveStudyUID(string[] str)
        {   
            TransferServiceContextService.DataTransferDescriptor dtd =null;
            TransferServiceContextPortTypeClient transProxy = null;
            NCIACoreServicePortTypeClient proxy = null;

            try
            {
                proxy = new NCIACoreServicePortTypeClient();
                TransferServiceContextReference tras = proxy.retrieveDicomDataByStudyUIDs(str); // new TransferServiceContextReference();
                EndpointReferenceType endPoint = tras.EndpointReference; // new EndpointReferenceType();
                AddressHeader[] ah = new AddressHeader[endPoint.ReferenceProperties.Any.Length];
                for (int lcv = 0; lcv < ah.Length; lcv++)
                {
                    XmlElement refProp = endPoint.ReferenceProperties.Any[lcv];
                    ah[lcv] = AddressHeader.CreateAddressHeader(refProp.LocalName, refProp.NamespaceURI, refProp.InnerText);
                }
                EndpointAddress ea = new EndpointAddress(new Uri(endPoint.Address.Value), ah);
                // create binding by hand so we don't have to associate a config file with a dll
                BasicHttpBinding binding = new BasicHttpBinding(BasicHttpSecurityMode.None);
                binding.Name = "TransferServiceContextPortTypePort";
                transProxy = new TransferServiceContextPortTypeClient(binding, ea);
                dtd = transProxy.getDataTransferDescriptor();
            }
            catch (System.Net.WebException ex)
            {
                System.Console.WriteLine(ex.Message);                
            }
            catch (Exception e)
            {
                System.Console.WriteLine(e.Message);
                throw new GridServicerException("Error querying NCIA Grid", e);
            }

            if (dtd.url != null && dtd.url.Equals(""))
            {
                WebRequest wr = WebRequest.Create(dtd.url);
                WebResponse resp = wr.GetResponse();
                byte[] buf = new byte[8192];
                int read;
                if (transProxy != null && proxy != null)
                {
                    try
                    {
                        Stream stream = resp.GetResponseStream();
                        FileStream fs = new FileStream(_directory + "/" + str[0] + ".zip", FileMode.Create, FileAccess.Write);
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
