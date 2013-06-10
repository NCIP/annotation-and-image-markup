#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using DataServiceUtil;
using System.Collections;

namespace AIMTCGAService
{
    public abstract class AIMTCGAQueryBase
    {
        protected AIMQueryParameters _queryParameters;

        protected Predicate FromQueryPredicate(QueryPredicate queryPredicate)
        {
            switch (queryPredicate)
            {
                case QueryPredicate.EQUAL_TO:
                    return Predicate.EQUAL_TO;
                case QueryPredicate.GREATER_THAN:
                    return Predicate.GREATER_THAN;
                case QueryPredicate.GREATER_THAN_EQUAL_TO:
                    return Predicate.GREATER_THAN_EQUAL_TO;
                case QueryPredicate.IS_NOT_NULL:
                    return Predicate.IS_NOT_NULL;
                case QueryPredicate.IS_NULL:
                    return Predicate.IS_NULL;
                case QueryPredicate.LESS_THAN:
                    return Predicate.LESS_THAN;
                case QueryPredicate.LESS_THAN_EQUAL_TO:
                    return Predicate.LESS_THAN_EQUAL_TO;
                case QueryPredicate.LIKE:
                    return Predicate.LIKE;
                case QueryPredicate.NOT_EQUAL_TO:
                    return Predicate.NOT_EQUAL_TO;
            }

            System.Diagnostics.Debug.Assert(false);
            return Predicate.LIKE;
        }

        protected Attribute CreateAttribute(string attributeName, QueryData queryData)
        {
            return CreateQRAttrAssoGroup.createAttribute(attributeName, FromQueryPredicate(queryData.Predicate), queryData.SelectedValue);
        }

        protected string[] processCQLObjectResult(AIMTCGAService.CQLQueryResults response)
        {
            var results = new ArrayList();
            foreach (CQLObjectResult result in response.Items)
            {
                results.Add(XMLSerializingDeserializing.Serialize(result.Any).InnerXml);
            }
            return (string[])results.ToArray(typeof(string));
        }
    }
}
