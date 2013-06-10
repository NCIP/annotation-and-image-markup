#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Configuration;
using ClearCanvas.Desktop;

namespace SearchComponent
{
	[SettingsGroupDescription("Search results configuration")]
	[SettingsProvider(typeof(ClearCanvas.Common.Configuration.StandardSettingsProvider))]
	public sealed partial class SearchSettings
	{
		private SearchSettings()
		{
			ApplicationSettingsRegistry.Instance.RegisterInstance(this);
		}
	}
}
