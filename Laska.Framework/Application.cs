using Laska.Interop;

namespace Laska.Framework
{
    public unsafe sealed class Application : IDisposable
    {
        private readonly IntPtr _application;
        private bool _disposed;

        internal Application(IntPtr application)
        {
            _disposed = false;
            _application = application;
        }

        public void Start()
        {
            LaskaNativeApi.LaskaApplicationStart(_application);
        }

        public void Dispose()
        {
            if (!_disposed)
            {
                LaskaNativeApi.LaskaApplicationDestroy(_application);
                _disposed = true;
            }
        }
    }
}
