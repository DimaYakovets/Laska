using Laska.Framework;
using Laska.Interop;
using Laska.Interop.Dotnet;
using System.Runtime;

namespace RuntimeCS;

public static class Program
{
    private static unsafe void DotnetInit(ref DotnetInit init)
    {
        ref UnsafeSpan<DotnetTypeInfo> types = ref *init.outDefinedTypes;

        types = UnsafeSpan<DotnetTypeInfo>.Allocate(2);
    }

    private static unsafe void Main(string[] _)
    {
        EngineStartupSpecification engineSpecification = default;
        engineSpecification.Dotnet.UseExternalDotnet = true;
        engineSpecification.Dotnet.Init = &DotnetInit;

        ApplicationSpecification applicationSpecification = default;
        applicationSpecification.WindowWidth = 1280;
        applicationSpecification.WindowHeight = 720;
        applicationSpecification.FullScreen = false;
        applicationSpecification.VSync = false;

        using Engine engine = new();
        engine.Startup(ref engineSpecification);

        using Application application = engine.CreateApplication(ref applicationSpecification);
        application.Start();
    }
}
