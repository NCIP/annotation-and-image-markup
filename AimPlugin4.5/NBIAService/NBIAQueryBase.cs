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

using System.Collections.Generic;
using System.Data;
using DataServiceUtil;

namespace NBIAService
{
    public abstract class NBIAQueryBase
    {
        protected NBIAQueryParameters _queryParameters;

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

            System.Diagnostics.Debug.Assert(false); // this should never happen
            return Predicate.LIKE;
        }

        protected Attribute CreateAttribute(string attributeName, QueryData queryData)
        {
            return CreateQRAttrAssoGroup.createAttribute(attributeName, FromQueryPredicate(queryData.Predicate), queryData.SelectedValue);
        }

        protected DataTable processCQLObjectResult(NBIAService.CQLQueryResults response)
        {
            HashSet<string> uids = new HashSet<string>();
            DataTable table = new DataTable();
            foreach (CQLAttributeResult result in response.Items)
            {
                bool addRow = true;
                DataRow dr = table.NewRow();
                foreach (TargetAttribute attr in result.Attribute)
                {
                    if (!attr.name.Contains("xmlns"))
                    {
                        if (!table.Columns.Contains(attr.name))
                        {
                            DataColumn dc = new DataColumn();
                            dc.DataType = System.Type.GetType("System.String");
                            dc.ColumnName = attr.name;
                            table.Columns.Add(dc);
                        }
                        // NCIA/NBIA has fixed the study duplication problem.
                        // We keep this line just in case it comes back again.
                        if (attr.name.Equals("studyInstanceUID"))
                        {
                            if (uids.Add(attr.value))
                                dr[attr.name] = attr.value;
                            else
                            {
                                addRow = false;
                                break;
                            }
                        }
                        else
                            dr[attr.name] = attr.value;
                    }
                }
                if (addRow)
                    table.Rows.Add(dr);
            }
            return table;
        }

    }
}
