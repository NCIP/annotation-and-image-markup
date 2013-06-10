#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Collections.Generic;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop.Explorer;
using ClearCanvas.Desktop;
using ClearCanvas.Desktop.Tables;

namespace SearchComponent
{
	public abstract class GridExplorerBase : IHealthcareArtifactExplorer
	{
		protected IApplicationComponent _component;

		#region IHealthcareArtifactExplorer Members

		public IApplicationComponent Component
		{
			get
			{
				if (_component == null)
					_component = CreateComponent();
				return _component;
			}
		}

		public bool IsAvailable
		{
			get { return true; }
		}

		public virtual string Name
		{
			get { return "caGrid Data Service"; }
		}

		#endregion

		protected abstract IApplicationComponent CreateComponent();

		protected RetrieveProgressComponent CreateRetrieveProgressComponent()
		{
			Table<RetrieveProgressResult> table = new Table<RetrieveProgressResult>();
			InitializeRetrieveProgressTable(table);

			RetrieveProgressComponent retrieveProgressComponent =
				new RetrieveProgressComponent(RetrieveProgressComponent.ToolbarSite, RetrieveProgressComponent.MenuSite,
											  RetrieveProgressComponent.ToolNamespace,
											  new RetrieveProgressToolExtensionPoint(), table);

			return retrieveProgressComponent;
		}

		private void InitializeRetrieveProgressTable(Table<RetrieveProgressResult> table)
		{
			TableColumn<RetrieveProgressResult, string> column;

			column = new TableColumn<RetrieveProgressResult, string>("Status", delegate(RetrieveProgressResult result)
       		{
       			string msg = string.IsNullOrEmpty(result.ProgressMessage)
       		             		? null
       		             		: result.ProgressMessage;

       			switch (result.Status)
       			{
       				case RetrieveStatus.Queued:
       					return "Waiting";
       				case RetrieveStatus.InProgress:
       					return msg ?? "Downloading...";
       				case RetrieveStatus.Canceled:
       					return "Canceled";
       				case RetrieveStatus.Completed:
       					return "Done";
       				case RetrieveStatus.CancelRequested:
       					return string.Format("{0}...Canceling", msg ?? "");
       			}
       			return msg ?? "";
       		}, 0.25F);
			table.Columns.Add(column);

			column = new TableColumn<RetrieveProgressResult, string>("Study Count", delegate(RetrieveProgressResult result)
       		{
       			return result.QueryItems.Count.ToString();
       		}, 0.05F);
			table.Columns.Add(column);

			column = new TableColumn<RetrieveProgressResult, string>("Patient Id", delegate(RetrieveProgressResult result)
			{
				switch(result.QueryItems.Count)
				{
					case 0:
						break;
					case 1:
						return result.QueryItems[0].Patient.PatientId ?? "";
					default:
						return string.Format("1. {0}...", result.QueryItems[0].Patient.PatientId ?? "");
				}
				return "";
			}, 0.25F);
			column.TooltipTextProvider =
				delegate(RetrieveProgressResult result)
					{
						if (result.QueryItems.Count > 1)
						{
							List<string> tooltipList = new List<string>();
							int cnt = 0;
							foreach (RetrieveQueryItem queryItem in result.QueryItems)
							{
								tooltipList.Add(string.Format("{0}. {1}", ++cnt, queryItem.Patient.PatientId ?? ""));
							}

							return StringUtilities.Combine(tooltipList, "\n");
						}

						return result.QueryItems.Count > 0 ? result.QueryItems[0].Patient.PatientId ?? "" : "";
					};
			table.Columns.Add(column);

			column = new TableColumn<RetrieveProgressResult, string>("Patient's Name", delegate(RetrieveProgressResult result) 
			{
				switch (result.QueryItems.Count)
				{
					case 0:
						break;
					case 1:
						return result.QueryItems[0].Patient.PatientsName ?? "";
					default:
						return string.Format("1. {0}...", result.QueryItems[0].Patient.PatientsName ?? "");
				}
				return "";
			}, 0.25F);
			column.TooltipTextProvider =
				delegate(RetrieveProgressResult result)
				{
					if (result.QueryItems.Count > 1)
					{
						List<string> tooltipList = new List<string>();
						int cnt = 0;
						foreach (RetrieveQueryItem queryItem in result.QueryItems)
						{
							tooltipList.Add(string.Format("{0}. {1}", ++cnt, queryItem.Patient.PatientsName ?? ""));
						}

						return StringUtilities.Combine(tooltipList, "\n");
					}

					return result.QueryItems.Count > 0 ? result.QueryItems[0].Patient.PatientsName ?? "" : "";
				};
			table.Columns.Add(column);

			column = new TableColumn<RetrieveProgressResult, string>("Study", delegate(RetrieveProgressResult result)
			{
				switch (result.QueryItems.Count)
				{
					case 0:
						break;
					case 1:
						return result.QueryItems[0].Study.StudyInstanceUid ?? "";
					default:
						return string.Format("1. {0}...", result.QueryItems[0].Study.StudyInstanceUid ?? "");
				}
				return "";

			}, 0.25F);
			column.TooltipTextProvider =
				delegate(RetrieveProgressResult result)
				{
					if (result.QueryItems.Count > 1)
					{
						List<string> tooltipList = new List<string>();
						int cnt = 0;
						foreach (RetrieveQueryItem queryItem in result.QueryItems)
						{
							tooltipList.Add(string.Format("{0}. {1}", ++cnt, queryItem.Study.StudyInstanceUid ?? ""));
						}

						return StringUtilities.Combine(tooltipList, "\n");
					}

					return result.QueryItems.Count > 0 ? result.QueryItems[0].Study.StudyInstanceUid ?? "" : "";
				};
			table.Columns.Add(column);
		}
	}
}
