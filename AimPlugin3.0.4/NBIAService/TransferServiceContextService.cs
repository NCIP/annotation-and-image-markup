//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

namespace TransferServiceContextService
{


    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
        "")]
    public partial class ResourceNotDestroyedFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(TerminationTimeChangeRejectedFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(UnableToSetTerminationTimeFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(ResourceNotDestroyedFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(ResourceUnknownFaultType2))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(ResumeFailedFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(PauseFailedFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(NoCurrentMessageOnTopicFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(TopicNotSupportedFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(InvalidTopicExpressionFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(TopicPathDialectUnknownFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(SubscribeCreationFailedFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(ResourceUnknownFaultType1))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(QueryEvaluationErrorFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(InvalidQueryExpressionFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(UnknownQueryExpressionDialectFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(SetResourcePropertyRequestFailedFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(UnableToModifyResourcePropertyFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(InvalidSetResourcePropertiesRequestContentFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(InvalidResourcePropertyQNameFaultType))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(ResourceUnknownFaultType))]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-BaseFaults-1.2-draft-01.xsd")]
    public partial class BaseFaultType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.DateTime timestampField;

        private EndpointReferenceType originatorField;

        private BaseFaultTypeErrorCode errorCodeField;

        private BaseFaultTypeDescription[] descriptionField;

        private BaseFaultType[] faultCauseField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 0)]
        public System.DateTime Timestamp
        {
            get
            {
                return this.timestampField;
            }
            set
            {
                this.timestampField = value;
                this.RaisePropertyChanged("Timestamp");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 1)]
        public EndpointReferenceType Originator
        {
            get
            {
                return this.originatorField;
            }
            set
            {
                this.originatorField = value;
                this.RaisePropertyChanged("Originator");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 2)]
        public BaseFaultTypeErrorCode ErrorCode
        {
            get
            {
                return this.errorCodeField;
            }
            set
            {
                this.errorCodeField = value;
                this.RaisePropertyChanged("ErrorCode");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute("Description", Order = 3)]
        public BaseFaultTypeDescription[] Description
        {
            get
            {
                return this.descriptionField;
            }
            set
            {
                this.descriptionField = value;
                this.RaisePropertyChanged("Description");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute("FaultCause", Order = 4)]
        public BaseFaultType[] FaultCause
        {
            get
            {
                return this.faultCauseField;
            }
            set
            {
                this.faultCauseField = value;
                this.RaisePropertyChanged("FaultCause");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://schemas.xmlsoap.org/ws/2004/03/addressing")]
    public partial class EndpointReferenceType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private AttributedURI addressField;

        private ReferencePropertiesType referencePropertiesField;

        private AttributedQName portTypeField;

        private ServiceNameType serviceNameField;

        private System.Xml.XmlElement[] anyField;

        private System.Xml.XmlAttribute[] anyAttrField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 0)]
        public AttributedURI Address
        {
            get
            {
                return this.addressField;
            }
            set
            {
                this.addressField = value;
                this.RaisePropertyChanged("Address");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 1)]
        public ReferencePropertiesType ReferenceProperties
        {
            get
            {
                return this.referencePropertiesField;
            }
            set
            {
                this.referencePropertiesField = value;
                this.RaisePropertyChanged("ReferenceProperties");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 2)]
        public AttributedQName PortType
        {
            get
            {
                return this.portTypeField;
            }
            set
            {
                this.portTypeField = value;
                this.RaisePropertyChanged("PortType");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 3)]
        public ServiceNameType ServiceName
        {
            get
            {
                return this.serviceNameField;
            }
            set
            {
                this.serviceNameField = value;
                this.RaisePropertyChanged("ServiceName");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Order = 4)]
        public System.Xml.XmlElement[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
                this.RaisePropertyChanged("Any");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyAttributeAttribute()]
        public System.Xml.XmlAttribute[] AnyAttr
        {
            get
            {
                return this.anyAttrField;
            }
            set
            {
                this.anyAttrField = value;
                this.RaisePropertyChanged("AnyAttr");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://schemas.xmlsoap.org/ws/2004/03/addressing")]
    public partial class AttributedURI : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlAttribute[] anyAttrField;

        private string valueField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyAttributeAttribute()]
        public System.Xml.XmlAttribute[] AnyAttr
        {
            get
            {
                return this.anyAttrField;
            }
            set
            {
                this.anyAttrField = value;
                this.RaisePropertyChanged("AnyAttr");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlTextAttribute(DataType = "anyURI")]
        public string Value
        {
            get
            {
                return this.valueField;
            }
            set
            {
                this.valueField = value;
                this.RaisePropertyChanged("Value");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security")]
    public partial class Operation : object, System.ComponentModel.INotifyPropertyChanged
    {

        private CommunicationMechanism communicationMechanismField;

        private string nameField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 0)]
        public CommunicationMechanism CommunicationMechanism
        {
            get
            {
                return this.communicationMechanismField;
            }
            set
            {
                this.communicationMechanismField = value;
                this.RaisePropertyChanged("CommunicationMechanism");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute()]
        public string name
        {
            get
            {
                return this.nameField;
            }
            set
            {
                this.nameField = value;
                this.RaisePropertyChanged("name");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security")]
    public partial class CommunicationMechanism : object, System.ComponentModel.INotifyPropertyChanged
    {

        private GSITransport gSITransportField;

        private GSISecureMessage gSISecureMessageField;

        private GSISecureConversation gSISecureConversationField;

        private None noneField;

        private bool anonymousPermittedField;

        /// <remarks/>
        public GSITransport GSITransport
        {
            get
            {
                return this.gSITransportField;
            }
            set
            {
                this.gSITransportField = value;
                this.RaisePropertyChanged("GSITransport");
            }
        }

        /// <remarks/>
        public GSISecureMessage GSISecureMessage
        {
            get
            {
                return this.gSISecureMessageField;
            }
            set
            {
                this.gSISecureMessageField = value;
                this.RaisePropertyChanged("GSISecureMessage");
            }
        }

        /// <remarks/>
        public GSISecureConversation GSISecureConversation
        {
            get
            {
                return this.gSISecureConversationField;
            }
            set
            {
                this.gSISecureConversationField = value;
                this.RaisePropertyChanged("GSISecureConversation");
            }
        }

        /// <remarks/>
        public None None
        {
            get
            {
                return this.noneField;
            }
            set
            {
                this.noneField = value;
                this.RaisePropertyChanged("None");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute()]
        public bool anonymousPermitted
        {
            get
            {
                return this.anonymousPermittedField;
            }
            set
            {
                this.anonymousPermittedField = value;
                this.RaisePropertyChanged("anonymousPermitted");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security")]
    public partial class GSITransport : CommunicationStyle
    {
    }

    /// <remarks/>
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(GSITransport))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(GSISecureConversation))]
    [System.Xml.Serialization.XmlIncludeAttribute(typeof(GSISecureMessage))]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security")]
    public partial class CommunicationStyle : object, System.ComponentModel.INotifyPropertyChanged
    {

        private protectionLevelType protectionLevelField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute()]
        public protectionLevelType protectionLevel
        {
            get
            {
                return this.protectionLevelField;
            }
            set
            {
                this.protectionLevelField = value;
                this.RaisePropertyChanged("protectionLevel");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security")]
    public enum protectionLevelType
    {

        /// <remarks/>
        integrity,

        /// <remarks/>
        privacy,

        /// <remarks/>
        either,
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security")]
    public partial class GSISecureConversation : CommunicationStyle
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security")]
    public partial class GSISecureMessage : CommunicationStyle
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security")]
    public partial class None : object, System.ComponentModel.INotifyPropertyChanged
    {

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security")]
    public partial class ServiceSecurityMetadata : object, System.ComponentModel.INotifyPropertyChanged
    {

        private CommunicationMechanism defaultCommunicationMechanismField;

        private Operation[] operationsField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 0)]
        public CommunicationMechanism defaultCommunicationMechanism
        {
            get
            {
                return this.defaultCommunicationMechanismField;
            }
            set
            {
                this.defaultCommunicationMechanismField = value;
                this.RaisePropertyChanged("defaultCommunicationMechanism");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlArrayAttribute(Order = 1)]
        [System.Xml.Serialization.XmlArrayItemAttribute(IsNullable = false)]
        public Operation[] operations
        {
            get
            {
                return this.operationsField;
            }
            set
            {
                this.operationsField = value;
                this.RaisePropertyChanged("operations");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://transfer.cagrid.org/Transfer")]
    public partial class DataStorageDescriptor : object, System.ComponentModel.INotifyPropertyChanged
    {

        private string locationField;

        private string userDNField;

        private bool deleteOnDestroyField;

        private Status statusField;

        private DataDescriptor dataDescriptorField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Form = System.Xml.Schema.XmlSchemaForm.Unqualified, Order = 0)]
        public string location
        {
            get
            {
                return this.locationField;
            }
            set
            {
                this.locationField = value;
                this.RaisePropertyChanged("location");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Form = System.Xml.Schema.XmlSchemaForm.Unqualified, Order = 1)]
        public string userDN
        {
            get
            {
                return this.userDNField;
            }
            set
            {
                this.userDNField = value;
                this.RaisePropertyChanged("userDN");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Form = System.Xml.Schema.XmlSchemaForm.Unqualified, Order = 2)]
        public bool deleteOnDestroy
        {
            get
            {
                return this.deleteOnDestroyField;
            }
            set
            {
                this.deleteOnDestroyField = value;
                this.RaisePropertyChanged("deleteOnDestroy");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 3)]
        public Status Status
        {
            get
            {
                return this.statusField;
            }
            set
            {
                this.statusField = value;
                this.RaisePropertyChanged("Status");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 4)]
        public DataDescriptor DataDescriptor
        {
            get
            {
                return this.dataDescriptorField;
            }
            set
            {
                this.dataDescriptorField = value;
                this.RaisePropertyChanged("DataDescriptor");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://transfer.cagrid.org/Transfer")]
    public enum Status
    {

        /// <remarks/>
        Staging,

        /// <remarks/>
        Staged,
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://transfer.cagrid.org/Transfer")]
    public partial class DataDescriptor : object, System.ComponentModel.INotifyPropertyChanged
    {

        private string nameField;

        private object metadataField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Form = System.Xml.Schema.XmlSchemaForm.Unqualified, Order = 0)]
        public string name
        {
            get
            {
                return this.nameField;
            }
            set
            {
                this.nameField = value;
                this.RaisePropertyChanged("name");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Form = System.Xml.Schema.XmlSchemaForm.Unqualified, Order = 1)]
        public object metadata
        {
            get
            {
                return this.metadataField;
            }
            set
            {
                this.metadataField = value;
                this.RaisePropertyChanged("metadata");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class TopicExpressionType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlNode[] anyField;

        private string dialectField;

        /// <remarks/>
        [System.Xml.Serialization.XmlTextAttribute()]
        [System.Xml.Serialization.XmlAnyElementAttribute(Order = 0)]
        public System.Xml.XmlNode[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
                this.RaisePropertyChanged("Any");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute(DataType = "anyURI")]
        public string Dialect
        {
            get
            {
                return this.dialectField;
            }
            set
            {
                this.dialectField = value;
                this.RaisePropertyChanged("Dialect");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class NotificationMessageHolderType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private TopicExpressionType topicField;

        private EndpointReferenceType producerReferenceField;

        private object messageField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 0)]
        public TopicExpressionType Topic
        {
            get
            {
                return this.topicField;
            }
            set
            {
                this.topicField = value;
                this.RaisePropertyChanged("Topic");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 1)]
        public EndpointReferenceType ProducerReference
        {
            get
            {
                return this.producerReferenceField;
            }
            set
            {
                this.producerReferenceField = value;
                this.RaisePropertyChanged("ProducerReference");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 2)]
        public object Message
        {
            get
            {
                return this.messageField;
            }
            set
            {
                this.messageField = value;
                this.RaisePropertyChanged("Message");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class DeleteType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlQualifiedName resourcePropertyField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute()]
        public System.Xml.XmlQualifiedName ResourceProperty
        {
            get
            {
                return this.resourcePropertyField;
            }
            set
            {
                this.resourcePropertyField = value;
                this.RaisePropertyChanged("ResourceProperty");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class UpdateType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlElement[] anyField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Order = 0)]
        public System.Xml.XmlElement[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
                this.RaisePropertyChanged("Any");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class InsertType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlElement[] anyField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Order = 0)]
        public System.Xml.XmlElement[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
                this.RaisePropertyChanged("Any");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://schemas.xmlsoap.org/ws/2004/03/addressing")]
    public partial class ServiceNameType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private string portNameField;

        private System.Xml.XmlAttribute[] anyAttrField;

        private System.Xml.XmlQualifiedName valueField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute(DataType = "NCName")]
        public string PortName
        {
            get
            {
                return this.portNameField;
            }
            set
            {
                this.portNameField = value;
                this.RaisePropertyChanged("PortName");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyAttributeAttribute()]
        public System.Xml.XmlAttribute[] AnyAttr
        {
            get
            {
                return this.anyAttrField;
            }
            set
            {
                this.anyAttrField = value;
                this.RaisePropertyChanged("AnyAttr");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlTextAttribute()]
        public System.Xml.XmlQualifiedName Value
        {
            get
            {
                return this.valueField;
            }
            set
            {
                this.valueField = value;
                this.RaisePropertyChanged("Value");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://schemas.xmlsoap.org/ws/2004/03/addressing")]
    public partial class AttributedQName : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlAttribute[] anyAttrField;

        private System.Xml.XmlQualifiedName valueField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyAttributeAttribute()]
        public System.Xml.XmlAttribute[] AnyAttr
        {
            get
            {
                return this.anyAttrField;
            }
            set
            {
                this.anyAttrField = value;
                this.RaisePropertyChanged("AnyAttr");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlTextAttribute()]
        public System.Xml.XmlQualifiedName Value
        {
            get
            {
                return this.valueField;
            }
            set
            {
                this.valueField = value;
                this.RaisePropertyChanged("Value");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://schemas.xmlsoap.org/ws/2004/03/addressing")]
    public partial class ReferencePropertiesType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlElement[] anyField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Order = 0)]
        public System.Xml.XmlElement[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
                this.RaisePropertyChanged("Any");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class QueryExpressionType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlNode[] anyField;

        private string dialectField;

        /// <remarks/>
        [System.Xml.Serialization.XmlTextAttribute()]
        [System.Xml.Serialization.XmlAnyElementAttribute(Order = 0)]
        public System.Xml.XmlNode[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
                this.RaisePropertyChanged("Any");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute(DataType = "anyURI")]
        public string Dialect
        {
            get
            {
                return this.dialectField;
            }
            set
            {
                this.dialectField = value;
                this.RaisePropertyChanged("Dialect");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class ResourcePropertyValueChangeNotificationType : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlElement oldValueField;

        private System.Xml.XmlElement newValueField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(IsNullable = true, Order = 0)]
        public System.Xml.XmlElement OldValue
        {
            get
            {
                return this.oldValueField;
            }
            set
            {
                this.oldValueField = value;
                this.RaisePropertyChanged("OldValue");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(IsNullable = true, Order = 1)]
        public System.Xml.XmlElement NewValue
        {
            get
            {
                return this.newValueField;
            }
            set
            {
                this.newValueField = value;
                this.RaisePropertyChanged("NewValue");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://transfer.cagrid.org/Transfer")]
    public partial class DataTransferDescriptor : object, System.ComponentModel.INotifyPropertyChanged
    {

        private string urlField;

        private DataDescriptor dataDescriptorField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Form = System.Xml.Schema.XmlSchemaForm.Unqualified, Order = 0)]
        public string url
        {
            get
            {
                return this.urlField;
            }
            set
            {
                this.urlField = value;
                this.RaisePropertyChanged("url");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 1)]
        public DataDescriptor DataDescriptor
        {
            get
            {
                return this.dataDescriptorField;
            }
            set
            {
                this.dataDescriptorField = value;
                this.RaisePropertyChanged("DataDescriptor");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-BaseFaults-1.2-draft-01.xsd")]
    public partial class BaseFaultTypeErrorCode : object, System.ComponentModel.INotifyPropertyChanged
    {

        private string dialectField;

        private string[] textField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute(DataType = "anyURI")]
        public string dialect
        {
            get
            {
                return this.dialectField;
            }
            set
            {
                this.dialectField = value;
                this.RaisePropertyChanged("dialect");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlTextAttribute()]
        public string[] Text
        {
            get
            {
                return this.textField;
            }
            set
            {
                this.textField = value;
                this.RaisePropertyChanged("Text");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-BaseFaults-1.2-draft-01.xsd")]
    public partial class BaseFaultTypeDescription : object, System.ComponentModel.INotifyPropertyChanged
    {

        private string langField;

        private string valueField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAttributeAttribute(Form = System.Xml.Schema.XmlSchemaForm.Qualified, Namespace = "http://www.w3.org/XML/1998/namespace")]
        public string lang
        {
            get
            {
                return this.langField;
            }
            set
            {
                this.langField = value;
                this.RaisePropertyChanged("lang");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlTextAttribute()]
        public string Value
        {
            get
            {
                return this.valueField;
            }
            set
            {
                this.valueField = value;
                this.RaisePropertyChanged("Value");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
        "")]
    public partial class TerminationTimeChangeRejectedFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
        "")]
    public partial class UnableToSetTerminationTimeFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(TypeName = "ResourceUnknownFaultType", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
        "")]
    public partial class ResourceUnknownFaultType2 : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class ResumeFailedFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class PauseFailedFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class NoCurrentMessageOnTopicFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class TopicNotSupportedFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class InvalidTopicExpressionFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class TopicPathDialectUnknownFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class SubscribeCreationFailedFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(TypeName = "ResourceUnknownFaultType", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class ResourceUnknownFaultType1 : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class QueryEvaluationErrorFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class InvalidQueryExpressionFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class UnknownQueryExpressionDialectFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class SetResourcePropertyRequestFailedFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class UnableToModifyResourcePropertyFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class InvalidSetResourcePropertiesRequestContentFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class InvalidResourcePropertyQNameFaultType : BaseFaultType
    {
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class ResourceUnknownFaultType : BaseFaultType
    {
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://transfer.cagrid.org/TransferService/Context", ConfigurationName = "TransferServiceContextService.TransferServiceContextPortType")]
    public interface TransferServiceContextPortType
    {

        // CODEGEN: Generating message contract since the wrapper name (GetDataTransferDescriptorRequest) of message getDataTransferDescriptorRequest does not match the default value (getDataTransferDescriptor)
        [System.ServiceModel.OperationContractAttribute(Action = "http://transfer.cagrid.org/TransferService/Context/GetDataTransferDescriptorReque" +
            "st", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.getDataTransferDescriptorResponse getDataTransferDescriptor(TransferServiceContextService.getDataTransferDescriptorRequest request);

        // CODEGEN: Generating message contract since the wrapper name (GetStatusRequest) of message getStatusRequest does not match the default value (getStatus)
        [System.ServiceModel.OperationContractAttribute(Action = "http://transfer.cagrid.org/TransferService/Context/GetStatusRequest", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.getStatusResponse getStatus(TransferServiceContextService.getStatusRequest request);

        // CODEGEN: Generating message contract since the wrapper name (SetStatusRequest) of message setStatusRequest does not match the default value (setStatus)
        [System.ServiceModel.OperationContractAttribute(Action = "http://transfer.cagrid.org/TransferService/Context/SetStatusRequest", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.setStatusResponse setStatus(TransferServiceContextService.setStatusRequest request);

        // CODEGEN: Generating message contract since the wrapper namespace (http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity) of message getServiceSecurityMetadataRequest does not match the default value (http://transfer.cagrid.org/TransferService/Context)
        [System.ServiceModel.OperationContractAttribute(Action = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity/GetServiceSecurityMe" +
            "tadataRequest", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.getServiceSecurityMetadataResponse getServiceSecurityMetadata(TransferServiceContextService.getServiceSecurityMetadataRequest request);

        // CODEGEN: Generating message contract since the operation Destroy is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime/Destroy", ReplyAction = "*")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceNotDestroyedFaultType), Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime/Destroy", Name = "ResourceNotDestroyedFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType2), Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime/Destroy", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.DestroyResponse1 Destroy(TransferServiceContextService.DestroyRequest request);

        // CODEGEN: Generating message contract since the operation SetTerminationTime is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime/SetTerminationTi" +
            "me", ReplyAction = "*")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.UnableToSetTerminationTimeFaultType), Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime/SetTerminationTi" +
            "me", Name = "UnableToSetTerminationTimeFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType2), Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime/SetTerminationTi" +
            "me", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.TerminationTimeChangeRejectedFaultType), Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime/SetTerminationTi" +
            "me", Name = "TerminationTimeChangeRejectedFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.SetTerminationTimeResponse1 SetTerminationTime(TransferServiceContextService.SetTerminationTimeRequest request);

        // CODEGEN: Generating message contract since the operation Subscribe is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification/Subscribe", ReplyAction = "*")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType1), Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification/Subscribe", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.SubscribeCreationFailedFaultType), Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification/Subscribe", Name = "SubscribeCreationFailedFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.TopicPathDialectUnknownFaultType), Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification/Subscribe", Name = "TopicPathDialectUnknownFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidTopicExpressionFaultType), Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification/Subscribe", Name = "InvalidTopicExpressionFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.TopicNotSupportedFaultType), Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification/Subscribe", Name = "TopicNotSupportedFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.SubscribeResponse1 Subscribe(TransferServiceContextService.SubscribeRequest request);
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName = "GetDataTransferDescriptorRequest", WrapperNamespace = "http://transfer.cagrid.org/TransferService/Context", IsWrapped = true)]
    public partial class getDataTransferDescriptorRequest
    {

        public getDataTransferDescriptorRequest()
        {
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName = "GetDataTransferDescriptorResponse", WrapperNamespace = "http://transfer.cagrid.org/TransferService/Context", IsWrapped = true)]
    public partial class getDataTransferDescriptorResponse
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://transfer.cagrid.org/Transfer", Order = 0)]
        public TransferServiceContextService.DataTransferDescriptor DataTransferDescriptor;

        public getDataTransferDescriptorResponse()
        {
        }

        public getDataTransferDescriptorResponse(TransferServiceContextService.DataTransferDescriptor DataTransferDescriptor)
        {
            this.DataTransferDescriptor = DataTransferDescriptor;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName = "GetStatusRequest", WrapperNamespace = "http://transfer.cagrid.org/TransferService/Context", IsWrapped = true)]
    public partial class getStatusRequest
    {

        public getStatusRequest()
        {
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName = "GetStatusResponse", WrapperNamespace = "http://transfer.cagrid.org/TransferService/Context", IsWrapped = true)]
    public partial class getStatusResponse
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://transfer.cagrid.org/Transfer", Order = 0)]
        public TransferServiceContextService.Status Status;

        public getStatusResponse()
        {
        }

        public getStatusResponse(TransferServiceContextService.Status Status)
        {
            this.Status = Status;
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://transfer.cagrid.org/TransferService/Context")]
    public partial class SetStatusRequestStatus : object, System.ComponentModel.INotifyPropertyChanged
    {

        private Status statusField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Namespace = "http://transfer.cagrid.org/Transfer", Order = 0)]
        public Status Status
        {
            get
            {
                return this.statusField;
            }
            set
            {
                this.statusField = value;
                this.RaisePropertyChanged("Status");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName = "SetStatusRequest", WrapperNamespace = "http://transfer.cagrid.org/TransferService/Context", IsWrapped = true)]
    public partial class setStatusRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://transfer.cagrid.org/TransferService/Context", Order = 0)]
        public TransferServiceContextService.SetStatusRequestStatus status;

        public setStatusRequest()
        {
        }

        public setStatusRequest(TransferServiceContextService.SetStatusRequestStatus status)
        {
            this.status = status;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName = "SetStatusResponse", WrapperNamespace = "http://transfer.cagrid.org/TransferService/Context", IsWrapped = true)]
    public partial class setStatusResponse
    {

        public setStatusResponse()
        {
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName = "GetServiceSecurityMetadataRequest", WrapperNamespace = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity", IsWrapped = true)]
    public partial class getServiceSecurityMetadataRequest
    {

        public getServiceSecurityMetadataRequest()
        {
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(WrapperName = "GetServiceSecurityMetadataResponse", WrapperNamespace = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity", IsWrapped = true)]
    public partial class getServiceSecurityMetadataResponse
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "gme://caGrid.caBIG/1.0/gov.nih.nci.cagrid.metadata.security", Order = 0)]
        public TransferServiceContextService.ServiceSecurityMetadata ServiceSecurityMetadata;

        public getServiceSecurityMetadataResponse()
        {
        }

        public getServiceSecurityMetadataResponse(TransferServiceContextService.ServiceSecurityMetadata ServiceSecurityMetadata)
        {
            this.ServiceSecurityMetadata = ServiceSecurityMetadata;
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
        "")]
    public partial class Destroy : object, System.ComponentModel.INotifyPropertyChanged
    {

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
        "")]
    public partial class DestroyResponse : object, System.ComponentModel.INotifyPropertyChanged
    {

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class DestroyRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "", Order = 0)]
        public TransferServiceContextService.Destroy Destroy;

        public DestroyRequest()
        {
        }

        public DestroyRequest(TransferServiceContextService.Destroy Destroy)
        {
            this.Destroy = Destroy;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class DestroyResponse1
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "", Order = 0)]
        public TransferServiceContextService.DestroyResponse DestroyResponse;

        public DestroyResponse1()
        {
        }

        public DestroyResponse1(TransferServiceContextService.DestroyResponse DestroyResponse)
        {
            this.DestroyResponse = DestroyResponse;
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
        "")]
    public partial class SetTerminationTime : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Nullable<System.DateTime> requestedTerminationTimeField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(IsNullable = true, Order = 0)]
        public System.Nullable<System.DateTime> RequestedTerminationTime
        {
            get
            {
                return this.requestedTerminationTimeField;
            }
            set
            {
                this.requestedTerminationTimeField = value;
                this.RaisePropertyChanged("RequestedTerminationTime");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
        "")]
    public partial class SetTerminationTimeResponse : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Nullable<System.DateTime> newTerminationTimeField;

        private System.DateTime currentTimeField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(IsNullable = true, Order = 0)]
        public System.Nullable<System.DateTime> NewTerminationTime
        {
            get
            {
                return this.newTerminationTimeField;
            }
            set
            {
                this.newTerminationTimeField = value;
                this.RaisePropertyChanged("NewTerminationTime");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 1)]
        public System.DateTime CurrentTime
        {
            get
            {
                return this.currentTimeField;
            }
            set
            {
                this.currentTimeField = value;
                this.RaisePropertyChanged("CurrentTime");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class SetTerminationTimeRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "", Order = 0)]
        public TransferServiceContextService.SetTerminationTime SetTerminationTime;

        public SetTerminationTimeRequest()
        {
        }

        public SetTerminationTimeRequest(TransferServiceContextService.SetTerminationTime SetTerminationTime)
        {
            this.SetTerminationTime = SetTerminationTime;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class SetTerminationTimeResponse1
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "", Order = 0)]
        public TransferServiceContextService.SetTerminationTimeResponse SetTerminationTimeResponse;

        public SetTerminationTimeResponse1()
        {
        }

        public SetTerminationTimeResponse1(TransferServiceContextService.SetTerminationTimeResponse SetTerminationTimeResponse)
        {
            this.SetTerminationTimeResponse = SetTerminationTimeResponse;
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class Subscribe : object, System.ComponentModel.INotifyPropertyChanged
    {

        private EndpointReferenceType consumerReferenceField;

        private TopicExpressionType topicExpressionField;

        private bool useNotifyField;

        private QueryExpressionType preconditionField;

        private QueryExpressionType selectorField;

        private object subscriptionPolicyField;

        private System.DateTime initialTerminationTimeField;

        private bool initialTerminationTimeFieldSpecified;

        public Subscribe()
        {
            this.useNotifyField = true;
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 0)]
        public EndpointReferenceType ConsumerReference
        {
            get
            {
                return this.consumerReferenceField;
            }
            set
            {
                this.consumerReferenceField = value;
                this.RaisePropertyChanged("ConsumerReference");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 1)]
        public TopicExpressionType TopicExpression
        {
            get
            {
                return this.topicExpressionField;
            }
            set
            {
                this.topicExpressionField = value;
                this.RaisePropertyChanged("TopicExpression");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 2)]
        [System.ComponentModel.DefaultValueAttribute(true)]
        public bool UseNotify
        {
            get
            {
                return this.useNotifyField;
            }
            set
            {
                this.useNotifyField = value;
                this.RaisePropertyChanged("UseNotify");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 3)]
        public QueryExpressionType Precondition
        {
            get
            {
                return this.preconditionField;
            }
            set
            {
                this.preconditionField = value;
                this.RaisePropertyChanged("Precondition");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 4)]
        public QueryExpressionType Selector
        {
            get
            {
                return this.selectorField;
            }
            set
            {
                this.selectorField = value;
                this.RaisePropertyChanged("Selector");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 5)]
        public object SubscriptionPolicy
        {
            get
            {
                return this.subscriptionPolicyField;
            }
            set
            {
                this.subscriptionPolicyField = value;
                this.RaisePropertyChanged("SubscriptionPolicy");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 6)]
        public System.DateTime InitialTerminationTime
        {
            get
            {
                return this.initialTerminationTimeField;
            }
            set
            {
                this.initialTerminationTimeField = value;
                this.RaisePropertyChanged("InitialTerminationTime");
            }
        }

        /// <remarks/>
        [System.Xml.Serialization.XmlIgnoreAttribute()]
        public bool InitialTerminationTimeSpecified
        {
            get
            {
                return this.initialTerminationTimeFieldSpecified;
            }
            set
            {
                this.initialTerminationTimeFieldSpecified = value;
                this.RaisePropertyChanged("InitialTerminationTimeSpecified");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class SubscribeResponse : object, System.ComponentModel.INotifyPropertyChanged
    {

        private EndpointReferenceType subscriptionReferenceField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 0)]
        public EndpointReferenceType SubscriptionReference
        {
            get
            {
                return this.subscriptionReferenceField;
            }
            set
            {
                this.subscriptionReferenceField = value;
                this.RaisePropertyChanged("SubscriptionReference");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class SubscribeRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd", Order = 0)]
        public TransferServiceContextService.Subscribe Subscribe;

        public SubscribeRequest()
        {
        }

        public SubscribeRequest(TransferServiceContextService.Subscribe Subscribe)
        {
            this.Subscribe = Subscribe;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class SubscribeResponse1
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd", Order = 0)]
        public TransferServiceContextService.SubscribeResponse SubscribeResponse;

        public SubscribeResponse1()
        {
        }

        public SubscribeResponse1(TransferServiceContextService.SubscribeResponse SubscribeResponse)
        {
            this.SubscribeResponse = SubscribeResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface TransferServiceContextPortTypeChannel : TransferServiceContextService.TransferServiceContextPortType, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class TransferServiceContextPortTypeClient : System.ServiceModel.ClientBase<TransferServiceContextService.TransferServiceContextPortType>, TransferServiceContextService.TransferServiceContextPortType
    {

        public TransferServiceContextPortTypeClient()
        {
        }

        public TransferServiceContextPortTypeClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public TransferServiceContextPortTypeClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public TransferServiceContextPortTypeClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public TransferServiceContextPortTypeClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.getDataTransferDescriptorResponse TransferServiceContextService.TransferServiceContextPortType.getDataTransferDescriptor(TransferServiceContextService.getDataTransferDescriptorRequest request)
        {
            return base.Channel.getDataTransferDescriptor(request);
        }

        public TransferServiceContextService.DataTransferDescriptor getDataTransferDescriptor()
        {
            TransferServiceContextService.getDataTransferDescriptorRequest inValue = new TransferServiceContextService.getDataTransferDescriptorRequest();
            TransferServiceContextService.getDataTransferDescriptorResponse retVal = ((TransferServiceContextService.TransferServiceContextPortType)(this)).getDataTransferDescriptor(inValue);
            return retVal.DataTransferDescriptor;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.getStatusResponse TransferServiceContextService.TransferServiceContextPortType.getStatus(TransferServiceContextService.getStatusRequest request)
        {
            return base.Channel.getStatus(request);
        }

        public TransferServiceContextService.Status getStatus()
        {
            TransferServiceContextService.getStatusRequest inValue = new TransferServiceContextService.getStatusRequest();
            TransferServiceContextService.getStatusResponse retVal = ((TransferServiceContextService.TransferServiceContextPortType)(this)).getStatus(inValue);
            return retVal.Status;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.setStatusResponse TransferServiceContextService.TransferServiceContextPortType.setStatus(TransferServiceContextService.setStatusRequest request)
        {
            return base.Channel.setStatus(request);
        }

        public void setStatus(TransferServiceContextService.SetStatusRequestStatus status)
        {
            TransferServiceContextService.setStatusRequest inValue = new TransferServiceContextService.setStatusRequest();
            inValue.status = status;
            TransferServiceContextService.setStatusResponse retVal = ((TransferServiceContextService.TransferServiceContextPortType)(this)).setStatus(inValue);
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.getServiceSecurityMetadataResponse TransferServiceContextService.TransferServiceContextPortType.getServiceSecurityMetadata(TransferServiceContextService.getServiceSecurityMetadataRequest request)
        {
            return base.Channel.getServiceSecurityMetadata(request);
        }

        public TransferServiceContextService.ServiceSecurityMetadata getServiceSecurityMetadata()
        {
            TransferServiceContextService.getServiceSecurityMetadataRequest inValue = new TransferServiceContextService.getServiceSecurityMetadataRequest();
            TransferServiceContextService.getServiceSecurityMetadataResponse retVal = ((TransferServiceContextService.TransferServiceContextPortType)(this)).getServiceSecurityMetadata(inValue);
            return retVal.ServiceSecurityMetadata;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.DestroyResponse1 TransferServiceContextService.TransferServiceContextPortType.Destroy(TransferServiceContextService.DestroyRequest request)
        {
            return base.Channel.Destroy(request);
        }

        public TransferServiceContextService.DestroyResponse Destroy(TransferServiceContextService.Destroy Destroy1)
        {
            TransferServiceContextService.DestroyRequest inValue = new TransferServiceContextService.DestroyRequest();
            inValue.Destroy = Destroy1;
            TransferServiceContextService.DestroyResponse1 retVal = ((TransferServiceContextService.TransferServiceContextPortType)(this)).Destroy(inValue);
            return retVal.DestroyResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.SetTerminationTimeResponse1 TransferServiceContextService.TransferServiceContextPortType.SetTerminationTime(TransferServiceContextService.SetTerminationTimeRequest request)
        {
            return base.Channel.SetTerminationTime(request);
        }

        public TransferServiceContextService.SetTerminationTimeResponse SetTerminationTime(TransferServiceContextService.SetTerminationTime SetTerminationTime1)
        {
            TransferServiceContextService.SetTerminationTimeRequest inValue = new TransferServiceContextService.SetTerminationTimeRequest();
            inValue.SetTerminationTime = SetTerminationTime1;
            TransferServiceContextService.SetTerminationTimeResponse1 retVal = ((TransferServiceContextService.TransferServiceContextPortType)(this)).SetTerminationTime(inValue);
            return retVal.SetTerminationTimeResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.SubscribeResponse1 TransferServiceContextService.TransferServiceContextPortType.Subscribe(TransferServiceContextService.SubscribeRequest request)
        {
            return base.Channel.Subscribe(request);
        }

        public TransferServiceContextService.SubscribeResponse Subscribe(TransferServiceContextService.Subscribe Subscribe1)
        {
            TransferServiceContextService.SubscribeRequest inValue = new TransferServiceContextService.SubscribeRequest();
            inValue.Subscribe = Subscribe1;
            TransferServiceContextService.SubscribeResponse1 retVal = ((TransferServiceContextService.TransferServiceContextPortType)(this)).Subscribe(inValue);
            return retVal.SubscribeResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl", ConfigurationName = "TransferServiceContextService.NotificationConsumer")]
    public interface NotificationConsumer
    {

        // CODEGEN: Generating message contract since the operation Notify is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(IsOneWay = true, Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "NotificationConsumer/Notify")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        void Notify(TransferServiceContextService.Notify request);
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class Notify
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Name = "Notify", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd", Order = 0)]
        [System.Xml.Serialization.XmlArrayItemAttribute("NotificationMessage", IsNullable = false)]
        public NotificationMessageHolderType[] Notify1;

        public Notify()
        {
        }

        public Notify(NotificationMessageHolderType[] Notify1)
        {
            this.Notify1 = Notify1;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface NotificationConsumerChannel : TransferServiceContextService.NotificationConsumer, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class NotificationConsumerClient : System.ServiceModel.ClientBase<TransferServiceContextService.NotificationConsumer>, TransferServiceContextService.NotificationConsumer
    {

        public NotificationConsumerClient()
        {
        }

        public NotificationConsumerClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public NotificationConsumerClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public NotificationConsumerClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public NotificationConsumerClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        void TransferServiceContextService.NotificationConsumer.Notify(TransferServiceContextService.Notify request)
        {
            base.Channel.Notify(request);
        }

        public void Notify(NotificationMessageHolderType[] Notify1)
        {
            TransferServiceContextService.Notify inValue = new TransferServiceContextService.Notify();
            inValue.Notify1 = Notify1;
            ((TransferServiceContextService.NotificationConsumer)(this)).Notify(inValue);
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl", ConfigurationName = "TransferServiceContextService.NotificationProducer")]
    public interface NotificationProducer
    {

        // CODEGEN: Generating message contract since the operation GetResourceProperty is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "NotificationProducer/GetResourcePropertyRequest", ReplyAction = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "NotificationProducer/GetResourcePropertyResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidResourcePropertyQNameFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidResourcePropertyQNameFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.GetResourcePropertyResponse1 GetResourceProperty(TransferServiceContextService.GetResourcePropertyRequest request);

        // CODEGEN: Generating message contract since the operation Subscribe is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "NotificationProducer/SubscribeRequest", ReplyAction = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "NotificationProducer/SubscribeResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType1), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.SubscribeCreationFailedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "SubscribeCreationFailedFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.TopicPathDialectUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "TopicPathDialectUnknownFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidTopicExpressionFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidTopicExpressionFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.TopicNotSupportedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "TopicNotSupportedFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.SubscribeResponse1 Subscribe(TransferServiceContextService.SubscribeRequest request);

        // CODEGEN: Generating message contract since the operation GetCurrentMessage is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "NotificationProducer/GetCurrentMessageRequest", ReplyAction = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "NotificationProducer/GetCurrentMessageResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType1), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidTopicExpressionFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidTopicExpressionFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.TopicNotSupportedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "TopicNotSupportedFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.NoCurrentMessageOnTopicFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "NoCurrentMessageOnTopicFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.GetCurrentMessageResponse GetCurrentMessage(TransferServiceContextService.GetCurrentMessageRequest request);
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class GetResourcePropertyResponse : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlElement[] anyField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Order = 0)]
        public System.Xml.XmlElement[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
                this.RaisePropertyChanged("Any");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class GetResourcePropertyRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd", Order = 0)]
        public System.Xml.XmlQualifiedName GetResourceProperty;

        public GetResourcePropertyRequest()
        {
        }

        public GetResourcePropertyRequest(System.Xml.XmlQualifiedName GetResourceProperty)
        {
            this.GetResourceProperty = GetResourceProperty;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class GetResourcePropertyResponse1
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd", Order = 0)]
        public TransferServiceContextService.GetResourcePropertyResponse GetResourcePropertyResponse;

        public GetResourcePropertyResponse1()
        {
        }

        public GetResourcePropertyResponse1(TransferServiceContextService.GetResourcePropertyResponse GetResourcePropertyResponse)
        {
            this.GetResourcePropertyResponse = GetResourcePropertyResponse;
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class GetCurrentMessage : object, System.ComponentModel.INotifyPropertyChanged
    {

        private TopicExpressionType topicField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 0)]
        public TopicExpressionType Topic
        {
            get
            {
                return this.topicField;
            }
            set
            {
                this.topicField = value;
                this.RaisePropertyChanged("Topic");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class GetCurrentMessageRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd", Order = 0)]
        public TransferServiceContextService.GetCurrentMessage GetCurrentMessage;

        public GetCurrentMessageRequest()
        {
        }

        public GetCurrentMessageRequest(TransferServiceContextService.GetCurrentMessage GetCurrentMessage)
        {
            this.GetCurrentMessage = GetCurrentMessage;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class GetCurrentMessageResponse
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Name = "GetCurrentMessageResponse", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd", Order = 0)]
        public System.Xml.XmlElement GetCurrentMessageResponse1;

        public GetCurrentMessageResponse()
        {
        }

        public GetCurrentMessageResponse(System.Xml.XmlElement GetCurrentMessageResponse1)
        {
            this.GetCurrentMessageResponse1 = GetCurrentMessageResponse1;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface NotificationProducerChannel : TransferServiceContextService.NotificationProducer, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class NotificationProducerClient : System.ServiceModel.ClientBase<TransferServiceContextService.NotificationProducer>, TransferServiceContextService.NotificationProducer
    {

        public NotificationProducerClient()
        {
        }

        public NotificationProducerClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public NotificationProducerClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public NotificationProducerClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public NotificationProducerClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.GetResourcePropertyResponse1 TransferServiceContextService.NotificationProducer.GetResourceProperty(TransferServiceContextService.GetResourcePropertyRequest request)
        {
            return base.Channel.GetResourceProperty(request);
        }

        public TransferServiceContextService.GetResourcePropertyResponse GetResourceProperty(System.Xml.XmlQualifiedName GetResourceProperty1)
        {
            TransferServiceContextService.GetResourcePropertyRequest inValue = new TransferServiceContextService.GetResourcePropertyRequest();
            inValue.GetResourceProperty = GetResourceProperty1;
            TransferServiceContextService.GetResourcePropertyResponse1 retVal = ((TransferServiceContextService.NotificationProducer)(this)).GetResourceProperty(inValue);
            return retVal.GetResourcePropertyResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.SubscribeResponse1 TransferServiceContextService.NotificationProducer.Subscribe(TransferServiceContextService.SubscribeRequest request)
        {
            return base.Channel.Subscribe(request);
        }

        public TransferServiceContextService.SubscribeResponse Subscribe(TransferServiceContextService.Subscribe Subscribe1)
        {
            TransferServiceContextService.SubscribeRequest inValue = new TransferServiceContextService.SubscribeRequest();
            inValue.Subscribe = Subscribe1;
            TransferServiceContextService.SubscribeResponse1 retVal = ((TransferServiceContextService.NotificationProducer)(this)).Subscribe(inValue);
            return retVal.SubscribeResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.GetCurrentMessageResponse TransferServiceContextService.NotificationProducer.GetCurrentMessage(TransferServiceContextService.GetCurrentMessageRequest request)
        {
            return base.Channel.GetCurrentMessage(request);
        }

        public System.Xml.XmlElement GetCurrentMessage(TransferServiceContextService.GetCurrentMessage GetCurrentMessage1)
        {
            TransferServiceContextService.GetCurrentMessageRequest inValue = new TransferServiceContextService.GetCurrentMessageRequest();
            inValue.GetCurrentMessage = GetCurrentMessage1;
            TransferServiceContextService.GetCurrentMessageResponse retVal = ((TransferServiceContextService.NotificationProducer)(this)).GetCurrentMessage(inValue);
            return retVal.GetCurrentMessageResponse1;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl", ConfigurationName = "TransferServiceContextService.SubscriptionManager")]
    public interface SubscriptionManager
    {

        // CODEGEN: Generating message contract since the operation GetResourceProperty is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/GetResourcePropertyRequest", ReplyAction = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/GetResourcePropertyResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidResourcePropertyQNameFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidResourcePropertyQNameFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.GetResourcePropertyResponse1 GetResourceProperty(TransferServiceContextService.GetResourcePropertyRequest request);

        // CODEGEN: Generating message contract since the operation Destroy is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/DestroyRequest", ReplyAction = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/DestroyResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType2), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceNotDestroyedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceNotDestroyedFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.DestroyResponse1 Destroy(TransferServiceContextService.DestroyRequest request);

        // CODEGEN: Generating message contract since the operation SetTerminationTime is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/SetTerminationTimeRequest", ReplyAction = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/SetTerminationTimeResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType2), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.UnableToSetTerminationTimeFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "UnableToSetTerminationTimeFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.TerminationTimeChangeRejectedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "TerminationTimeChangeRejectedFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.SetTerminationTimeResponse1 SetTerminationTime(TransferServiceContextService.SetTerminationTimeRequest request);

        // CODEGEN: Generating message contract since the operation PauseSubscription is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/PauseSubscriptionRequest", ReplyAction = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/PauseSubscriptionResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType1), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.PauseFailedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "PauseFailedFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.PauseSubscriptionResponse1 PauseSubscription(TransferServiceContextService.PauseSubscriptionRequest request);

        // CODEGEN: Generating message contract since the operation ResumeSubscription is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/ResumeSubscriptionRequest", ReplyAction = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.wsdl/" +
            "SubscriptionManager/ResumeSubscriptionResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType1), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResumeFailedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResumeFailedFault", Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.ResumeSubscriptionResponse1 ResumeSubscription(TransferServiceContextService.ResumeSubscriptionRequest request);
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class PauseSubscription : object, System.ComponentModel.INotifyPropertyChanged
    {

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class PauseSubscriptionResponse : object, System.ComponentModel.INotifyPropertyChanged
    {

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class PauseSubscriptionRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd", Order = 0)]
        public TransferServiceContextService.PauseSubscription PauseSubscription;

        public PauseSubscriptionRequest()
        {
        }

        public PauseSubscriptionRequest(TransferServiceContextService.PauseSubscription PauseSubscription)
        {
            this.PauseSubscription = PauseSubscription;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class PauseSubscriptionResponse1
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd", Order = 0)]
        public TransferServiceContextService.PauseSubscriptionResponse PauseSubscriptionResponse;

        public PauseSubscriptionResponse1()
        {
        }

        public PauseSubscriptionResponse1(TransferServiceContextService.PauseSubscriptionResponse PauseSubscriptionResponse)
        {
            this.PauseSubscriptionResponse = PauseSubscriptionResponse;
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class ResumeSubscription : object, System.ComponentModel.INotifyPropertyChanged
    {

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd")]
    public partial class ResumeSubscriptionResponse : object, System.ComponentModel.INotifyPropertyChanged
    {

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class ResumeSubscriptionRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd", Order = 0)]
        public TransferServiceContextService.ResumeSubscription ResumeSubscription;

        public ResumeSubscriptionRequest()
        {
        }

        public ResumeSubscriptionRequest(TransferServiceContextService.ResumeSubscription ResumeSubscription)
        {
            this.ResumeSubscription = ResumeSubscription;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class ResumeSubscriptionResponse1
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsn/2004/06/wsn-WS-BaseNotification-1.2-draft-01.xsd", Order = 0)]
        public TransferServiceContextService.ResumeSubscriptionResponse ResumeSubscriptionResponse;

        public ResumeSubscriptionResponse1()
        {
        }

        public ResumeSubscriptionResponse1(TransferServiceContextService.ResumeSubscriptionResponse ResumeSubscriptionResponse)
        {
            this.ResumeSubscriptionResponse = ResumeSubscriptionResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface SubscriptionManagerChannel : TransferServiceContextService.SubscriptionManager, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class SubscriptionManagerClient : System.ServiceModel.ClientBase<TransferServiceContextService.SubscriptionManager>, TransferServiceContextService.SubscriptionManager
    {

        public SubscriptionManagerClient()
        {
        }

        public SubscriptionManagerClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public SubscriptionManagerClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public SubscriptionManagerClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public SubscriptionManagerClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.GetResourcePropertyResponse1 TransferServiceContextService.SubscriptionManager.GetResourceProperty(TransferServiceContextService.GetResourcePropertyRequest request)
        {
            return base.Channel.GetResourceProperty(request);
        }

        public TransferServiceContextService.GetResourcePropertyResponse GetResourceProperty(System.Xml.XmlQualifiedName GetResourceProperty1)
        {
            TransferServiceContextService.GetResourcePropertyRequest inValue = new TransferServiceContextService.GetResourcePropertyRequest();
            inValue.GetResourceProperty = GetResourceProperty1;
            TransferServiceContextService.GetResourcePropertyResponse1 retVal = ((TransferServiceContextService.SubscriptionManager)(this)).GetResourceProperty(inValue);
            return retVal.GetResourcePropertyResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.DestroyResponse1 TransferServiceContextService.SubscriptionManager.Destroy(TransferServiceContextService.DestroyRequest request)
        {
            return base.Channel.Destroy(request);
        }

        public TransferServiceContextService.DestroyResponse Destroy(TransferServiceContextService.Destroy Destroy1)
        {
            TransferServiceContextService.DestroyRequest inValue = new TransferServiceContextService.DestroyRequest();
            inValue.Destroy = Destroy1;
            TransferServiceContextService.DestroyResponse1 retVal = ((TransferServiceContextService.SubscriptionManager)(this)).Destroy(inValue);
            return retVal.DestroyResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.SetTerminationTimeResponse1 TransferServiceContextService.SubscriptionManager.SetTerminationTime(TransferServiceContextService.SetTerminationTimeRequest request)
        {
            return base.Channel.SetTerminationTime(request);
        }

        public TransferServiceContextService.SetTerminationTimeResponse SetTerminationTime(TransferServiceContextService.SetTerminationTime SetTerminationTime1)
        {
            TransferServiceContextService.SetTerminationTimeRequest inValue = new TransferServiceContextService.SetTerminationTimeRequest();
            inValue.SetTerminationTime = SetTerminationTime1;
            TransferServiceContextService.SetTerminationTimeResponse1 retVal = ((TransferServiceContextService.SubscriptionManager)(this)).SetTerminationTime(inValue);
            return retVal.SetTerminationTimeResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.PauseSubscriptionResponse1 TransferServiceContextService.SubscriptionManager.PauseSubscription(TransferServiceContextService.PauseSubscriptionRequest request)
        {
            return base.Channel.PauseSubscription(request);
        }

        public TransferServiceContextService.PauseSubscriptionResponse PauseSubscription(TransferServiceContextService.PauseSubscription PauseSubscription1)
        {
            TransferServiceContextService.PauseSubscriptionRequest inValue = new TransferServiceContextService.PauseSubscriptionRequest();
            inValue.PauseSubscription = PauseSubscription1;
            TransferServiceContextService.PauseSubscriptionResponse1 retVal = ((TransferServiceContextService.SubscriptionManager)(this)).PauseSubscription(inValue);
            return retVal.PauseSubscriptionResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.ResumeSubscriptionResponse1 TransferServiceContextService.SubscriptionManager.ResumeSubscription(TransferServiceContextService.ResumeSubscriptionRequest request)
        {
            return base.Channel.ResumeSubscription(request);
        }

        public TransferServiceContextService.ResumeSubscriptionResponse ResumeSubscription(TransferServiceContextService.ResumeSubscription ResumeSubscription1)
        {
            TransferServiceContextService.ResumeSubscriptionRequest inValue = new TransferServiceContextService.ResumeSubscriptionRequest();
            inValue.ResumeSubscription = ResumeSubscription1;
            TransferServiceContextService.ResumeSubscriptionResponse1 retVal = ((TransferServiceContextService.SubscriptionManager)(this)).ResumeSubscription(inValue);
            return retVal.ResumeSubscriptionResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.wsd" +
        "l", ConfigurationName = "TransferServiceContextService.ScheduledResourceTermination")]
    public interface ScheduledResourceTermination
    {

        // CODEGEN: Generating message contract since the operation SetTerminationTime is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.wsd" +
            "l/ScheduledResourceTermination/SetTerminationTimeRequest", ReplyAction = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.wsd" +
            "l/ScheduledResourceTermination/SetTerminationTimeResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.UnableToSetTerminationTimeFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "UnableToSetTerminationTimeFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType2), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.TerminationTimeChangeRejectedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "TerminationTimeChangeRejectedFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.SetTerminationTimeResponse1 SetTerminationTime(TransferServiceContextService.SetTerminationTimeRequest request);
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface ScheduledResourceTerminationChannel : TransferServiceContextService.ScheduledResourceTermination, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class ScheduledResourceTerminationClient : System.ServiceModel.ClientBase<TransferServiceContextService.ScheduledResourceTermination>, TransferServiceContextService.ScheduledResourceTermination
    {

        public ScheduledResourceTerminationClient()
        {
        }

        public ScheduledResourceTerminationClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public ScheduledResourceTerminationClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public ScheduledResourceTerminationClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public ScheduledResourceTerminationClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.SetTerminationTimeResponse1 TransferServiceContextService.ScheduledResourceTermination.SetTerminationTime(TransferServiceContextService.SetTerminationTimeRequest request)
        {
            return base.Channel.SetTerminationTime(request);
        }

        public TransferServiceContextService.SetTerminationTimeResponse SetTerminationTime(TransferServiceContextService.SetTerminationTime SetTerminationTime1)
        {
            TransferServiceContextService.SetTerminationTimeRequest inValue = new TransferServiceContextService.SetTerminationTimeRequest();
            inValue.SetTerminationTime = SetTerminationTime1;
            TransferServiceContextService.SetTerminationTimeResponse1 retVal = ((TransferServiceContextService.ScheduledResourceTermination)(this)).SetTerminationTime(inValue);
            return retVal.SetTerminationTimeResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.wsd" +
        "l", ConfigurationName = "TransferServiceContextService.ImmediateResourceTermination")]
    public interface ImmediateResourceTermination
    {

        // CODEGEN: Generating message contract since the operation Destroy is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.wsd" +
            "l/ImmediateResourceTermination/DestroyRequest", ReplyAction = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.wsd" +
            "l/ImmediateResourceTermination/DestroyResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceNotDestroyedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceNotDestroyedFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType2), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceLifetime-1.2-draft-01.xsd" +
            "")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.DestroyResponse1 Destroy(TransferServiceContextService.DestroyRequest request);
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface ImmediateResourceTerminationChannel : TransferServiceContextService.ImmediateResourceTermination, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class ImmediateResourceTerminationClient : System.ServiceModel.ClientBase<TransferServiceContextService.ImmediateResourceTermination>, TransferServiceContextService.ImmediateResourceTermination
    {

        public ImmediateResourceTerminationClient()
        {
        }

        public ImmediateResourceTerminationClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public ImmediateResourceTerminationClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public ImmediateResourceTerminationClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public ImmediateResourceTerminationClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.DestroyResponse1 TransferServiceContextService.ImmediateResourceTermination.Destroy(TransferServiceContextService.DestroyRequest request)
        {
            return base.Channel.Destroy(request);
        }

        public TransferServiceContextService.DestroyResponse Destroy(TransferServiceContextService.Destroy Destroy1)
        {
            TransferServiceContextService.DestroyRequest inValue = new TransferServiceContextService.DestroyRequest();
            inValue.Destroy = Destroy1;
            TransferServiceContextService.DestroyResponse1 retVal = ((TransferServiceContextService.ImmediateResourceTermination)(this)).Destroy(inValue);
            return retVal.DestroyResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
        "sdl", ConfigurationName = "TransferServiceContextService.GetResourceProperty")]
    public interface GetResourceProperty
    {

        // CODEGEN: Generating message contract since the operation GetResourceProperty is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
            "sdl/GetResourceProperty/GetResourcePropertyRequest", ReplyAction = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
            "sdl/GetResourceProperty/GetResourcePropertyResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidResourcePropertyQNameFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidResourcePropertyQNameFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.GetResourcePropertyResponse1 GetResourceProperty(TransferServiceContextService.GetResourcePropertyRequest request);
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface GetResourcePropertyChannel : TransferServiceContextService.GetResourceProperty, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class GetResourcePropertyClient : System.ServiceModel.ClientBase<TransferServiceContextService.GetResourceProperty>, TransferServiceContextService.GetResourceProperty
    {

        public GetResourcePropertyClient()
        {
        }

        public GetResourcePropertyClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public GetResourcePropertyClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public GetResourcePropertyClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public GetResourcePropertyClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.GetResourcePropertyResponse1 TransferServiceContextService.GetResourceProperty.GetResourceProperty(TransferServiceContextService.GetResourcePropertyRequest request)
        {
            return base.Channel.GetResourceProperty(request);
        }

        public TransferServiceContextService.GetResourcePropertyResponse GetResourceProperty(System.Xml.XmlQualifiedName GetResourceProperty1)
        {
            TransferServiceContextService.GetResourcePropertyRequest inValue = new TransferServiceContextService.GetResourcePropertyRequest();
            inValue.GetResourceProperty = GetResourceProperty1;
            TransferServiceContextService.GetResourcePropertyResponse1 retVal = ((TransferServiceContextService.GetResourceProperty)(this)).GetResourceProperty(inValue);
            return retVal.GetResourcePropertyResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
        "sdl", ConfigurationName = "TransferServiceContextService.GetMultipleResourceProperties")]
    public interface GetMultipleResourceProperties
    {

        // CODEGEN: Generating message contract since the operation GetMultipleResourceProperties is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
            "sdl/GetMultipleResourceProperties/GetMultipleResourcePropertiesRequest", ReplyAction = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
            "sdl/GetMultipleResourceProperties/GetMultipleResourcePropertiesResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidResourcePropertyQNameFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidResourcePropertyQNameFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.GetMultipleResourcePropertiesResponse1 GetMultipleResourceProperties(TransferServiceContextService.GetMultipleResourcePropertiesRequest request);
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class GetMultipleResourcePropertiesResponse : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlElement[] anyField;

        /// <remarks/>
        [System.Xml.Serialization.XmlAnyElementAttribute(Order = 0)]
        public System.Xml.XmlElement[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
                this.RaisePropertyChanged("Any");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class GetMultipleResourcePropertiesRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd", Order = 0)]
        [System.Xml.Serialization.XmlArrayItemAttribute("ResourceProperty", IsNullable = false)]
        public System.Xml.XmlQualifiedName[] GetMultipleResourceProperties;

        public GetMultipleResourcePropertiesRequest()
        {
        }

        public GetMultipleResourcePropertiesRequest(System.Xml.XmlQualifiedName[] GetMultipleResourceProperties)
        {
            this.GetMultipleResourceProperties = GetMultipleResourceProperties;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class GetMultipleResourcePropertiesResponse1
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd", Order = 0)]
        public TransferServiceContextService.GetMultipleResourcePropertiesResponse GetMultipleResourcePropertiesResponse;

        public GetMultipleResourcePropertiesResponse1()
        {
        }

        public GetMultipleResourcePropertiesResponse1(TransferServiceContextService.GetMultipleResourcePropertiesResponse GetMultipleResourcePropertiesResponse)
        {
            this.GetMultipleResourcePropertiesResponse = GetMultipleResourcePropertiesResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface GetMultipleResourcePropertiesChannel : TransferServiceContextService.GetMultipleResourceProperties, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class GetMultipleResourcePropertiesClient : System.ServiceModel.ClientBase<TransferServiceContextService.GetMultipleResourceProperties>, TransferServiceContextService.GetMultipleResourceProperties
    {

        public GetMultipleResourcePropertiesClient()
        {
        }

        public GetMultipleResourcePropertiesClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public GetMultipleResourcePropertiesClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public GetMultipleResourcePropertiesClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public GetMultipleResourcePropertiesClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.GetMultipleResourcePropertiesResponse1 TransferServiceContextService.GetMultipleResourceProperties.GetMultipleResourceProperties(TransferServiceContextService.GetMultipleResourcePropertiesRequest request)
        {
            return base.Channel.GetMultipleResourceProperties(request);
        }

        public TransferServiceContextService.GetMultipleResourcePropertiesResponse GetMultipleResourceProperties(System.Xml.XmlQualifiedName[] GetMultipleResourceProperties1)
        {
            TransferServiceContextService.GetMultipleResourcePropertiesRequest inValue = new TransferServiceContextService.GetMultipleResourcePropertiesRequest();
            inValue.GetMultipleResourceProperties = GetMultipleResourceProperties1;
            TransferServiceContextService.GetMultipleResourcePropertiesResponse1 retVal = ((TransferServiceContextService.GetMultipleResourceProperties)(this)).GetMultipleResourceProperties(inValue);
            return retVal.GetMultipleResourcePropertiesResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
        "sdl", ConfigurationName = "TransferServiceContextService.SetResourceProperties")]
    public interface SetResourceProperties
    {

        // CODEGEN: Generating message contract since the operation SetResourceProperties is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
            "sdl/SetResourceProperties/SetResourcePropertiesRequest", ReplyAction = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
            "sdl/SetResourceProperties/SetResourcePropertiesResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidSetResourcePropertiesRequestContentFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidSetResourcePropertiesRequestContentFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.UnableToModifyResourcePropertyFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "UnableToModifyResourcePropertyFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidResourcePropertyQNameFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidResourcePropertyQNameFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.SetResourcePropertyRequestFailedFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "SetResourcePropertyRequestFailedFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.SetResourcePropertiesResponse1 SetResourceProperties(TransferServiceContextService.SetResourcePropertiesRequest request);
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class SetResourcePropertiesResponse : object, System.ComponentModel.INotifyPropertyChanged
    {

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class SetResourcePropertiesRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd", Order = 0)]
        [System.Xml.Serialization.XmlArrayItemAttribute("Delete", typeof(DeleteType), IsNullable = false)]
        [System.Xml.Serialization.XmlArrayItemAttribute("Insert", typeof(InsertType), IsNullable = false)]
        [System.Xml.Serialization.XmlArrayItemAttribute("Update", typeof(UpdateType), IsNullable = false)]
        public object[] SetResourceProperties;

        public SetResourcePropertiesRequest()
        {
        }

        public SetResourcePropertiesRequest(object[] SetResourceProperties)
        {
            this.SetResourceProperties = SetResourceProperties;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class SetResourcePropertiesResponse1
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd", Order = 0)]
        public TransferServiceContextService.SetResourcePropertiesResponse SetResourcePropertiesResponse;

        public SetResourcePropertiesResponse1()
        {
        }

        public SetResourcePropertiesResponse1(TransferServiceContextService.SetResourcePropertiesResponse SetResourcePropertiesResponse)
        {
            this.SetResourcePropertiesResponse = SetResourcePropertiesResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface SetResourcePropertiesChannel : TransferServiceContextService.SetResourceProperties, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class SetResourcePropertiesClient : System.ServiceModel.ClientBase<TransferServiceContextService.SetResourceProperties>, TransferServiceContextService.SetResourceProperties
    {

        public SetResourcePropertiesClient()
        {
        }

        public SetResourcePropertiesClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public SetResourcePropertiesClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public SetResourcePropertiesClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public SetResourcePropertiesClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.SetResourcePropertiesResponse1 TransferServiceContextService.SetResourceProperties.SetResourceProperties(TransferServiceContextService.SetResourcePropertiesRequest request)
        {
            return base.Channel.SetResourceProperties(request);
        }

        public TransferServiceContextService.SetResourcePropertiesResponse SetResourceProperties(object[] SetResourceProperties1)
        {
            TransferServiceContextService.SetResourcePropertiesRequest inValue = new TransferServiceContextService.SetResourcePropertiesRequest();
            inValue.SetResourceProperties = SetResourceProperties1;
            TransferServiceContextService.SetResourcePropertiesResponse1 retVal = ((TransferServiceContextService.SetResourceProperties)(this)).SetResourceProperties(inValue);
            return retVal.SetResourcePropertiesResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
        "sdl", ConfigurationName = "TransferServiceContextService.QueryResourcePropertiesPortType")]
    public interface QueryResourcePropertiesPortType
    {

        // CODEGEN: Generating message contract since the operation QueryResourceProperties is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
            "sdl/QueryResourcePropertiesPortType/QueryResourcePropertiesRequest", ReplyAction = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.w" +
            "sdl/QueryResourcePropertiesPortType/QueryResourcePropertiesResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidResourcePropertyQNameFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidResourcePropertyQNameFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.UnknownQueryExpressionDialectFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "UnknownQueryExpressionDialectFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidQueryExpressionFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidQueryExpressionFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.QueryEvaluationErrorFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "QueryEvaluationErrorFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.QueryResourcePropertiesResponse1 QueryResourceProperties(TransferServiceContextService.QueryResourcePropertiesRequest request);
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class QueryResourceProperties : object, System.ComponentModel.INotifyPropertyChanged
    {

        private QueryExpressionType queryExpressionField;

        /// <remarks/>
        [System.Xml.Serialization.XmlElementAttribute(Order = 0)]
        public QueryExpressionType QueryExpression
        {
            get
            {
                return this.queryExpressionField;
            }
            set
            {
                this.queryExpressionField = value;
                this.RaisePropertyChanged("QueryExpression");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    /// <remarks/>
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Xml", "2.0.50727.4016")]
    [System.SerializableAttribute()]
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
        "sd")]
    public partial class QueryResourcePropertiesResponse : object, System.ComponentModel.INotifyPropertyChanged
    {

        private System.Xml.XmlNode[] anyField;

        /// <remarks/>
        [System.Xml.Serialization.XmlTextAttribute()]
        [System.Xml.Serialization.XmlAnyElementAttribute(Order = 0)]
        public System.Xml.XmlNode[] Any
        {
            get
            {
                return this.anyField;
            }
            set
            {
                this.anyField = value;
                this.RaisePropertyChanged("Any");
            }
        }

        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;

        protected void RaisePropertyChanged(string propertyName)
        {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if((propertyChanged != null))
            {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class QueryResourcePropertiesRequest
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd", Order = 0)]
        public TransferServiceContextService.QueryResourceProperties QueryResourceProperties;

        public QueryResourcePropertiesRequest()
        {
        }

        public QueryResourcePropertiesRequest(TransferServiceContextService.QueryResourceProperties QueryResourceProperties)
        {
            this.QueryResourceProperties = QueryResourceProperties;
        }
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.MessageContractAttribute(IsWrapped = false)]
    public partial class QueryResourcePropertiesResponse1
    {

        [System.ServiceModel.MessageBodyMemberAttribute(Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd", Order = 0)]
        public TransferServiceContextService.QueryResourcePropertiesResponse QueryResourcePropertiesResponse;

        public QueryResourcePropertiesResponse1()
        {
        }

        public QueryResourcePropertiesResponse1(TransferServiceContextService.QueryResourcePropertiesResponse QueryResourcePropertiesResponse)
        {
            this.QueryResourcePropertiesResponse = QueryResourcePropertiesResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface QueryResourcePropertiesPortTypeChannel : TransferServiceContextService.QueryResourcePropertiesPortType, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class QueryResourcePropertiesPortTypeClient : System.ServiceModel.ClientBase<TransferServiceContextService.QueryResourcePropertiesPortType>, TransferServiceContextService.QueryResourcePropertiesPortType
    {

        public QueryResourcePropertiesPortTypeClient()
        {
        }

        public QueryResourcePropertiesPortTypeClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public QueryResourcePropertiesPortTypeClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public QueryResourcePropertiesPortTypeClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public QueryResourcePropertiesPortTypeClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.QueryResourcePropertiesResponse1 TransferServiceContextService.QueryResourcePropertiesPortType.QueryResourceProperties(TransferServiceContextService.QueryResourcePropertiesRequest request)
        {
            return base.Channel.QueryResourceProperties(request);
        }

        public TransferServiceContextService.QueryResourcePropertiesResponse QueryResourceProperties(TransferServiceContextService.QueryResourceProperties QueryResourceProperties1)
        {
            TransferServiceContextService.QueryResourcePropertiesRequest inValue = new TransferServiceContextService.QueryResourcePropertiesRequest();
            inValue.QueryResourceProperties = QueryResourceProperties1;
            TransferServiceContextService.QueryResourcePropertiesResponse1 retVal = ((TransferServiceContextService.QueryResourcePropertiesPortType)(this)).QueryResourceProperties(inValue);
            return retVal.QueryResourcePropertiesResponse;
        }
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity", ConfigurationName = "TransferServiceContextService.ServiceSecurityPortType")]
    public interface ServiceSecurityPortType
    {

        // CODEGEN: Generating message contract since the wrapper name (GetServiceSecurityMetadataRequest) of message getServiceSecurityMetadataRequest does not match the default value (getServiceSecurityMetadata)
        [System.ServiceModel.OperationContractAttribute(Action = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity/ServiceSecurityPortT" +
            "ype/getServiceSecurityMetadataRequest", ReplyAction = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity/ServiceSecurityPortT" +
            "ype/getServiceSecurityMetadataResponse")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.getServiceSecurityMetadataResponse getServiceSecurityMetadata(TransferServiceContextService.getServiceSecurityMetadataRequest request);

        // CODEGEN: Generating message contract since the operation GetResourceProperty is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity/ServiceSecurityPortT" +
            "ype/GetResourcePropertyRequest", ReplyAction = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity/ServiceSecurityPortT" +
            "ype/GetResourcePropertyResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidResourcePropertyQNameFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidResourcePropertyQNameFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.GetResourcePropertyResponse1 GetResourceProperty(TransferServiceContextService.GetResourcePropertyRequest request);

        // CODEGEN: Generating message contract since the operation GetMultipleResourceProperties is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity/ServiceSecurityPortT" +
            "ype/GetMultipleResourcePropertiesRequest", ReplyAction = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity/ServiceSecurityPortT" +
            "ype/GetMultipleResourcePropertiesResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidResourcePropertyQNameFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidResourcePropertyQNameFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.GetMultipleResourcePropertiesResponse1 GetMultipleResourceProperties(TransferServiceContextService.GetMultipleResourcePropertiesRequest request);

        // CODEGEN: Generating message contract since the operation QueryResourceProperties is neither RPC nor document wrapped.
        [System.ServiceModel.OperationContractAttribute(Action = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity/ServiceSecurityPortT" +
            "ype/QueryResourcePropertiesRequest", ReplyAction = "http://security.introduce.cagrid.nci.nih.gov/ServiceSecurity/ServiceSecurityPortT" +
            "ype/QueryResourcePropertiesResponse")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.ResourceUnknownFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "ResourceUnknownFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidResourcePropertyQNameFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidResourcePropertyQNameFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.UnknownQueryExpressionDialectFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "UnknownQueryExpressionDialectFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.InvalidQueryExpressionFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "InvalidQueryExpressionFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.FaultContractAttribute(typeof(TransferServiceContextService.QueryEvaluationErrorFaultType), Action = "http://www.w3.org/2005/08/addressing/soap/fault", Name = "QueryEvaluationErrorFault", Namespace = "http://docs.oasis-open.org/wsrf/2004/06/wsrf-WS-ResourceProperties-1.2-draft-01.x" +
            "sd")]
        [System.ServiceModel.XmlSerializerFormatAttribute(SupportFaults = true)]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(CommunicationStyle))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DataStorageDescriptor))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(NotificationMessageHolderType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(DeleteType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(UpdateType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(InsertType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(BaseFaultType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(QueryExpressionType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(ResourcePropertyValueChangeNotificationType))]
        [System.ServiceModel.ServiceKnownTypeAttribute(typeof(Operation[]))]
        TransferServiceContextService.QueryResourcePropertiesResponse1 QueryResourceProperties(TransferServiceContextService.QueryResourcePropertiesRequest request);
    }

    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public interface ServiceSecurityPortTypeChannel : TransferServiceContextService.ServiceSecurityPortType, System.ServiceModel.IClientChannel
    {
    }

    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    public partial class ServiceSecurityPortTypeClient : System.ServiceModel.ClientBase<TransferServiceContextService.ServiceSecurityPortType>, TransferServiceContextService.ServiceSecurityPortType
    {

        public ServiceSecurityPortTypeClient()
        {
        }

        public ServiceSecurityPortTypeClient(string endpointConfigurationName) :
            base(endpointConfigurationName)
        {
        }

        public ServiceSecurityPortTypeClient(string endpointConfigurationName, string remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public ServiceSecurityPortTypeClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) :
            base(endpointConfigurationName, remoteAddress)
        {
        }

        public ServiceSecurityPortTypeClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) :
            base(binding, remoteAddress)
        {
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.getServiceSecurityMetadataResponse TransferServiceContextService.ServiceSecurityPortType.getServiceSecurityMetadata(TransferServiceContextService.getServiceSecurityMetadataRequest request)
        {
            return base.Channel.getServiceSecurityMetadata(request);
        }

        public TransferServiceContextService.ServiceSecurityMetadata getServiceSecurityMetadata()
        {
            TransferServiceContextService.getServiceSecurityMetadataRequest inValue = new TransferServiceContextService.getServiceSecurityMetadataRequest();
            TransferServiceContextService.getServiceSecurityMetadataResponse retVal = ((TransferServiceContextService.ServiceSecurityPortType)(this)).getServiceSecurityMetadata(inValue);
            return retVal.ServiceSecurityMetadata;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.GetResourcePropertyResponse1 TransferServiceContextService.ServiceSecurityPortType.GetResourceProperty(TransferServiceContextService.GetResourcePropertyRequest request)
        {
            return base.Channel.GetResourceProperty(request);
        }

        public TransferServiceContextService.GetResourcePropertyResponse GetResourceProperty(System.Xml.XmlQualifiedName GetResourceProperty1)
        {
            TransferServiceContextService.GetResourcePropertyRequest inValue = new TransferServiceContextService.GetResourcePropertyRequest();
            inValue.GetResourceProperty = GetResourceProperty1;
            TransferServiceContextService.GetResourcePropertyResponse1 retVal = ((TransferServiceContextService.ServiceSecurityPortType)(this)).GetResourceProperty(inValue);
            return retVal.GetResourcePropertyResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.GetMultipleResourcePropertiesResponse1 TransferServiceContextService.ServiceSecurityPortType.GetMultipleResourceProperties(TransferServiceContextService.GetMultipleResourcePropertiesRequest request)
        {
            return base.Channel.GetMultipleResourceProperties(request);
        }

        public TransferServiceContextService.GetMultipleResourcePropertiesResponse GetMultipleResourceProperties(System.Xml.XmlQualifiedName[] GetMultipleResourceProperties1)
        {
            TransferServiceContextService.GetMultipleResourcePropertiesRequest inValue = new TransferServiceContextService.GetMultipleResourcePropertiesRequest();
            inValue.GetMultipleResourceProperties = GetMultipleResourceProperties1;
            TransferServiceContextService.GetMultipleResourcePropertiesResponse1 retVal = ((TransferServiceContextService.ServiceSecurityPortType)(this)).GetMultipleResourceProperties(inValue);
            return retVal.GetMultipleResourcePropertiesResponse;
        }

        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Advanced)]
        TransferServiceContextService.QueryResourcePropertiesResponse1 TransferServiceContextService.ServiceSecurityPortType.QueryResourceProperties(TransferServiceContextService.QueryResourcePropertiesRequest request)
        {
            return base.Channel.QueryResourceProperties(request);
        }

        public TransferServiceContextService.QueryResourcePropertiesResponse QueryResourceProperties(TransferServiceContextService.QueryResourceProperties QueryResourceProperties1)
        {
            TransferServiceContextService.QueryResourcePropertiesRequest inValue = new TransferServiceContextService.QueryResourcePropertiesRequest();
            inValue.QueryResourceProperties = QueryResourceProperties1;
            TransferServiceContextService.QueryResourcePropertiesResponse1 retVal = ((TransferServiceContextService.ServiceSecurityPortType)(this)).QueryResourceProperties(inValue);
            return retVal.QueryResourcePropertiesResponse;
        }
    }
}
