using System.Runtime.InteropServices;

namespace Laska.Interop.Dotnet;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct UnsafeSpan<T> 
    where T : unmanaged
{
    public Span<T> Span => new(Values, (int)Length);
    
    public ulong Length;
    public T* Values;

    public static UnsafeSpan<T> Allocate(int size)
    {
        return new UnsafeSpan<T>()
        {
            Length = (uint)size,
            Values = (T*)NativeMemory.AllocZeroed((uint)(sizeof(T) * size))
        };
    }
}
