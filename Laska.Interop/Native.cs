using Laska.Interop.Dotnet;
using System.Runtime.InteropServices;

namespace Laska.Interop;

public struct ApplicationSpecification
{
    public uint WindowHeight;
    public uint WindowWidth;
    public bool FullScreen;
    public bool VSync;
};

public unsafe struct DotnetStartupSpecification
{
    public bool UseExternalDotnet;
    public delegate*<ref DotnetInit, void> Init;
}

public struct EngineStartupSpecification
{
    public DotnetStartupSpecification Dotnet;
}

public static class LaskaNativeApi
{
    private const string DllName = "Laska";

    [DllImport(DllName, EntryPoint = "lskEngineStartup")]
    public extern static bool LaskaEngineStartup(ref EngineStartupSpecification specs);

    [DllImport(DllName, EntryPoint = "lskEngineShutdown")]
    public extern static void LaskaEngineShutdown();

    [DllImport(DllName, EntryPoint = "lskApplicationCreate")]
    public extern static unsafe IntPtr LaskaApplicationCreate(ref ApplicationSpecification specs);

    [DllImport(DllName, EntryPoint = "lskApplicationStart")]
    public extern static unsafe void LaskaApplicationStart(IntPtr app);

    [DllImport(DllName, EntryPoint = "lskApplicationDestroy")]
    public extern static unsafe void LaskaApplicationDestroy(IntPtr app);
}
