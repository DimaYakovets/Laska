using Laska.Interop;

namespace Laska.Framework
{
    public unsafe sealed class Engine : IDisposable
    {
        private bool _initialized;
        private IntPtr _application;

        public Engine()
        {
            _initialized = false;
        }

        public bool Startup(ref EngineStartupSpecification specification)
        {
            _initialized = LaskaNativeApi.LaskaEngineStartup(ref specification);

            return _initialized;
        }

        public void Shutdown()
        {
            if (_initialized)
            {
                LaskaNativeApi.LaskaEngineShutdown();

                _initialized = false;
            }
        }

        public Application CreateApplication(ref ApplicationSpecification specification)
        {
            if (!_initialized)
            {
                throw new InvalidOperationException();
            }

            _application = LaskaNativeApi.LaskaApplicationCreate(ref specification);

            return new Application(_application);
        }

        public void Dispose()
        {
            Shutdown();
        }
    }
}
