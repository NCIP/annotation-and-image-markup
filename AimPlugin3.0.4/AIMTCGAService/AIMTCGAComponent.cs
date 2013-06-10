#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System.Collections.Specialized;

using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;
using ClearCanvas.Desktop;

namespace AIMTCGAService
{
    /// <summary>
    /// Extension point for views onto <see cref="AIMTCGAComponent"/>.
    /// </summary>
    [ExtensionPoint]
    public sealed class AIMTCGAComponentViewExtensionPoint : ExtensionPoint<IApplicationComponentView>
    {
    }

    /// <summary>
    /// AIMTCGAComponent class.
    /// </summary>
    [AssociateView(typeof(AIMTCGAComponentViewExtensionPoint))]
    public class AIMTCGAComponent : ApplicationComponent
    {
    	private string _aimDataServiceUrl;
    	private StringCollection _aimDataServiceUrlList;
    	private bool _saveRequested;

		public string AIMTCGAServiceUrl
		{
			get { return _aimDataServiceUrl; }
			set
			{
				if (_aimDataServiceUrl == value)
					return;

				_aimDataServiceUrl = value;
				NotifyPropertyChanged("AIMTCGAServiceUrl");
			}
		}

		public StringCollection AIMTCGAServiceList
		{
			get { return _aimDataServiceUrlList; }
			set
			{
				if (IsEqual(_aimDataServiceUrlList, value))
					return;

				_aimDataServiceUrlList = value;
				NotifyPropertyChanged("AIMTCGAServiceList");
			}
		}

    	public bool SaveRequested
    	{
			get { return _saveRequested; }
			set
			{
				if (_saveRequested == value)
					return;

				_saveRequested = value;
			}
    	}

        public AIMTCGAComponent()
        {
        }

        public override void Start()
        {
            base.Start();

        	AIMTCGAServiceUrl = AIMDataServiceSettings.Default.AIMDataServiceUrl;
        	AIMTCGAServiceList = AIMDataServiceSettings.Default.AIMDataServiceUrlList;
        }

        public override void Stop()
        {
            base.Stop();

			if (_saveRequested)
			{
				var hasChanged = false;
				if (AIMDataServiceSettings.Default.AIMDataServiceUrl != _aimDataServiceUrl)
				{
					AIMDataServiceSettings.Default.AIMDataServiceUrl = _aimDataServiceUrl;
					hasChanged = true;
					if (!string.IsNullOrEmpty(_aimDataServiceUrl) && !CollectionUtils.Contains(_aimDataServiceUrlList, p => (string) p == _aimDataServiceUrl))
						_aimDataServiceUrlList.Insert(0, _aimDataServiceUrl);
				}

				if (!hasChanged && !IsEqual(AIMDataServiceSettings.Default.AIMDataServiceUrlList, _aimDataServiceUrlList))
					hasChanged = true;

				if (hasChanged)
				{
					AIMDataServiceSettings.Default.AIMDataServiceUrlList = _aimDataServiceUrlList;
					AIMDataServiceSettings.Default.Save();
				}
			}
        }

		private static bool IsEqual(StringCollection collOne, StringCollection collTwo)
		{
			if (collOne != collTwo)
			{
				if (collOne == null || collTwo == null || collOne.Count != collTwo.Count)
					return false;

				for (var i = 0; i < collOne.Count; i++)
				{
					if (collOne[i] != collTwo[i])
						return false;
				}
			}
			return true;
		}
    }
}
