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
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Globalization;
using System.IO;
using System.Net;
using System.Net.Configuration;
using System.Reflection;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Web;
using AimDataService.Configuration;
using ClearCanvas.Common;

namespace AimDataService
{
    public static class AimeWebService
    {
        private const int KeyValidTime = 600;

        public static ApiKeyCredentials Login(string username, string password)
        {
            return Login(username, password, "external.org", KeyValidTime);
        }

        public static ApiKeyCredentials Login(string username, string password, string clientId)
        {
            return Login(username, password, clientId, KeyValidTime);
        }

        public static ApiKeyCredentials Login(string username, string password, string clientId,
                                              int validLifeTimeSeconds)
        {
            using (var webClient = new WebClient())
            {
                SetAllowUnsafeHeaderParsing20();

                string url = SearchSettings.Default.SecureTokenServiceLoginUrl;

                if (String.IsNullOrEmpty(url))
                    //url = "http://imaging.cci.emory.edu/rest/aime-test/middleware/securityTokenService";
                    return null;

                // Base64 encoding of login credentials
                string credentialsBase64 = Convert.ToBase64String(Encoding.ASCII.GetBytes(username + ":" + password));

                // Add encoded credentials to header as basic authentication
                webClient.Headers[HttpRequestHeader.Authorization] = string.Format("Basic {0}", credentialsBase64);

                NameValueCollection queryString = BuildQueryString(new Collection<KeyValuePair<string, string>>
                                                                       {
                                                                           new KeyValuePair<string, string>("clientId",
                                                                                                            clientId),
                                                                           new KeyValuePair<string, string>("lifetime",
                                                                                                            validLifeTimeSeconds
                                                                                                                .
                                                                                                                ToString
                                                                                                                ())
                                                                       });

                using (var ms = new MemoryStream(webClient.DownloadData(url + "?" + queryString)))
                {
                    var serializer = new DataContractJsonSerializer(typeof (AimeLoginResult));
                    var aimLoginResult = (AimeLoginResult) serializer.ReadObject(ms);
                    DateTime expirationTime;
                    //DateTime.TryParse(aimLoginResult.Expires, out expirationTime);

                    DateTime? nullableExpiration = null;

                    if (DateTime.TryParseExact(aimLoginResult.Expires, "ddd MMM dd HH:mm:ss EDT yyyy",
                                               new CultureInfo("en-US"), DateTimeStyles.None, out expirationTime))
                    {
                        expirationTime = TimeZoneInfo.ConvertTime(expirationTime,
                                                                  TimeZoneInfo.FindSystemTimeZoneById(
                                                                      "Eastern Standard Time"),
                                                                  TimeZoneInfo.Local);
                        nullableExpiration = expirationTime;
                    }

                    return new ApiKeyCredentials
                               {
                                   UserName = username,
                                   Password = password,
                                   ApiKey = aimLoginResult.ApiKey,
                                   ClientId = aimLoginResult.Clientid,
                                   ExpirationTime = nullableExpiration
                               };
                }
            }
        }

        public static List<AimeAnnotationContainer> Find(string apiKey, AimeSearchCriteria searchCriteria)
        {
            using (var webClient = new WebClient())
            {
                string url = SearchSettings.Default.AimDataServiceUrl;

                if (String.IsNullOrEmpty(url))
                    //url = "http://imaging.cci.emory.edu/rest/aime-test/middleware/services/AIME/AIME4";
                    return new List<AimeAnnotationContainer>();

                if (!url.EndsWith("/"))
                    url = url.Trim() + "/";

                // Add encoded credentials to header as basic authentication
                webClient.Headers.Add("api_key", apiKey);
                webClient.Headers["Content-Type"] = "text/plain; charset=UTF-8";

                NameValueCollection queryString = BuildFindQueryString(searchCriteria);

                Platform.Log(LogLevel.Debug, "Find on AIM Data Service: " + url + "query/find?" + queryString);

                using (var ms = new MemoryStream(webClient.DownloadData(url + "query/find?" + queryString)))
                {
                    var serializer = new DataContractJsonSerializer(typeof (List<AimeAnnotationContainer>));

                    return (List<AimeAnnotationContainer>) serializer.ReadObject(ms);
                }
            }
        }

        public static string Retrieve(string apiKey, AimeSearchCriteria searchCriteria)
        {
            using (var webClient = new WebClient())
            {
                string url = SearchSettings.Default.AimDataServiceUrl;

                if (String.IsNullOrEmpty(url))
                    //url = "http://imaging.cci.emory.edu/rest/aime-test/middleware/services/AIME/AIME4";
                    return null;

                if (!url.EndsWith("/"))
                    url = url.Trim() + "/";

                // Add encoded credentials to header as basic authentication
                webClient.Headers.Add("api_key", apiKey);
                webClient.Headers["Content-Type"] = "text/plain; charset=UTF-8";

                NameValueCollection queryString = BuildFindQueryString(searchCriteria);

                Platform.Log(LogLevel.Debug, "Retrieve on AIM Data Service: " + url + "query/retrieve?" + queryString);

                string results = webClient.DownloadString(url + "query/retrieve?" + queryString);

                // Remove results tag
                const string resultsTagOpen = "<results>";
                const string resultsTagClose = "</results>";
                if (results.Contains(resultsTagOpen) && results.Contains(resultsTagClose))
                {
                    results = results.Substring(
                        results.IndexOf(resultsTagOpen) + resultsTagOpen.Length,
                        results.IndexOf(resultsTagClose) - (results.IndexOf(resultsTagOpen) + resultsTagOpen.Length)
                        );
                }

                return results;
            }
        }

