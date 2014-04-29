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
using ClearCanvas.Common;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Tools;

namespace AimDataService
{
    [ExtensionOf(typeof(DesktopToolExtensionPoint))]
    public class AimDataServiceLoginTool : Tool<IDesktopToolContext>
    {
        private static ApiKeyCredentials _credentials;

        public static ApiKeyCredentials Credentials
        {
            get { return _credentials; }
            internal set { _credentials = value; }
        }

        public static bool CredentialsValid
        {
            get
            {
                // Attempt to get new API key if credentials have expired
                try
                {
                    if (_credentials != null && (_credentials.ExpirationTime.HasValue && DateTime.Now > _credentials.ExpirationTime))
                        Credentials = AimeWebService.Login(_credentials.UserName, _credentials.Password);
                }
                catch (Exception ex)
                {
                    Platform.Log(LogLevel.Warn, ex, "Failed renew API Key logging into AIM Data Service 2.", null);
                }
                if (_credentials == null || (_credentials.ExpirationTime.HasValue && DateTime.Now > _credentials.ExpirationTime))
                    return false;
                return true;
            }
        }

        public AimDataServiceLoginTool()
        {
            Instance = this;
        }

        public static DialogBoxAction RequestLogin()
        {
            if (!String.IsNullOrEmpty(Configuration.SearchSettings.Default.SecureTokenServiceLoginUrl))
            {
              
                var loginComponent = new AimDataServiceLoginComponent();

                var action = Instance.Context.DesktopWindow.ShowDialogBox(loginComponent, "AIM Data Service Login");
                if (action == DialogBoxAction.Ok)
                {
                    Credentials = loginComponent.Credentials;
                }
                return action;  
            }
            return DialogBoxAction.Cancel;
        }

        private static AimDataServiceLoginTool Instance { get; set; }
    }
}
