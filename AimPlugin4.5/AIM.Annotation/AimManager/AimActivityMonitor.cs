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

namespace AIM.Annotation.AimManager
{
	public interface IAimActivityMonitor : IDisposable
	{
		bool IsConnected { get; }
		event EventHandler IsConnectedChanged;

		event EventHandler<StudyAimAnnotationsChangedEventArgs> StudyAnnotationsChanged;
		event EventHandler<StudyAimAnnotationClearedEventArgs> StudiesCleared;
	}

	public abstract class AimActivityMonitor : IAimActivityMonitor
	{
		private static readonly object _instanceLock = new object();
		private static AimActivityMonitorReal _instance;

		internal static volatile int _proxyCount = 0;

		internal AimActivityMonitor()
		{
		}

		~AimActivityMonitor()
		{
			Dispose(false);
		}

		#region IAimActivityMonitor

		public abstract bool IsConnected { get; }
		public abstract event EventHandler IsConnectedChanged;

		public abstract event EventHandler<StudyAimAnnotationsChangedEventArgs> StudyAnnotationsChanged;
		public abstract event EventHandler<StudyAimAnnotationClearedEventArgs> StudiesCleared;

		#endregion


		public static IAimActivityMonitor Create()
		{
			return Create(true);
		}

		public static IAimActivityMonitor Create(bool useSynchronizationContext)
		{
			var syncContext = useSynchronizationContext ? SynchronizationContext.Current : null;
			if (useSynchronizationContext && syncContext == null)
				throw new ArgumentException("Current thread has no synchronization context.", "useSynchronizationContext");

			return Create(syncContext);
		}

		public static IAimActivityMonitor Create(SynchronizationContext synchronizationContext)
		{
			lock (_instanceLock)
			{
				if (_instance == null)
					_instance = new AimActivityMonitorReal();

				_proxyCount++;
				Platform.Log(LogLevel.Debug, "AimActivityMonitor proxy created (count = {0})", _proxyCount);
				return new AimActivityMonitorProxy(_instance, synchronizationContext);
			}
		}

		internal static void OnProxyDisposed()
		{
			lock (_instanceLock)
			{
				if (_proxyCount == 0)
					return; //Should never happen, except possibly when there's unit tests running.

				--_proxyCount;
				Platform.Log(LogLevel.Debug, "AimActivityMonitor proxy disposed (count = {0}).", _proxyCount);
				if (_proxyCount > 0)
					return;

				var monitor = _instance;
				_instance = null;
				//No need to do this synchronously.
				ThreadPool.QueueUserWorkItem(ignore => monitor.Dispose());
			}
		}


		public void Dispose()
		{
			try
			{
				Dispose(true);
				GC.SuppressFinalize(this);
			}
			catch (Exception e)
			{
				Platform.Log(LogLevel.Debug, e, "Unexpected error disposing AimActivityMonitor.");
			}
		}

		protected virtual void Dispose(bool disposing)
		{
		}
	}
}
