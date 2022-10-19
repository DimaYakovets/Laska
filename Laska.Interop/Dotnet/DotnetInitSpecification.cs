using System.Runtime.InteropServices;

namespace Laska.Interop.Dotnet;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct DotnetApiCallbacks
{
    public delegate* unmanaged[Cdecl]<int, IntPtr> dotnet_create_instance;
    public delegate* unmanaged[Cdecl]<IntPtr, void> dotnet_finalize;
    public delegate* unmanaged[Cdecl]<IntPtr, int, void> dotnet_call_init;
    public delegate* unmanaged[Cdecl]<IntPtr, int, float, void> dotnet_call_early_update;
    public delegate* unmanaged[Cdecl]<IntPtr, int, float, void> dotnet_call_fixed_update;
    public delegate* unmanaged[Cdecl]<IntPtr, int, float, void> dotnet_call_update;
    public delegate* unmanaged[Cdecl]<IntPtr, int, float, void> dotnet_call_late_update;
    public delegate* unmanaged[Cdecl]<IntPtr, int, void> dotnet_call_delete;
    public delegate* unmanaged[Cdecl]<IntPtr, IntPtr, void> dotnet_call_collision_enter;
    public delegate* unmanaged[Cdecl]<IntPtr, IntPtr, void> dotnet_call_collision_exit;
}

public struct DotnetMethod
{
    public int TypeIndex;
    public int MethodIndex;
}

[StructLayout(LayoutKind.Sequential)]
public struct DotnetMethodInfo
{
    public UnsafeString Name;
    public DotnetMethod Method;
}

[StructLayout(LayoutKind.Sequential)]
public struct DotnetTypeInfo
{
    public UnsafeString Name;
    public DotnetType Type;
    public UnsafeSpan<DotnetMethodInfo> DefinedMethods;
}

[StructLayout(LayoutKind.Sequential)]
public struct DotnetType
{
    public int Handle;
}

[StructLayout(LayoutKind.Sequential)]
public unsafe struct DotnetInit
{
    public UnsafeSpan<IntPtr> inFunctionPointers;
    public UnsafeSpan<UnsafeString> inDllList;
    public DotnetApiCallbacks* outApiFunctions;
    public UnsafeSpan<DotnetTypeInfo>* outDefinedTypes;
}
