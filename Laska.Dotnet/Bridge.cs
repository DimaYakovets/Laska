using System.Reflection;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Laska.Dotnet;

public static unsafe class Bridge
{
    private static ScriptInfo[] _infos;

    private static DotnetMethodInfo CreateMetodInfo(string typeName, string methodName, int type, int methodIndex)
    {
        string fullName = typeName + "." + methodName;

        DotnetMethodInfo method = new()
        {
            Method = new()
            {
                MethodIndex = methodIndex,
                TypeIndex = type
            },
            Name = new()
            {
                Chars = Memory.AllocZeroed<char>((uint)fullName.Length + 1),
            }
        };

        fixed (char* n = fullName)
        {
            Unsafe.CopyBlock(method.Name.Chars, n, (uint)(sizeof(char) * fullName.Length));
        }

        return method;
    }

    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    public static void Init(DotnetInit* initInfo)
    {
        _infos = Assembly.GetExecutingAssembly()
            .DefinedTypes
            .Where(t => t.Name.EndsWith("Behavior"))
            .Select(t => new ScriptInfo(t))
            .ToArray();

        if (initInfo->inFunctionPointers.Values != null)
        {
            ref UnsafeArray<IntPtr> api = ref initInfo->inFunctionPointers;
        }

        if (initInfo->outApiFunctions != null)
        {
            ref DotnetApiFunctions api = ref *initInfo->outApiFunctions;

            api.dotnet_create_instance = &CreateInstance;
            api.dotnet_finalize = &Finalize;
            api.dotnet_call_init = &CallInit;
            api.dotnet_call_update = &CallUpdate;
        }

        if (initInfo->outDefinedTypes != null)
        {
            if (_infos.Length > 0)
            {
                ref UnsafeArray<DotnetTypeInfo> types = ref *initInfo->outDefinedTypes;

                types = UnsafeArray<DotnetTypeInfo>.Allocate(_infos.Length);

                List<DotnetMethodInfo> methods = new();

                for (int i = 0; i < _infos.Length; i++)
                {
                    ref ScriptInfo info = ref _infos[i];

                    string scriptFullName = info.ScriptType.FullName;
                    uint typeNameLen = (uint)scriptFullName.Length;

                    types.Values[i].Name.Chars = Memory.AllocZeroed<char>(typeNameLen + 1);
                    types.Values[i].Type.Handle = i;

                    fixed (char* str = info.ScriptType.FullName)
                    {
                        Unsafe.CopyBlock(types.Values[i].Name.Chars, str, typeNameLen * sizeof(char));
                    }

                    if (info.Init != null)
                    {
                        methods.Add(CreateMetodInfo(scriptFullName, nameof(ScriptInfo.Init), i, 0));
                    }

                    if (info.Update != null)
                    {
                        methods.Add(CreateMetodInfo(scriptFullName, nameof(ScriptInfo.Update), i, 0));
                    }

                    if (info.Delete != null)
                    {
                        methods.Add(CreateMetodInfo(scriptFullName, nameof(ScriptInfo.Delete), i, 0));
                    }

                    types.Values[i].DefinedMethods = UnsafeArray<DotnetMethodInfo>.Allocate(methods.Count);

                    for (int j = 0; j < methods.Count; j++)
                    {
                        types.Values[i].DefinedMethods.Values[j] = methods[j];
                    }

                    methods.Clear();
                }
            }
        }
    }

    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    public static IntPtr CreateInstance(int type)
    {
        return (IntPtr)GCHandle.Alloc(Activator.CreateInstance(_infos[type].ScriptType), GCHandleType.Normal);
    }

    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    public static void Finalize(IntPtr handle)
    {
        ((GCHandle)handle).Free();
    }

    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    public static void CallInit(IntPtr handle, int type)
    {
        _infos[type].Init(Unsafe.As<IntPtr, object>(ref *(IntPtr*)handle));
    }

    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    public static void CallUpdate(IntPtr handle, int type, float dt)
    {
        _infos[type].Update(((GCHandle)handle).Target, dt);
    }

    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    public static byte TryStartNoGC(long size)
    {
        return GC.TryStartNoGCRegion(size) ? (byte)1 : (byte)0;
    }

    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    public static void EndNoGC()
    {
        GC.EndNoGCRegion();
    }
}