        public static string Submit(string apiKey, string annotation)
        {
            if (annotation != null)
            {
                using (var webClient = new WebClient())
                {
                    string url = SearchSettings.Default.AimDataServiceUrl;

                    if (String.IsNullOrEmpty(url))
                        //url = "http://imaging.cci.emory.edu/rest/aime-test/middleware/services/AIME/AIME4";
                        return String.Empty;

                    if (!url.EndsWith("/"))
                        url = url.Trim() + "/";

                    webClient.Headers.Add("api_key", apiKey);
                    webClient.Headers["Content-Type"] = "text/plain; charset=UTF-8";

                    string result = webClient.UploadString(url + "submit/xml", annotation);
                    return result;
                }
            }
            return "fail";
        }

        private static NameValueCollection BuildFindQueryString(AimeSearchCriteria searchCriteria)
        {
            string annotationContainerUids = String.Empty;
            if (!String.IsNullOrEmpty(searchCriteria.AnnotationContainreUid))
            {
                annotationContainerUids = "'" + searchCriteria.AnnotationContainreUid + "'";
            }
            var keyValueCollection = new Collection<KeyValuePair<string, string>>();
            if (!String.IsNullOrEmpty(searchCriteria.Username))
                keyValueCollection.Add(new KeyValuePair<string, string>("username", searchCriteria.Username));
            if (!String.IsNullOrEmpty(searchCriteria.AnatomicEntity))
                keyValueCollection.Add(new KeyValuePair<string, string>("anatomicalEntity",
                                                                        searchCriteria.AnatomicEntity));
            if (!String.IsNullOrEmpty(searchCriteria.AnatomicEntityCharacteristic))
                keyValueCollection.Add(new KeyValuePair<string, string>("anatomicEntityCharacteristic",
                                                                        searchCriteria.AnatomicEntityCharacteristic));
            if (!String.IsNullOrEmpty(searchCriteria.ImagingObservationEntity))
                keyValueCollection.Add(new KeyValuePair<string, string>("imagingObservationEntity",
                                                                        searchCriteria.ImagingObservationEntity));
            if (!String.IsNullOrEmpty(searchCriteria.ImagingObservationEntityCharacteristic))
                keyValueCollection.Add(new KeyValuePair<string, string>("imagingObservationEntityCharacteristic",
                                                                        searchCriteria.
                                                                            ImagingObservationEntityCharacteristic));
            if (!String.IsNullOrEmpty(searchCriteria.StudyInstanceUid))
                keyValueCollection.Add(new KeyValuePair<string, string>("studyInstanceUID",
                                                                        searchCriteria.StudyInstanceUid));
            if (!String.IsNullOrEmpty(searchCriteria.PatientName))
                keyValueCollection.Add(new KeyValuePair<string, string>("patientName", searchCriteria.PatientName));
            if (!String.IsNullOrEmpty(searchCriteria.PatientId))
                keyValueCollection.Add(new KeyValuePair<string, string>("patientID", searchCriteria.PatientId));
            if (!String.IsNullOrEmpty(searchCriteria.AnnotationName))
                keyValueCollection.Add(new KeyValuePair<string, string>("annotationName", searchCriteria.AnnotationName));
            if (!String.IsNullOrEmpty(annotationContainerUids))
                keyValueCollection.Add(new KeyValuePair<string, string>("annotationContainerUID",
                                                                        annotationContainerUids));

            return BuildQueryString(keyValueCollection);
        }

        private static NameValueCollection BuildQueryString(IEnumerable<KeyValuePair<string, string>> keyValueCollection)
        {
            NameValueCollection queryString = HttpUtility.ParseQueryString(string.Empty);

            foreach (var keyValue in keyValueCollection)
                queryString[keyValue.Key] = keyValue.Value;

            return queryString;
        }

        public static bool SetAllowUnsafeHeaderParsing20()
        {
            //Get the assembly that contains the internal class
            Assembly aNetAssembly = Assembly.GetAssembly(typeof (SettingsSection));
            if (aNetAssembly != null)
            {
                //Use the assembly in order to get the internal type for the internal class
                Type aSettingsType = aNetAssembly.GetType("System.Net.Configuration.SettingsSectionInternal");
                if (aSettingsType != null)
                {
                    //Use the internal static property to get an instance of the internal settings class.
                    //If the static instance isn't created already the property will create it for us.
                    object anInstance = aSettingsType.InvokeMember("Section",
                                                                   BindingFlags.Static | BindingFlags.GetProperty |
                                                                   BindingFlags.NonPublic, null, null, new object[] {});

                    if (anInstance != null)
                    {
                        //Locate the private bool field that tells the framework is unsafe header parsing should be allowed or not
                        FieldInfo aUseUnsafeHeaderParsing = aSettingsType.GetField("useUnsafeHeaderParsing",
                                                                                   BindingFlags.NonPublic |
                                                                                   BindingFlags.Instance);
                        if (aUseUnsafeHeaderParsing != null)
                        {
                            aUseUnsafeHeaderParsing.SetValue(anInstance, true);
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    }
}
