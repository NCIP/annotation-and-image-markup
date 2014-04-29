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

using System;
using System.Threading;
using ClearCanvas.Common;
using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.AimManager
{
	internal class AimActivityMonitorProxy : AimActivityMonitor
	{
		private readonly IAimActivityMonitor _real;
		private readonly SynchronizationContext _synchronizationContext;

		private event EventHandler _isConnectedChanged;
		private event EventHandler<StudyAimAnnotationsChangedEventArgs> _studyAnnotationsChanged;
		private event EventHandler<StudyAimAnnotationClearedEventArgs> _studiesCleared;

		private volatile bool _disposed;

		internal AimActivityMonitorProxy(IAimActivityMonitor real, SynchronizationContext synchronizationContext)
		{
			Platform.CheckForNullReference(real, "real");

			_real = real;
			_synchronizationContext = synchronizationContext;
		}

		public override bool IsConnected
		{
			get
			{
				CheckDisposed();
				return _real.IsConnected;
			}
		}

		public override event EventHandler IsConnectedChanged
		{
			add
			{
				CheckDisposed();

				var subscribeToReal = _isConnectedChanged == null;
				if (subscribeToReal)
					_real.IsConnectedChanged += OnIsConnectedChanged;

				_isConnectedChanged += value;
			}

			remove
			{
				CheckDisposed();

				_isConnectedChanged -= value;

				var unsubscribeFromReal = _isConnectedChanged == null;
				if (unsubscribeFromReal)
					_real.IsConnectedChanged -= OnIsConnectedChanged;
			}
		}

		public override event EventHandler<StudyAimAnnotationsChangedEventArgs> StudyAnnotationsChanged
		{
			add
			{
				CheckDisposed();

				var subscribeToReal = _studyAnnotationsChanged == null;
				if (subscribeToReal)
					_real.StudyAnnotationsChanged += OnStudyAnnotationsChanged;

				_studyAnnotationsChanged += value;
			}
			remove
			{
				CheckDisposed();

				_studyAnnotationsChanged -= value;

				var unsubscribeFromReal = _studyAnnotationsChanged == null;
				if (unsubscribeFromReal)
					_real.StudyAnnotationsChanged -= OnStudyAnnotationsChanged;
			}
		}

		public override event EventHandler<StudyAimAnnotationClearedEventArgs> StudiesCleared
		{
			add
			{
				CheckDisposed();

				var subscribeToReal = _studiesCleared == null;
				if (subscribeToReal)
					_real.StudiesCleared += OnStudiesCleared;

				_studiesCleared += value;
			}
			remove
			{
				CheckDisposed();

				_studiesCleared -= value;

				var unsubscribeFromReal = _studiesCleared == null;
				if (unsubscribeFromReal)
					_real.StudiesCleared -= OnStudiesCleared;
			}
		}

		private void OnIsConnectedChanged(object sender, EventArgs e)
		{
			if (_synchronizationContext != null)
				_synchronizationContext.Post(ignore => FireIsConnectedChanged(), null);
			else
				FireIsConnectedChanged();
		}

		private void OnStudyAnnotationsChanged(object sender, StudyAimAnnotationsChangedEventArgs args)
		{
			if (_synchronizationContext != null)
				_synchronizationContext.Post(ignore => FireStudyAnnotationsChanged(args), null);
			else
				FireStudyAnnotationsChanged(args);
		}

		private void OnStudiesCleared(object sender, StudyAimAnnotationClearedEventArgs args)
		{
			if (_synchronizationContext != null)
				_synchronizationContext.Post(ignore => FireStudiesCleared(args), null);
			else
				FireStudiesCleared(args);
		}

		private void FireIsConnectedChanged()
		{
			if (!_disposed)
				EventsHelper.Fire(_isConnectedChanged, this, EventArgs.Empty);
		}

		private void FireStudyAnnotationsChanged(StudyAimAnnotationsChangedEventArgs e)
		{
			if (!_disposed)
				EventsHelper.Fire(_studyAnnotationsChanged, this, e);
		}

		private void FireStudiesCleared(StudyAimAnnotationClearedEventArgs e)
		{
			if (!_disposed)
				EventsHelper.Fire(_studiesCleared, this, e);
		}

		private void CheckDisposed()
		{
			if (_disposed)
				throw new ObjectDisposedException("AimActivityMonitor has already been disposed.");
		}

		protected override void Dispose(bool disposing)
		{
			_disposed = true;

			if (disposing)
			{
				if (_isConnectedChanged != null)
					_real.IsConnectedChanged -= OnIsConnectedChanged;

				if (_studyAnnotationsChanged != null)
					_real.StudyAnnotationsChanged -= OnStudyAnnotationsChanged;

				if (_studiesCleared != null)
					_real.StudiesCleared -= OnStudiesCleared;
			}

			OnProxyDisposed();
		}
	}
}
