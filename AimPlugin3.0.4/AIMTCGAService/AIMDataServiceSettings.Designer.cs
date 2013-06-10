//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L


namespace AIMTCGAService {
    
    
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "9.0.0.0")]
    internal sealed partial class AIMDataServiceSettings : global::System.Configuration.ApplicationSettingsBase {
        
        private static AIMDataServiceSettings defaultInstance = ((AIMDataServiceSettings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new AIMDataServiceSettings())));
        
        public static AIMDataServiceSettings Default {
            get {
                return defaultInstance;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("")]
        public string AIMDataServiceUrl {
            get {
                return ((string)(this["AIMDataServiceUrl"]));
            }
            set {
                this["AIMDataServiceUrl"] = value;
            }
        }
        
        [global::System.Configuration.UserScopedSettingAttribute()]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [global::System.Configuration.DefaultSettingValueAttribute("<?xml version=\"1.0\" encoding=\"utf-16\"?>\r\n<ArrayOfString xmlns:xsi=\"http://www.w3." +
            "org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" />")]
        public global::System.Collections.Specialized.StringCollection AIMDataServiceUrlList {
            get {
                return ((global::System.Collections.Specialized.StringCollection)(this["AIMDataServiceUrlList"]));
            }
            set {
                this["AIMDataServiceUrlList"] = value;
            }
        }
    }
}
