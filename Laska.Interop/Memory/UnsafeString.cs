using System.Runtime.InteropServices;

namespace Laska.Interop.Dotnet;

[StructLayout(LayoutKind.Sequential)]
public unsafe struct UnsafeString
{
    public string Value => new(Chars);
    public char* Chars;
}
