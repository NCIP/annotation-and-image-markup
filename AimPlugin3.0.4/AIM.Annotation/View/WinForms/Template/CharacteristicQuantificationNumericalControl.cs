//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using AIM.Annotation.Template;

namespace AIM.Annotation.View.WinForms.Template
{
	public partial class CharacteristicQuantificationNumericalControl : UserControl
	{
		private static readonly OperatorNameValuePair[] _availableOperators =
			new[]
				{
					new OperatorNameValuePair(null, null),
					new OperatorNameValuePair("=", "Equal"),
					new OperatorNameValuePair("!=", "NotEqual"),
					new OperatorNameValuePair("<", "LessThan"),
					new OperatorNameValuePair("<=", "LessThanEqual"),
					new OperatorNameValuePair(">", "GreaterThan"),
					new OperatorNameValuePair(">=", "GreaterThanEqual")
				};

		public CharacteristicQuantificationNumericalControl(Numerical numerical)
		{
			InitializeComponent();

			_ddlComparisonOperator.DataSource = _availableOperators;
			_ddlComparisonOperator.DisplayMember = "Name";
			_ddlComparisonOperator.ValueMember = "Value";

			_lblUcumString.Text = numerical.UcumString;

			_txtValue.Mask = @"9.099999";
			_txtValue.ValidatingType = typeof (double);
			_txtValue.Text = numerical.Value.ToString();
		}

		internal class OperatorNameValuePair
		{
			public string Name { get; private set; }
			public string Value { get; private set; }

			public OperatorNameValuePair(string name, string value)
			{
				Name = name;
				Value = value;
			}

			public override string ToString()
			{
				return Value == null ? "---" : Name;
			}
		}
	}
}
