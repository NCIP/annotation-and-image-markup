This is an official release of the AIM version 3.0.2.

It consists of a model, documentation, examples and library.
It is a minor release that address issues discovered after the 
initial release of AIM version 3.0 and adds Linux compatibility.

There are four folders, which are doc, examples, lib and source.

The doc folder consists of AIM related document and XML schemas.
*Note: user should use AIM_v3_rv11_XML.xsd for creating and
validating AIM XML documents.

The examples folder consists of examples of DICOM Images, AIM DICOM SR, 
AIM XML documents and ANIVATR tool used to covert between DICOM SR 
and XML documents.

The lib folder contains binaries for AIM XML library and a tool called ANIVATR.

AIM Toolkit version 3.0.2 changes:
1. Added Linux (Ubuntu x86) make files
2. Modified code to build on Linux platform
3. Updated DCMTK to version 3.6.0
4. Update xerces-c to version 3.1

AIM Toolkit version 3.0.1 changes:
1. Added AIM Model Version property to the API (BaseModel class)
2. Used AIM Model Version in the Series Description of new AIM DICOM objects
3. Fixed parsing of attribute values with namespaces
4. Updated source code and precompiled binaries to include the latest changes
