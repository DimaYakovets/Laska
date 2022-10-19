using System.Runtime.InteropServices;

namespace Laska.Dotnet;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct DotnetApiFunctions
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
    public UnsafeArray<DotnetMethodInfo> DefinedMethods;
}

[StructLayout(LayoutKind.Sequential)]
public struct DotnetType
{
    public int Handle;
}

[StructLayout(LayoutKind.Sequential)]
public unsafe struct UnsafeArray<T> where T : unmanaged
{
    public Span<T> Span => new(Values, (int)Length);
    public ulong Length;
    public T* Values;

    public static UnsafeArray<T> Allocate(int size)
    {
        return new UnsafeArray<T>()
        {
            Length = (uint)size,
            Values = Memory.AllocZeroed<T>((uint)size)
        };
    }
}

[StructLayout(LayoutKind.Sequential)]
public unsafe struct UnsafeString
{
    public string Value => new(Chars);
    public char* Chars;
}

[StructLayout(LayoutKind.Sequential)]
public unsafe struct DotnetInit
{
    public UnsafeArray<IntPtr> inFunctionPointers;
    public UnsafeArray<UnsafeString> inDllList;
    public DotnetApiFunctions* outApiFunctions;
    public UnsafeArray<DotnetTypeInfo>* outDefinedTypes;
}
