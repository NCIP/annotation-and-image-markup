//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

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

		protected DataTable processCQLObjectResult(CQLQueryResults response)
		{
			var uids = new HashSet<string>();
			var table = new DataTable();
			foreach (CQLAttributeResult result in response.Items)
			{
				var addRow = true;
				var dr = table.NewRow();
				foreach (var attr in result.Attribute)
				{
					if (!attr.name.Contains("xmlns"))
					{
						if (!table.Columns.Contains(attr.name))
						{
							var dc = new DataColumn();
							dc.DataType = System.Type.GetType("System.String");
							dc.ColumnName = attr.name;
							table.Columns.Add(dc);
						}
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
