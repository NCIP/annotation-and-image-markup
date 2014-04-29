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

namespace NBIAService
{
    class CreateQRAttrAssoGroup
    {
        static public QueryRequestCqlQuery createQueryRequestCqlQuery(string name, string[] queryModifierItems, ItemsChoiceType[] queryModifierItemsChoiceType1,
                                                        Association targetAssociation, Group targetGroup)
        {
            QueryRequestCqlQuery arg = new QueryRequestCqlQuery();
            arg.CQLQuery = new CQLQuery();
            arg.CQLQuery.Target = new Object();
            arg.CQLQuery.Target.name = name;
            if ((queryModifierItems != null) && (queryModifierItemsChoiceType1 != null))
            {
                arg.CQLQuery.QueryModifier = new QueryModifier();
                arg.CQLQuery.QueryModifier.countOnly = false;
                arg.CQLQuery.QueryModifier.Items = queryModifierItems;
                arg.CQLQuery.QueryModifier.ItemsElementName = queryModifierItemsChoiceType1;
            }
            if (targetAssociation != null)
                arg.CQLQuery.Target.Item = targetAssociation;
            else if (targetGroup != null)
                arg.CQLQuery.Target.Item = targetGroup;

            return arg;
        }

        public static Attribute createAttribute(string name, Predicate predicate, string value)
        {
            if (name.Equals(null) || predicate.Equals(null) || value.Equals(null))
                return null;
            Attribute attr1 = new Attribute();
            attr1.name = name;
            attr1.predicate = predicate;
            attr1.value = value;
            return attr1;
        }

        public static Association createAssociation(string name, string rolename, Group group)
        {
            Association asso = new Association();
            asso.name = name;
            asso.roleName = rolename;
            asso.Item = group;
            return asso;
        }

        public static Association createAssociation(string name, string rolename, Group group, Attribute attr, Association association)
        {
            Association asso = new Association();
            asso.name = name;
            asso.roleName = rolename;
            if (group != null)
                asso.Item = group;
            else if (attr != null)
                asso.Item = attr;
            else if (association != null)
                asso.Item = association;
            return asso;
        }

        public static Group createGroup(Attribute attr, LogicalOperator logicalOperator)
        {
            return createGroup(new object[] { attr }, logicalOperator);
        }

        public static Group createGroup(Association asso, LogicalOperator logicalOperator)
        {
            return createGroup(new object[] { asso }, logicalOperator);
        }

        public static Group createGroup(object[] items, LogicalOperator logicalOperator)
        {
            Group gr1 = new Group();
            gr1.logicRelation = logicalOperator;
            gr1.Items = items;
            return gr1;
        }
    }
}
