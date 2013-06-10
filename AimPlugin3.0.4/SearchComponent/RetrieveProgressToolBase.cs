#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Tools;

namespace SearchComponent
{
	public abstract class RetrieveProgressToolBase : Tool<IRetrieveProgressToolContext>
	{
		private bool _enabled;
		private event EventHandler _enabledChanged;

		/// <summary>
		/// Default constructor.
		/// </summary>
		/// <remarks>
		/// A no-args constructor is required by the framework.  Do not remove.
		/// </remarks>
		protected RetrieveProgressToolBase()
		{
		}

		/// <summary>
		/// Gets whether this tool is enabled/disabled in the UI.
		/// </summary>
		public bool Enabled
		{
			get { return _enabled; }
			protected set
			{
				if (_enabled != value)
				{
					_enabled = value;
					EventsHelper.Fire(_enabledChanged, this, EventArgs.Empty);
				}
			}
		}

		/// <summary>
		/// Notifies that the <see cref="Enabled"/> state of this tool has changed.
		/// </summary>
		public event EventHandler EnabledChanged
		{
			add { _enabledChanged += value; }
			remove { _enabledChanged -= value; }
		}

		public override void Initialize()
		{
			base.Initialize();
			Context.SelectionChanged += OnSelectedItemChanged;
		}

		/// <summary>
		/// Called when selection of a progress item is changed
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		protected virtual void OnSelectedItemChanged(object sender, EventArgs e)
		{
			this.Enabled = this.Context.Selection.Item != null;
		}
	}
}
