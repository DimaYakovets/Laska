using System.Runtime.InteropServices;

namespace Laska.Dotnet;

internal static unsafe class Memory
{
    internal static T* Alloc<T>(uint count) where T : unmanaged
    {
        return (T*)NativeMemory.Alloc(count, (uint)sizeof(T));
    }

    internal static T* AllocZeroed<T>(uint count) where T : unmanaged
    {
        return (T*)NativeMemory.AllocZeroed(count, (uint)sizeof(T));
    }
}
