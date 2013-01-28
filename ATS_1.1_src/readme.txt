AimTemplateService


Configuration

Update the variables in serverConfig.txt to reflect the path to a keystore and
name of a keystore (if using SSL) and path to a directory in which the XML
databases can be stored. In addition, a default container can be specified so
that the server will look there when a query does not specify a collection.

To disable SSL, leave the keystorepath and keystorename variables blank.

All paths are treated as absolute paths.


Starting

Start the AimTemplateService by running AimTemplateService.jar. If using SSL, port
8443 must be open and free. If not using SSL, port 8080 must be open and free.


Usage

The AimTemplateService listens on port 8443 for requests via HTTPS if using SSL,
and port 8080 for requests via HTTP if not. There are multiple resources
available. For example, if the server was running on localhost using SSL:

https://localhost:8443/templates
This resource takes POST requests for arbitrary XQuery expressions.
Fields:
namespace (type: text): This must have a string value corresponding to the
   namespace of the documents you want to query. This can be the empty string if
   referring to the default namespace.
xquery (type: text): This must be the XQuery expression you want to have
   evaluated. Note that specifying the collection must be done with the
   collection function.
Returns: XML result of query.

https://localhost:8443/templates/upload
This resource takes POST requests to upload and add XML documents to an existing
or a new collection.
Fields:
collection (type: text): The collection to add the new document to. If the
   collection specified does not exist, it is created.
<any> (type: file): A file to add to the collection. All values of fields of
   type file are added, regardless of field name.
Returns: String describing success/failure of upload.
   

